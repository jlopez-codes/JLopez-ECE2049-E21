/*
 * peripherals.h
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_


#include <msp430.h>
#include <stdint.h>
#include "grlib.h"

#define DISPLAY_SHARP128x128
#if defined(DISPLAY_SHARP96x96)
#include "LcdDriver/sharp96/Sharp96x96.h"
#include "LcdDriver/sharp96/HAL_MSP_EXP430FR5529_Sharp96x96.h"
#elif defined(DISPLAY_SHARP128x128)
#include "LcdDriver/sharp128/Sharp128x128.h"
#include "LcdDriver/sharp128/HAL_MSP_EXP430F5529_Sharp128x128.h"
#endif

/*
 * DAC pin assignment is as follows
 * LDAC         P3.7
 * CS           P8.2
 * MOSI/SDI     P3.0
 * SCLK         P3.2
 */
#define DAC_PORT_LDAC_SEL       P3SEL
#define DAC_PORT_LDAC_DIR       P3DIR
#define DAC_PORT_LDAC_OUT       P3OUT

#define DAC_PORT_CS_SEL         P8OUT
#define DAC_PORT_CS_DIR         P8DIR
#define DAC_PORT_CS_OUT         P8OUT

#define DAC_PORT_SPI_SEL        P3SEL
#define DAC_PORT_SPI_DIR        P3DIR

#define DAC_PIN_MOSI            BIT0
#define DAC_PIN_SCLK            BIT2
#define DAC_PIN_CS              BIT2
#define DAC_PIN_LDAC            BIT7

#define DAC_SPI_REG_CTL0        UCB0CTL0
#define DAC_SPI_REG_CTL1        UCB0CTL1
#define DAC_SPI_REG_BRL         UCB0BR0
#define DAC_SPI_REG_BRH         UCB0BR1
#define DAC_SPI_REG_IFG         UCB0IFG
#define DAC_SPI_REG_STAT        UCB0STAT
#define DAC_SPI_REG_TXBUF       UCB0TXBUF
#define DAC_SPI_REG_RXBUF       UCB0RXBUF
#define DAC_SPI_CLK_SRC     (UCSSEL__SMCLK)
#define DAC_SPI_CLK_TICKS   0




//E,D,C,G
typedef enum notes
{
    NOTE_E,
    NOTE_D,
    NOTE_C,
    NOTE_G,
    NOTE_B
}
note;

/*
 * these are in ticks
 * every 0.005 seconds i increment by one
 */
typedef enum durations
{
    hold = 120, //120ticks * 0.005 = 1.2seconds this is
    quick = 60, //60ticks  * 0.005 = 0.3seconds
}
duration;

// Globals
extern tContext g_sContext; // user defined type used by graphics library

// Prototypes for functions defined implemented in peripherals.c
void configDisplay(void);
void BuzzerOn(note n);
void BuzzerOff(void);

void initLaunchpadButtons(void);
char readLaunchpadButtons(void);
void initLaunchpadLeds(void);
void setLaunchpadLeds(char v);
char readExternalButtons(void);
void initExternalButtons(void);

#endif /* PERIPHERALS_H_ */

