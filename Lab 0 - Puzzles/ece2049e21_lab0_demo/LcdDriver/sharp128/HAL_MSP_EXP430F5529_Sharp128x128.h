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
// HAL_MSP-EXP430FR5969_Sharp128x128.h - Prototypes for the Sharp128x128
//                  LCD display driver. There is no output from Sharp128x128 LCD
//
//                   MSP430FR5969                 LCD Sharp128x128
//                -----------------             -----------------
//               |     P2.2/UCB0CLK|---------> |SPI_CLK  EXT_MODE|--GND
//            /|\|                 |           |                 |
//             | |    P1.6/UCB0SIMO|---------> |SPI_SI   EXTCOMIN|--GND
//             --|RST              |           |                 |
//               |             P2.4|---------> |SPI_CS           |
//               |                 |		   |                 |
//               |             P4.3|---------> |DISP             |
//               |                 |		   |                 |
//               |             P4.2|-----*---> |VDD              |
//               |                 |      `--> |VDDA             |
//               |                 |            -----------------
//                -----------------
//*****************************************************************************

#ifndef __HAL_MSP_EXP430FR5969_SHARPLCD_H__
#define __HAL_MSP_EXP430FR5969_SHARPLCD_H__

#include <stdint.h>
#include <msp430.h>

//*****************************************************************************
//
// User Configuration for the LCD Driver
//
//*****************************************************************************

/*
 * Pin assignment is as follows:
 * Power        P6.5
 * DISP         P1.6
 * CS           P6.6
 * MOSI         P3.0
 * SCLK         P3.2
 */
#define PORT_SPI_SEL                        P3SEL
#define PORT_SPI_DIR                        P3DIR
#define PORT_DISP_SEL                       P1SEL
#define PORT_DISP_DIR                       P1DIR
#define PORT_DISP_OUT                       P1OUT

#define PORT_CS_SEL                         P6SEL
#define PORT_CS_DIR                         P6DIR
#define PORT_CS_OUT                         P6OUT

#define PORT_PWR_SEL                        P6SEL
#define PORT_PWR_DIR                        P6DIR
#define PORT_PWR_OUT                        P6OUT



#define PIN_SPI_MOSI                        BIT0
#define PIN_SPI_SCLK                        BIT2
#define PIN_PWR                             BIT5
#define PIN_DISP                            BIT6
#define PIN_CS                              BIT6

#define SPI_REG_CTL0    UCB0CTL0
#define SPI_REG_CTL1    UCB0CTL1
#define SPI_REG_BRL     UCB0BR0
#define SPI_REG_BRH     UCB0BR1
#define SPI_REG_IFG     UCB0IFG
#define SPI_REG_STAT    UCB0STAT
#define SPI_REG_TXBUF   UCB0TXBUF
#define SPI_REG_RXBUF   UCB0RXBUF

/*
 * UCSI SPI Clock parameters
 * The actual clock frequency is given in number of
 * ticks of the specified clock source.
 *
 * For our configuration, we use the same frequency
 * as SMCLK, which is 1.25MHz.
 */
#define SPI_CLK_SRC     (UCSSEL__SMCLK)
#define SPI_CLK_TICKS   0

// LCD Screen Dimensions
//#define LCD_VERTICAL_MAX                   128
//#define LCD_HORIZONTAL_MAX                 128

#ifdef USE_DRIVERLIB
// Ports from MSP430 connected to LCD
#define LCD_SPI_SI_PORT                     GPIO_PORT_P1
#define LCD_SPI_CLK_PORT                    GPIO_PORT_P2
#define LCD_DISP_PORT                       GPIO_PORT_P4
#define LCD_POWER_PORT                      GPIO_PORT_P4
#define LCD_SPI_CS_PORT                     GPIO_PORT_P2

// Pins from MSP430 connected to LCD
#define LCD_SPI_SI_PIN                      GPIO_PIN6
#define LCD_SPI_SI_PIN_FUNCTION             GPIO_SECONDARY_MODULE_FUNCTION
#define LCD_SPI_CLK_PIN                     GPIO_PIN2
#define LCD_SPI_CLK_PIN_FUNCTION            GPIO_SECONDARY_MODULE_FUNCTION
#define LCD_DISP_PIN                        GPIO_PIN3
#define LCD_POWER_PIN                       GPIO_PIN2
#define LCD_SPI_CS_PIN                      GPIO_PIN4

// Definition of USCI base address to be used for SPI communication
#define LCD_EUSCI_BASE                EUSCI_B0_BASE
#endif
// Non-volatile Memory used to store DisplayBuffer
//#define NON_VOLATILE_MEMORY_BUFFER

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern void HAL_LCD_initDisplay(void);
extern void HAL_LCD_writeCommandOrData(uint16_t command);
extern void HAL_LCD_clearCS(void);
extern void HAL_LCD_setCS(void);
extern void HAL_LCD_prepareMemoryWrite(void);
extern void HAL_LCD_finishMemoryWrite(void);
extern void HAL_LCD_waitUntilLcdWriteFinish(void);
extern void HAL_LCD_disableDisplay(void);
extern void HAL_LCD_enableDisplay(void);

#endif // __HAL_MSP_EXP430FR5969_SHARPLCD_H__
