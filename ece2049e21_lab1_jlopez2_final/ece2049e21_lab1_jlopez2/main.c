#include <msp430.h>
#include "peripherals.h"
#include "utils/debug_assert.h"
#include <stdlib.h>
#include <time.h>

#define BUTTON_RIGHT 0X01
#define BUTTON_LEFT 0X02

#define LED_NONE 0x00
#define LED_RIGHT  0x01
#define LED_LEFT 0x02



//STORE THE CARD VALUES FOR THE PLAYER
//Ace, numbers 2-10, Jack, Queen, King
int PlayerCardValues(char cardValue)
{
    int pHand = 0;

    if((cardValue == 'J') || (cardValue == 'Q') || (cardValue == 'K') || (cardValue == 'E'))
    {
        pHand += 10;
    }
    else if(cardValue == '2')
    {
        pHand += 2;
    }
    else if(cardValue == '3')
    {
        pHand += 3;
    }
    else if(cardValue == '4')
    {
        pHand += 4;
    }
    else if(cardValue == '5')
    {
        pHand += 5;
    }
    else if(cardValue == '6')
    {
        pHand += 6;
    }
    else if(cardValue == '7')
    {
        pHand += 7;
    }
    else if(cardValue == '8')
    {
        pHand += 8;
    }
    else if(cardValue == '9')
    {
        pHand += 9;
    }
    else if((cardValue == 'A') && ((pHand + 11) <= 21))
    {
        pHand += 11;
    }
    else if((cardValue == 'A') && ((pHand = 11) > 21))
    {
        pHand += 1;
    }

    return pHand;
}

//STORE THE CARD VALUES FOR THE DEALER
//Ace, numbers 2-10, Jack, Queen, King
int DealerCardValues(char cardValue) {
        int dHand = 0;
            if (cardValue == 'J' ||  'Q' ||  'K' || 'E'){
                dHand += 10;
                }
            else if (cardValue == '2') {
                dHand += 2;
                }
            else if (cardValue == '3') {
                dHand += 3;
                }
            else if (cardValue == '4') {
                dHand += 4;
                }
            else if (cardValue == '5') {
                dHand += 5;
            }
            else if (cardValue == '6'){
                dHand += 6;
                }
            else if (cardValue == '7'){
                dHand += 7;
                }
            else if (cardValue == '8'){
                dHand += 8;
                }
            else if (cardValue == '9'){
                dHand += 9;
                }
            else if ((cardValue == 'A') && (dHand + 11 <= 17)) {
                dHand += 11;
                }
            else if ((cardValue == 'A') && (dHand + 11 > 17)) {
                dHand += 1;
            }
        return dHand;
    }


void swDelay(char numLoops);

//USED FROM LAB 0
void swapCards(char *cardOne, char *cardTwo)
{
    char temp = *cardOne;
    *cardOne = *cardTwo;
    *cardTwo = temp;
}

// Shuffle the card values in the deck
//create a new array to fill with random card values
void shuffleNumbers(char arr[], int input)
{
    srand(input);
    int i = 12;
    for(i; i > 0; i--)
    {
        int j = rand() % (i+1);
        swapCards(&arr[i], &arr[j]);
    }
}

void shuffleSuit(char arr[], int input)
{
    srand(8);
    int i = 3;
    for(i; i > 0; i--)
    {
        int j = rand() % (i+1);
        swapCards(&arr[i], &arr[j]);
    }
}

void swDelay(char numLoops)
{
    volatile unsigned int i,j;

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;
        while (i > 0)
           i--;
    }
}


enum game_state {
    WELCOME = 0,
    PROMPT  = 1,
    READ    = 2,
    SHUFFLE = 3,
    DEAL    = 4,
    LOST    = 5,
    RESET   = 6,
};

// Main
void main(void)
{
    int doOnce = 1;
    int input_number = 0;
    int playerVal;
    int dealerVal;

    char numbers[] = {'E','2','3','4','5','6','7','8','9','A','J','Q','K'};
    char suit[] = {'H','D','S','C'};

    unsigned char buffer[3];
    buffer[0] = '-';
    buffer[1] = '>';

    WDTCTL = WDTPW | WDTHOLD;

    initLaunchpadButtons();
    initLaunchpadLeds();
    configDisplay();


    int state = 0;

    while (1)
    {
        char button_state = readLaunchpadButtons();

        switch (state)
        {
            case WELCOME:

            Graphics_drawStringCentered(&g_sContext, "MSP430",               AUTO_STRING_LENGTH, 64, 15, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "BlackJack",            AUTO_STRING_LENGTH, 64, 25, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press LEFT to start", AUTO_STRING_LENGTH, 64, 35, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            if (button_state & BUTTON_LEFT)
            {
                Graphics_clearDisplay(&g_sContext);
                swDelay(1);
                state = PROMPT;
            }
            break;

            case PROMPT:

            Graphics_drawStringCentered(&g_sContext, "Enter Cut",  AUTO_STRING_LENGTH, 64, 15, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Using Left Button",            AUTO_STRING_LENGTH, 64, 25, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Then Hit RIGHT button",  AUTO_STRING_LENGTH, 64, 105, TRANSPARENT_TEXT);

            buffer[2] = input_number + '0';
            Graphics_drawStringCentered(&g_sContext, buffer, 3, 64, 35, OPAQUE_TEXT);
            Graphics_flushBuffer(&g_sContext);
            state = READ;
            break;

            case READ:
            if(button_state & BUTTON_LEFT)
            {
                swDelay(1);
                state = SHUFFLE;
            }
            else
            {
                input_number = (input_number + 1) % 10;
                state = PROMPT;
            }
            break;

            case SHUFFLE:
            shuffleNumbers(numbers, input_number);
            shuffleSuit(suit, input_number);

            //THIS IS ALL THE POSSIBLE CARDS EACH PLAYER CAN HAVE
            //ITS CREATES HOW MANY CARDS EACH PLAYER CAN HAVE
            unsigned char playerDeal[11] = {numbers[0],suit[0],'&',numbers[1],suit[1]};
            unsigned char dealerDeal[19]  = {numbers[2],suit[2],numbers[3],suit[3]};
            unsigned char showDeal[3]    = {numbers[2],suit[2]};                        //1 CARD SHOWN

            playerVal = PlayerCardValues(playerDeal[0]);
            playerVal += PlayerCardValues(playerDeal[3]);
            dealerVal = PlayerCardValues(dealerDeal[0]);
            dealerVal += PlayerCardValues(dealerDeal[2]);

            while (doOnce == 1) //prevents getting stuck in an infinite loop
            {
                Graphics_drawStringCentered(&g_sContext, "Player", AUTO_STRING_LENGTH, 40, 40, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, playerDeal, AUTO_STRING_LENGTH, 40, 55, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "Dealer", AUTO_STRING_LENGTH, 90, 40, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, showDeal, AUTO_STRING_LENGTH, 90, 55, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                doOnce = 0;
            }

            if (button_state & BUTTON_RIGHT)
            {
                Graphics_clearDisplay(&g_sContext);
                swDelay(1);
                state = DEAL ;
            }
            break;

            case DEAL:
            Graphics_drawStringCentered(&g_sContext, "Player", AUTO_STRING_LENGTH, 40, 40, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, playerDeal, AUTO_STRING_LENGTH, 40, 55, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Dealer", AUTO_STRING_LENGTH, 90, 40, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, showDeal, AUTO_STRING_LENGTH, 90, 55, TRANSPARENT_TEXT);

            Graphics_drawStringCentered(&g_sContext, "HIT with left", AUTO_STRING_LENGTH, 64, 75, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "STAY with right", AUTO_STRING_LENGTH, 64, 95, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            //IF PLAYER HITS
            if (button_state & BUTTON_LEFT)
            {
                Graphics_clearDisplay(&g_sContext);
                playerDeal[5] = '&';
                playerDeal[6] = numbers[4];
                playerDeal[7] = suit[1];
                playerVal += PlayerCardValues(playerDeal[6]);

            //IF PLAYER BUSTS
            if (playerVal > 21)
            {
                Graphics_clearDisplay(&g_sContext);
                swDelay(1);
                state = LOST;
            }

                Graphics_drawStringCentered(&g_sContext, "Player:", AUTO_STRING_LENGTH, 40, 40, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, playerDeal, AUTO_STRING_LENGTH, 40, 55, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "Dealer:", AUTO_STRING_LENGTH, 90, 40, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, showDeal, AUTO_STRING_LENGTH, 90, 55, TRANSPARENT_TEXT);

                Graphics_drawStringCentered(&g_sContext, "HIT with left", AUTO_STRING_LENGTH, 64, 75, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "STAY with right", AUTO_STRING_LENGTH, 64, 95, TRANSPARENT_TEXT);
            }

            //IF PLAYER STAYS
            if (button_state & BUTTON_RIGHT)
            {
                dealerDeal[5] = '&';
                dealerDeal[6] = numbers[4];
                dealerDeal[7] = suit[1];
                dealerVal += DealerCardValues(dealerDeal[6]);

            //IF DEALER BUSTS
            if(dealerVal > 17)
            {
                Graphics_clearDisplay(&g_sContext);
                swDelay(1);
                state = RESET;
            }
            else
            {
                Graphics_clearDisplay(&g_sContext);
                swDelay(1);
                state = LOST;
            }
         }
            break;

            case LOST:

            Graphics_drawStringCentered(&g_sContext, "LOST", AUTO_STRING_LENGTH, 58, 30, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Play Again?", AUTO_STRING_LENGTH, 64, 89, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press Left Button!", AUTO_STRING_LENGTH, 64, 99, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            if (button_state & BUTTON_LEFT)
            {
                Graphics_clearDisplay(&g_sContext);
                swDelay(1);
                state = WELCOME;
            }
            break;

            case RESET:

            Graphics_drawStringCentered(&g_sContext, "WON", AUTO_STRING_LENGTH, 64, 33, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Play Again?", AUTO_STRING_LENGTH, 64, 89, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press Left Button!", AUTO_STRING_LENGTH, 64, 99, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            Graphics_clearDisplay(&g_sContext);

            if (button_state & BUTTON_LEFT)
            {
                Graphics_clearDisplay(&g_sContext);
                swDelay(1);
                state = WELCOME;
            }
            break;
        } //STATE
    } //WHILE
} //MAIN
