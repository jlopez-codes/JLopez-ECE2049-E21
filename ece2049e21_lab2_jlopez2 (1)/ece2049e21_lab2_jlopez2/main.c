/************** ECE2049 Lab 2 ******************/
/************** 12 July 2021   **********************/
/***************************************************/
#include <msp430.h>
#include "peripherals.h"
#include "utils/ustdlib.h"
#include "utils/debug_assert.h"


volatile long unsigned int timer = 0;


// Function Prototypes
void swDelay(char numLoops);
void swDelay(char numLoops)
{
    volatile unsigned int i,j;
    for (j=0; j<numLoops; j++)
    {
        i = 50000;
        while (i > 0)
            while (i)
            i--;
    }
}


#pragma vector = TIMER2_A0_VECTOR
interrupt void Timer_A2_ISR(void)
{
    timer++;
}

/*
 * Timer A2 properly configured with resolution set to 0.005s or less
 * Loop through each note in your song and play it for the amount of time specified in
 * your data structure, lighting up an LED for each note. You must use the timer to keep track of
 * the duration of each note—no software delays! When the song is done, go back to the starting
 * state
 *
 * t_int = 0.005 seconds
 * t_int = (MAX_CNT + 1)/(32768)
 * 0.005*(32768) = 163.84 --> rounded up to 164
 * 164 - 1 = 163
 * MAX_CNT = 163
 */
void TimerA2(void)
{
    TA2CTL = TASSEL_1 + ID_0 + MC_1;
    TA2CCR0 = 163;
    TA2CCTL0 = CCIE;
}

/*
 * LEDs are on P6.0-6.1
 * Register PDIR makes pins an input or output so P6.0 will looks like P6DIR = 0b01000001;
 * Register P1OUT specifies a pin as high or low, since we are initializing, set as  low
 *
 */
void initExternalLeds(void)
{
    P6SEL &= ~(BIT3|BIT2|BIT1|BIT0); // Set LED pins for digital I/O
    P6DIR |= (BIT3|BIT2|BIT1|BIT0); // Set LED pins as outputs
    P6OUT &= ~(BIT3|BIT2|BIT1|BIT0); // Turn LEDs off (set output register to 0)
}

//Write a function setExternalLeds() to take in a variable x and set the state of the LEDs, interpreting
//x as a bit vector.
void setExternalLeds(char x)
{
    if (x & BIT0) {
        P6OUT |= BIT3;
    }
    else {
        P6OUT &= ~BIT3;
    }

    if (x & BIT1) {
        P6OUT |= BIT2;
    }
    else {
        P6OUT &= ~BIT2;
    }

    if (x & BIT2) {
        P6OUT |= BIT1;
    }
    else {
        P6OUT &= ~BIT1;
    }

    if (x & BIT3) {
        P6OUT |= BIT0;
    }
    else {
        P6OUT &= ~BIT0;
    }
}

/*
 * play a few notes using the buzzer, and light up an LED for each note
 * used setLaunchpadLeds
 */
void setExternalLeds(note notes)
{
    if((notes == NOTE_E) | (notes == NOTE_B))
    {
        setExternalLeds(0x08);
    }
    else if(notes == NOTE_D)
    {
        setExternalLeds(0x04);
    }
    else if(notes == NOTE_C)
    {
        setExternalLeds(0x02);
    }
    else if(notes == NOTE_G)
    {
        setExternalLeds(0x01);
    }
}

/*
 * Song defined using a data structure representing (at least) pitch and duration for each note
*/
note MHALLmelody[28] = {NOTE_E,NOTE_D,NOTE_C,NOTE_D,NOTE_E,NOTE_E,NOTE_E,NOTE_D,NOTE_D,NOTE_D,NOTE_E,NOTE_G,NOTE_G,NOTE_E,NOTE_D,NOTE_C,NOTE_D,NOTE_E,NOTE_E,NOTE_E,NOTE_E,NOTE_D,NOTE_D,NOTE_E,NOTE_D,NOTE_C};
duration MHALLDurations[28] = {quick, quick, quick, quick, quick, quick, hold, quick, quick, quick, quick, quick, quick, hold, quick, quick, quick, quick, quick, quick, hold, quick, quick, quick, quick, quick, quick, hold};

enum State
{
    stage1,
    stage2
}
state;


enum State state = stage1;



// Main
void main(void)
 {
    WDTCTL = WDTPW | WDTHOLD;

    // *** System initialization ***
    initLaunchpadButtons();
    initLaunchpadLeds();
    initExternalButtons();
    initExternalLeds();
    configDisplay();

    int i;
    char button_state;

    while (1)
    {
        switch(state)
        //E,D,C,G
        {
             case stage1: //stage 1 Connect a small buzzer and configure it to play different frequencies
               button_state = readExternalButtons();

                if(button_state == 1)
                {
                    BuzzerOn(NOTE_E); //YELLOW
                    setExternalLeds(0x08); //p6.0
                }

                else if(button_state == 2)
                {
                    BuzzerOn(NOTE_D); //BLUE
                    setExternalLeds(0x04); //p6.1
                }
                else if(button_state == 4)
                {
                    BuzzerOn(NOTE_C);//GREEN
                    setExternalLeds(0x02); //p6.2
                }
                else if (button_state == 8)
                {
                    BuzzerOn(NOTE_G); //RED
                    setExternalLeds(0x01); //P6.3
                }
                else if (button_state = readLaunchpadButtons())
                {
                   state = stage2;
                }
               break;

            case stage2:
                /*
                 * Using the timer count, i play it at the beginning of the program and enable interrupts
                 * to compare the duration of each note to the elapsed time using the global count.
                 */
                TimerA2();
                _enable_interrupt();

                for(i = 0; i < 26; i++)

                {
                    BuzzerOn(MHALLmelody[i]);
                    setExternalLeds(MHALLmelody[i]);
                    unsigned long start_time = timer;
                    while((timer - start_time) < MHALLDurations[i]){}
                    BuzzerOff();
                }
                break;

            }
    }

 }





