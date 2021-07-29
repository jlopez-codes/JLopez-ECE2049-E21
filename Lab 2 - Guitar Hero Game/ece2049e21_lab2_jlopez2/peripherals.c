/*
 * peripherals.c
 */
#include "peripherals.h"

// Globals
tContext g_sContext;    // user defined type used by graphics library

void BuzzerOn(note n)
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    switch(n)
    {
        case NOTE_E:
            TB0CCR0 = 50;
            break;
            // ACLK = 32768 HZ
            //t_int = (MAX_CNT + 1)/f_ACLK
            //t_int = (50+1)/(32768) = 0.0015564s is the period
            //Frequency = 1/(period)
            //1/(0.0015564) = 642Hz

        case NOTE_D:
            TB0CCR0 = 56;
            break;
            // ACLK = 32768 HZ
            //t_int = (MAX_CNT + 1)/f_ACLK
            //t_int = (56+1)/(32768) = 0.0017395s is the period
            //Frequency = 1/(period)
            //1/(0.0017395) = 574Hz

        case NOTE_C:
            TB0CCR0 = 63;
            break;
            // ACLK = 32768 HZ
            //t_int = (MAX_CNT + 1)/f_ACLK
            //t_int = (63+1)/(32768) = 0.001953s is the period
            //Frequency = 1/(period)
            //1/(0.001953) = 512Hz

        case NOTE_G:
            TB0CCR0 = 42;
            break;
            // ACLK = 32768 HZ
            //t_int = (MAX_CNT + 1)/f_ACLK
            //t_int = (42+1)/(32768) = 0.00131226s is the period
            //Frequency = 1/(period)
            //1/(0.00131226) = 762Hz

        case NOTE_B:
            TB0CCR0 = 66;
            break;
            // ACLK = 32768 HZ
            //t_int = (MAX_CNT + 1)/f_ACLK
            //t_int = (66+1)/(32768) = 0.00204468s is the period
            //Frequency = 1/(period)
            //1/(0.00204468) = 489Hz
      }

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

void initExternalButtons(void)
{
    P1SEL &= ~BIT4;
    P1DIR &= ~BIT4;
    P1REN |=  BIT4;
    P1OUT |=  BIT4;

    P1SEL &= ~BIT5;
    P1DIR &= ~BIT5;
    P1REN |=  BIT5;
    P1OUT |=  BIT5;

    P2SEL &= ~BIT4;
    P2DIR &= ~BIT4;
    P2REN |=  BIT4;
    P2OUT |=  BIT4;

    P2SEL &= ~BIT5;
    P2DIR &= ~BIT5;
    P2REN |=  BIT5;
    P2OUT |=  BIT5;
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
    // Read input registers for both buttons
    // into variable that is 0 or 1
    char b0 = (~P1IN & BIT1) >> 1;
    char b1 = (~P2IN & BIT1) >> 1;

    // Finally, combine the variables to create the output
    // in the format we specified
    return (b1 << 1) | b0;
}

char readExternalButtons(void)
{
    // Read input registers for both buttons
    // into variable that is 0 or 1

    char b0 = (~P1IN & BIT4) >> 4;
    char b1 = (~P2IN & BIT4) >> 4;
    char b2 = (~P1IN & BIT5) >> 5;
    char b3 = (~P2IN & BIT5) >> 5;

    // Finally, combine the variables to create the output
    // in the format we specified
    char read = b0;
    read |= (b1 << 1);
    read |= (b2 << 2);
    read |= (b3 << 3);
    return read;
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
