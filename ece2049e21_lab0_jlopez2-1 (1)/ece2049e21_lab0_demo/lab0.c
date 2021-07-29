/************** ECE2049 DEMO CODE ******************/
/************** 14 May 2018   **********************/
/***************************************************/

#include <msp430.h>
#include <puzzle_tests.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

// Include puzzles for lab 0

// Function Prototypes
void swDelay(char numLoops);
int demoThings(void);


// Declare globals here

// Main
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired

    demoThings();

    // *** System initialization ***
    initLaunchpadButtons();
    initLaunchpadLeds();
    configDisplay();

    // ******* PUZZLES *********
    // Run tests on programming puzzles for lab 0
    // Ctrl+Click on this function to find its source
    test_all_puzzles();

    // Turn on the LEDs and make some noise to indicate we're done with puzzles
    // (There will be no sound unless you are using a board with an external buzzer)
    BuzzerOn();
    setLaunchpadLeds(0x3);
    swDelay(1);
    setLaunchpadLeds(0x0);
    BuzzerOff();

    // ********* DEMO CODE **********
    // This part of the program demonstrates an actual
    // program that provides some useful functionality with the hardware

    // *** Intro Screen ***

    Graphics_clearDisplay(&g_sContext); // Clear the display

    // Write some text to the display
    int h_center = LCD_HORIZONTAL_MAX / 2;
    Graphics_drawStringCentered(&g_sContext, "Welcome",  AUTO_STRING_LENGTH, h_center, 15, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to",       AUTO_STRING_LENGTH, h_center, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "ECE2049!", AUTO_STRING_LENGTH, h_center, 35, TRANSPARENT_TEXT);

    // Draw a box around everything because it looks nice
    Graphics_Rectangle box = {.xMin = 5, .xMax = LCD_HORIZONTAL_MAX - 5,
                              .yMin = 5, .yMax = LCD_VERTICAL_MAX - 5 };
    Graphics_drawRectangle(&g_sContext, &box);

    // We are now done writing to the display.  However, if we stopped here, we would not
    // see any changes on the actual LCD.  This is because we need to send our changes
    // to the LCD, which then refreshes the display.
    // Since this is a slow operation, it is best to refresh (or "flush") only after
    // we are done drawing everything we need.
    Graphics_flushBuffer(&g_sContext);


    // In our loop, we are going to read from the buttons and use that input
    // to update the LCD display.
    // To draw text on the display, we need to build an array of characters, so
    // here we make a "buffer" of 3 characters that we will adjust based on our input
    unsigned char buffer[3];
    buffer[0] = '>';
    buffer[2] = '<';

    while (1)    // Forever loop
    {
        char button_state = readLaunchpadButtons();

        if (button_state != 0)
        {
            setLaunchpadLeds(button_state);

            // Update the buffer based on the button state
            // Q: What does the "+ '0'" do?  Why is it necessary?
            // (What happens if you remove the "+ '0'"?)
            // Hint:  think back to the earlier question about the new value for "test".
            buffer[1] = button_state + '0';

            // Draw the characters in our buffer.  Our buffer is always 3 characters long,
            // so we can specify a length of 3 rather than using AUTO_STRING_LENGTH for argument 3
            Graphics_drawStringCentered(&g_sContext, buffer,  3, h_center, 45, OPAQUE_TEXT);
            Graphics_flushBuffer(&g_sContext); // Update the display
        }

    }  // end while (1)
}

int demoThings(void)
{
    // Define some local variables
    float a_flt = 190.68;
    int  test = 0x0800;      // In C prefix 0x means the number that follows is in hex
    long unsigned X = 114656;     // No prefix so number is assumed to be in decimal
    unsigned char myGrade='A';

    // Some utterly useless instructions
    // Use the debugger to step through these instructions.

    a_flt = a_flt * test;
    X = test + X;

    test = test - myGrade;

    // A number minus a letter?? What's actually going on here?
    // Q: What value stored in myGrade (i.e. what's the ASCII code for "A")?

    // Step past this point in the debugger
    // Q: What is the new value for test?  Explain the result.

    return test;
}

void swDelay(char numLoops)
{
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent removal in optimization
			                    // by compiler. Functionally this is useless code

	for (j=0; j<numLoops; j++)
    {
    	i = 50000 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}
