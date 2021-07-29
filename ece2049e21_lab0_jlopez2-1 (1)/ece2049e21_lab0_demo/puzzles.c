/*
 * lab0.c - Programming puzzles for lab 0
 *
 *  Created on: Apr 10, 2018
 *      Author: deemer
 */

#include <puzzles.h>


/*
 * ****** PUZZLES ********
 * This is where you implement your solutions for the puzzles
 *
 * Each function provides a comment describing how the function
 * should be implemented, as well as the C operations you are permitted
 * to use.
 *
 * Currently, each function is a "stub":  it does nothing, but contains
 * a meaningless dummy statement (like "return 0") that just
 * allows it to compile.  You should replace the body of the function
 * with your own implementation.
 *
 * If you want to know more about how the function should operate,
 * take a look at its tests in puzzle_tests.c.  These tests provide
 * some sample inputs and outputs for each function.
 *
 * ***NOTE***: YOU MAY NOT BE REQUIRED TO COMPLETE ALL OF THE
 * PUZZLES LISTED HERE.  SEE YOUR LAB DOCUMENT FOR DETAILS ON WHICH PUZZLES
 * ARE REQUIRED AND WHICH MAY BE EXTRA CREDIT.
 *
 */

// ********* WARMUP *********
// linear:  Given x, output a value corresponding
// to the linear equation 2*x + 4
//
// ALLOWED OPERATORS:  All bitwise and logical operators, if/else statements
// PROHIBITED: loops (for, while), calling functions, or floating point math
int linear(int x)
{
    return 2*x + 4;

}

// gt20: Return 1 if both a and b are greater than 20,
// and 0 otherwise
// ALLOWED OPERATORS:  All bitwise and logical operators, if/else statements
// PROHIBITED: loops (for, while), calling functions, or floating point math
int gt20(int a, int b)
{
        if (a>20 && b>20){
            return 1;
        } else {
            return 0;
        }
}



// ******** LOGICAL OPERATORS **********

// clamp:  "Clamp" input x within upper and lower bounds
// lower and upper:  if x < lower, return lower, if x > upper
// return upper, otherwise return x.
// ALLOWED OPERATORS:  All bitwise and logical operators, if/else statements
// PROHIBITED: loops (for, while), calling functions, or floating point math

    int clamp(int x, int lower, int upper)
    {
        if (x < lower){
            return lower;
        }
        if (x > upper){
            return upper;
        }
        else{
            return x;
        }

    }

    /*
     * In this puzzle, there needed to be a comparison between the upper and lower bounds.
     * I used an if statement because
     *
     *
     */


// Return true if x corresponds to a letter
// in the ASCII table (that is A-Z or a-z)
// To do this, you may NOT write an if statement
// for each character.
// HINT:  Look at an ASCII table
//
// ALLOWED OPERATORS:  All bitwise and logical operators, if/else statements
// PROHIBITED: loops (for, while), calling functions, or floating point math
int isLetter(char x)
{
    return ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'));
}

/*
 * "Shift" character c in the alphabet by
 * the number of places given by variable shift.
 * For example, 'A' shifted by 3 -> 'D'
 *
 * If shifting the letter would go past 'Z', the shifted result
 * should wrap around, eg. 'X' shifted by 4 -> 'B'
 * See the tests for more examples.
 *
 * You may NOT solve this problem by writing one
 * if statement per letter.  Hint:  see ASCII table.
 *
 * You may assume that the input is a CAPITAL ASCII letter.
 *
 *
 * ALLOWED OPERATORS:  All bitwise and logical operators, if/else statements
 * PROHIBITED: loops (for, while), calling functions, or floating point math
 */
char letterShift(char c, int shift)
{
    char v = c + shift;
    if (v > 'Z')
    {
        return v - 26;
    }
    else
    {
        return v;
    }


}

/*
 * assign a new variable that shifts the input by the number of times its shifted
 * if the v is greater than Z (ASCII 'Z'= 90)
 * subtract v - 26 because if 'Z' = 90 and 'A' = 65, then 90-65 = 26 which will return back to A
 */

// ******** BITWISE MANIPULATION **********


// testBit:  Return a value with bit b of x to 1,
// leaving all other bits unchanged
// You may assume b is in the range 0-15.
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
int setBit(int x, int b)
{
    return (x = x | 1 << b); // (x|= 1<<b)
}


/*
 *
 * setBit means making a bit 1 regardless of it's previous value
 * I used bitwise operation OR to set a particular bit because if we do OR
 * between 1 and any other bit, the results becomes 1
 *
 * Bits are numbered starting from 0 aka LSB
 * To find if the Nth bit of an integer is set, I shifted the operation to check
 * the value of only that one specific bit.
 *
 * so if b = 15   and x = 0x4444 ==50244
 *
 *
 *          50244 | 1 << 15                             shift the number 1 to the left 15 bits (1<<15 == 2^15 == 32768)
 *          50244 | 0000 0000 0000 0001 << 15
 *          50244 | 1000 0000 0000 0000 == 32768d
 *          50244 | 32668
 *
 *           1100 0100 0100 0100
 *           1000 0000 0000 0000
 *         -----------------------
 *           1100 0100 0100 0100 == 0xC444
 *
 */

// testBit:  Return a value with bit b of x to 0,
// leaving all other bits unchanged
// You may assume b is in the range 0-15.
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
int clearBit(int x, int b)
{
    return (x = x & ~(1 << b));
}

/*
 * clearBit means making a bit 0 regardless of it's previous value
 * I used bitwise operation AND (&) to set a particular bit because if we do &
 * between 0 and any other bit, the results becomes 0
 *
 * Same process as the setBit but this time we are looking to set a 0 so I used
 * the AND operator.
 *
 */



// Compute x/(2^n) (that is, x divided by the quantity (two to the power n))
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
int divpwr2(int x, int n)
{
    return x>>n;
}

// Count number of 1's in x
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
int bitCount(char x)
{
    return 0;
}



// ******** BYTE MANIPULATION **********

// Get *BYTE* n from x
// Assume n is a value from 0-3,
// and byte 0 is the LEAST significant byte
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
char getByte(long x, int n)
{
    return (x >> (8*n)) & 0xFF;
}

/*
 * Goal: extract byte n from integer x
 *     TEST_ASSERT2(getByte(0xAABBCCDD, 0), 0xDD);
    TEST_ASSERT2(getByte(0xAABBCCDD, 1), 0xCC);
    TEST_ASSERT2(getByte(0xAABBCCDD, 2), 0xBB);
    TEST_ASSERT2(getByte(0xAABBCCDD, 3), 0xAA);

    1 byte = 8 bits

    You are multiplying (8 bits) * ('n' of bytes)


 */

// Swap all bytes in x such that the
// most significant byte becomes the least significant
// byte, and the least significant byte becomes
// the most significant byte, and so on
// See the tests for examples.
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
unsigned long swapBytes(unsigned long x)
{
    return 0;
}


// ******** TWO'S COMPLEMENT **********

// Compute -x without the - operator
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
int negate(int x)
{
    return ~x + 1;
}

/*
 * To get a negative notation of an integer, you write out the number in binary.
 * Then invert the digits and add one to the result.
 *
 * The '~' is used to invert the digits.
 */


// Return true if x >= 0,
// but without using any logical operators
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
int isPositive(int x) //16 bits for int
{
   return (~x >> 15) & 1;
}

/*
* I used bitwise operation AND (&) to set a particular bit because if we do &
* between 0 and any other bit, the results becomes 0
*
*     TEST_ASSERT(isPositive(1));
    TEST_ASSERT(isPositive(32111));
    TEST_ASSERT(!isPositive(-1));
*/


// Compute !x without using the ! operator
// You are limited to straight-line code (similar to bitSet/bitTest),
// no loops or conditionals
//
// ALLOWED OPERATORS:  ! ~ | & ^ + << >> = and casting
// PROHIBITED:  if, for, while, switch, any logical operators like < && ==,
//              calling functions, or floating point math
int bang(int x)
{
    return 0;
}


// ********* LOOPS AND ARRAYS *********

// Given array of values "vals" with size indicated by "num_vals",
// return 1 if all values are >= 21, 0 otherwise
//
// ALLOWED OPERATORS:  All operators and loops
// PROHIBITED:  No library functions
int over21(char *vals, char num_vals)
{
    int i;
    for (i = 0; i < num_vals; i++)
    {
        if (vals[i] < 21){
            return 0;
        }
    }
    return 1;
}

/*
 * Compute the length of the null-terminated
 * string s.  The length returned should NOT
 * count the null-terminator.
 *
 * You may assume that all strings tested have
 * length less than 255.
 *
 * ALLOWED OPERATORS:  All operators and loops
 * PROHIBITED:  No library functions (but you can use your own)
 *
 */
#define STR_MAX 255 // Feel free to use this definition
int strLength(char *s)
{
    int i;
    for (i=0; s[i] != '\0'; ++i);

  return i;
}


/*
 * Implement the "Caesar cipher", which is an ancient
 * example of cryptography.
 * To encode a message, shift all characters in the null-terminated
 * string s by 3 letters.   For example "APPLE" becomes "DSSOH"
 * To do this, use your letterShift function.
 *
 * You may assume that the input is a null-terminated, ASCII
 * string containing only CAPITAL letters.
 *
 * ALLOWED OPERATORS:  All operators and loops
 * PROHIBITED:  No library functions (but you can use your own)
 *
 */
void caesar(char *s)
{
    int i;
    for (i=0; i<=strLength(s)-1; i++)

    {
        s[i] = letterShift(s[i], 3);
    }
}

// ********* FLOATING POINT AND MORE *********

// Compute the integer form of the base-2 log of x
// This is equivalent to floor(log2(x))
// See the tests for some examples
// You may use loops and conditionals for this puzzle.
//
// ALLOWED OPERATORS:  All operators and loops
// PROHIBITED:  No library functions
unsigned int ilog2(unsigned long x)
{
    return 0;
}




// Compute -f
// Assume that f is a number in single-precision IEEE754 format
//
// C does not permit bitwise operators on floats,
// so the input and return type of this function is
// unsigned long to allow you to alter its format
//
// You may use conditionals for this puzzle.
//
// ALLOWED OPERATORS:  All operators and loops
// PROHIBITED:  No library functions (but you can use your own)
unsigned long floatNeg(unsigned long f)
{
    return 0;
}

// Return the single-precision IEEE754 representation of integer x
// You may use conditionals, loops, and your ilog2 function
//
// As above, the return type for this function is unsigned long
// to allow you to manipulate its format
//
// ALLOWED OPERATORS:  All operators and loops
// PROHIBITED:  No library functions (but you can use your own, such as ilog2)
unsigned long i2f(int x)
{
    return 0;
}


