/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
//
// HAL_MSP-EXP430FR5969_Sharp128x128.c
//
//*****************************************************************************
//
//! \addtogroup display_api
//! @{
//
//*****************************************************************************

#include "grlib.h"

#ifdef USE_DRIVERLIB
#include "inc/hw_memmap.h"
#include "../../driverlibHeaders.h"
#endif

#include <LcdDriver/sharp128/HAL_MSP_EXP430F5529_Sharp128x128.h>


//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the Sharp128x128 display. This function
//! configures the GPIO pins used to control the LCD display when the basic
//! GPIO interface is in use. On exit, the LCD has been reset and is ready to
//! receive command and data writes.
//!
//! \return None.
//
//*****************************************************************************
void HAL_LCD_initDisplay(void)
{
#ifdef USE_DRIVERLIB
    // Configure LCD_SCLK_PIN for SPI_CLK mode
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_SPI_CLK_PORT,
                                                LCD_SPI_CLK_PIN,
                                                LCD_SPI_CLK_PIN_FUNCTION);

    // Configure LCD_MOSI_PIN for SPI_MOSI mode
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_SPI_SI_PORT,
                                                LCD_SPI_SI_PIN,
                                                LCD_SPI_SI_PIN_FUNCTION);

    // Provide power to LCD
    GPIO_setAsOutputPin(LCD_POWER_PORT,
                        LCD_POWER_PIN);

    GPIO_setOutputHighOnPin(LCD_POWER_PORT,
                            LCD_POWER_PIN);

    // Turn on DISP
    GPIO_setAsOutputPin(LCD_DISP_PORT,
                        LCD_DISP_PIN);

    GPIO_setOutputHighOnPin(LCD_DISP_PORT,
                            LCD_DISP_PIN);

    // Configure LCD_SPI_CS_PIN as output pin
    GPIO_setAsOutputPin(LCD_SPI_CS_PORT,
                        LCD_SPI_CS_PIN);

    HAL_LCD_clearCS();

    EUSCI_B_SPI_initMasterParam spiMasterParams =
    {
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
        8000000,
        1000000,
        EUSCI_B_SPI_MSB_FIRST,
        EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
        EUSCI_B_SPI_3PIN
    };

    EUSCI_B_SPI_initMaster(LCD_EUSCI_BASE,
                           &spiMasterParams);

    EUSCI_B_SPI_enable(LCD_EUSCI_BASE);
#else
    // Configure SCLK and MOSI for peripheral mode
    PORT_SPI_SEL |= (PIN_SPI_MOSI|PIN_SPI_SCLK);

    // The LCD is powered using a GPIO pin, so configure it as output
    PORT_PWR_SEL &= ~PIN_PWR;
    PORT_PWR_DIR |=  PIN_PWR;

    // Drive the power pin high to power the LCD
    PORT_PWR_OUT |=  PIN_PWR;

    // Configure the display enable signal DISP, drive it high to enable the LCD
    PORT_DISP_SEL &= ~PIN_DISP;
    PORT_DISP_DIR |=  PIN_DISP;
    PORT_DISP_OUT |=  PIN_DISP;

    // Configure the display chip select as an output
    PORT_CS_SEL &=  ~PIN_CS;
    PORT_CS_DIR |=   PIN_CS;

    // Initialize the chip select in a deasserted state
    HAL_LCD_clearCS();

    // Now configure UCSIB0 to function as our SPI controller

    // Disable the module so we can configure it
    SPI_REG_CTL1 |= UCSWRST;

    SPI_REG_CTL0 &= ~(UCCKPH|UCCKPL|UC7BIT|UCMSB); // Reset the controller config parameters
    SPI_REG_CTL1 &= ~UCSSEL_3; // Reset the clock configuration

    SPI_REG_CTL1 |= SPI_CLK_SRC; // Select SMCLK for our clock source

    // Set SPI clock frequency (which is the same frequency as SMCLK so this can apparently be 0)
    SPI_REG_BRL  =  ((uint16_t)SPI_CLK_TICKS) & 0xFF;         // Load the low byte
    SPI_REG_BRH  = (((uint16_t)SPI_CLK_TICKS) >> 8) & 0xFF;   // Load the high byte

    // Configure for SPI master, synchronous, 3 wire SPI, MSB first, capture data on first edge,
    // and inactive low polarity
    SPI_REG_CTL0 |= (UCMST|UCSYNC|UCMODE_0|UCMSB|UCCKPH);

    // Reenable the module
    SPI_REG_CTL1 &= ~UCSWRST;
    SPI_REG_IFG  &= ~UCRXIFG;
#endif
}

//*****************************************************************************
//
// Writes command or data to the LCD Driver
//
// \param ucCmdData is the 8 or 16 bit command to send to the LCD driver
// Uses the SET_LCD_DATA macro
//
// \return None
//
//*****************************************************************************
void HAL_LCD_writeCommandOrData(uint16_t command)
{
#ifdef USE_DRIVERLIB
    while(!EUSCI_B_SPI_getInterruptStatus(LCD_EUSCI_BASE,
                                          EUSCI_B_SPI_TRANSMIT_INTERRUPT))
    {
        ;
    }
    EUSCI_B_SPI_transmitData(LCD_EUSCI_BASE,command);
#else
    /* Wait for the TX buffer to be ready */
    while(!(SPI_REG_IFG & UCTXIFG));

    /* Send the data */
    SPI_REG_TXBUF = command;
#endif
}

//*****************************************************************************
//
// Clears CS line
//
// This macro allows to clear the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************
void HAL_LCD_clearCS(void){
#ifdef USE_DRIVERLIB
    GPIO_setOutputLowOnPin(LCD_SPI_CS_PORT, LCD_SPI_CS_PIN);
#else
    PORT_CS_OUT &= ~PIN_CS;
#endif
}

//*****************************************************************************
//
// Set CS line
//
// This macro allows to set the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************
void HAL_LCD_setCS(void){
#ifdef USE_DRIVERLIB
    GPIO_setOutputHighOnPin(LCD_SPI_CS_PORT, LCD_SPI_CS_PIN);
#else
    PORT_CS_OUT |= PIN_CS;
#endif
}

//*****************************************************************************
//
// Waits until the SPI communication with the LCD is finished a command to
// the LCD Driver
//
// \param None
//
// \return None
//*****************************************************************************
void HAL_LCD_waitUntilLcdWriteFinish(void)
{
#if USE_DRIVERLIB
    while(EUSCI_B_SPI_isBusy(LCD_EUSCI_BASE))
#else
    while(SPI_REG_STAT & UCBUSY);
#endif
    {
        ;
    }
}

//*****************************************************************************
//
// Disables Shapr128x128 LCD
//
// \param None
//
// \return None
//*****************************************************************************
void HAL_LCD_disableDisplay(void)
{
#ifdef USE_DRIVERLIB
    GPIO_setOutputLowOnPin(LCD_DISP_PORT, LCD_DISP_PIN);
    GPIO_setOutputLowOnPin(LCD_POWER_PORT, LCD_POWER_PIN);
#else
    PORT_DISP_OUT &= ~PIN_DISP;
    PORT_PWR_OUT  &= ~PIN_PWR;
#endif
}

//*****************************************************************************
//
// Enables Shapr128x128 LCD
//
// \param None
//
// \return None
//*****************************************************************************
void HAL_LCD_enableDisplay(void)
{
#ifdef USE_DRIVERLIB
    GPIO_setOutputHighOnPin(LCD_POWER_PORT, LCD_POWER_PIN);
    GPIO_setOutputHighOnPin(LCD_DISP_PORT, LCD_DISP_PIN);
#else
    PORT_DISP_OUT |= PIN_DISP;
    PORT_PWR_OUT |= PIN_PWR;
#endif
}

//*****************************************************************************
//
// Prepare to write memory
//
// This macro unlocks flash memory controller and
// sets access right on flash controller
//
// \return None
//
//*****************************************************************************
void HAL_LCD_prepareMemoryWrite()
{
}

//*****************************************************************************
//
// Finish memory writing
//
// This macro removes access rights on flash controller and
// locks flash memory controller.
//
// \return None
//
//*****************************************************************************
void HAL_LCD_finishMemoryWrite()
{
    __no_operation();
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
