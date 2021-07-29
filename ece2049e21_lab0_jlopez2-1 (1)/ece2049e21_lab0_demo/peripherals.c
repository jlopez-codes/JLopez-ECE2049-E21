/*
 * peripherals.c
 *
 *  Created on: Jan 29, 2014
 *      Author: deemer
 *  Updated on Jan 3, 2016
 *  	smj
 *  Updated on July 7, 2018
 *      deemer
 *  Updated on Jan 14, 2018
 *      smj
 *
 */

#include "peripherals.h"


// Globals
tContext g_sContext;    // user defined type used by graphics library




/*
 * Enable a PWM-controlled buzzer on P3.5
 * This function makes use of TimerB0.
 */
void BuzzerOn(void)
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    // Doing this with a hard coded values is NOT the best method
    // We do it here only as an example. You will fix this in Lab 2.
    TB0CCR0   = 128;                    // Set the PWM period in ACLK ticks
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}


/*
 * Disable the buzzer on P7.5
 */
void BuzzerOff(void)
{
    // Disable both capture/compare periods
    TB0CCTL0 = 0;
    TB0CCTL5 = 0;
}

void initLaunchpadButtons(void)
{
    P1SEL &= ~BIT1;
    P1DIR &= ~BIT1;
    P1REN |=  BIT1;
    P1OUT |=  BIT1;

    P2SEL &= ~BIT1;
    P2DIR &= ~BIT1;
    P2REN |=  BIT1;
    P2OUT |=  BIT1;
}

char readLaunchpadButtons(void)
{
    return (~P2IN & BIT1) | ((~P1IN & BIT1) >> 1);
}

void initLaunchpadLeds(void)
{
    P1SEL &= ~BIT0;
    P1DIR |=  BIT0;
    P1OUT &= ~BIT0;

    P4SEL &= ~BIT7;
    P4DIR |=  BIT7;
    P4OUT &= ~BIT7;
}

void setLaunchpadLeds(char v) {
    // LSB:  Rightmost LED (LED2, P4.7)
    if (v & BIT0) {
        P4OUT |= BIT7;
    } else {
        P4OUT &= ~BIT7;
    }

    // MSB:  Leftmost LED (LED1, P1.0)
    if (v & BIT1) {
        P1OUT |= BIT0;
    } else {
        P1OUT &= ~BIT0;
    }
}

void configDisplay(void)
{
    // Enable use of external clock crystals
     P5SEL |= (BIT5|BIT4|BIT3|BIT2);

	// Initialize the display peripheral
#if defined(DISPLAY_SHARP96x96)
	Sharp96x96_Init();
#elif defined(DISPLAY_SHARP128x128)
    Sharp128x128_initDisplay();
    Sharp128x128_enable();
#endif

    // Configure the graphics library to use this display.
	// The global g_sContext is a data structure containing information the library uses
	// to send commands for our particular display.
	// You must pass this parameter to each graphics library function so it knows how to
	// communicate with our display.
#if defined(DISPLAY_SHARP96x96)
    Graphics_initContext(&g_sContext, &g_sharp96x96LCD);
#elif defined(DISPLAY_SHARP128x128)
	Graphics_initContext(&g_sContext, &g_sharp128x128LCD);
#endif

    Graphics_setForegroundColor(&g_sContext, ClrBlack);
    Graphics_setBackgroundColor(&g_sContext, ClrWhite);
    Graphics_setFont(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);
    Graphics_flushBuffer(&g_sContext);
}


//------------------------------------------------------------------------------
// Timer1 A0 Interrupt Service Routine
//------------------------------------------------------------------------------
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR (void)
{
	// Display is using Timer A1
	// Not sure where Timer A1 is configured?
#if defined(DISPLAY_SHARP96x96)
	Sharp96x96_SendToggleVCOMCommand();  // display needs this toggle < 1 per sec
#elif defined(DISPLAY_SHARP128x128)
	Sharp128x128_SendToggleVCOMCommand();
#endif
}
