/*
 * lab0_tests.c - Tests for lab 0 programming puzzles
 *
 *  Created on: Apr 19, 2018
 *      Author: deemer
 *  Updated 17 May 2018
 */
#include <msp430.h>
#include <puzzle_tests.h>
#include <puzzles.h>
#include <string.h>


// Prototypes
void test_linear(void);
void test_gt20(void);
void test_setBit(void);
void test_clearBit(void);
void test_bitCount(void);
void test_divpwr2(void);
void test_negate(void);
void test_isPositive(void);
void test_swapBytes(void);
void test_myMax(void);
void test_clamp(void);
void test_isLetter(void);
void test_average(void);
void test_over21(void);
void test_strLength(void);
void test_letterShift(void);
void test_caesar(void);
void test_i2f(void);
void test_bang(void);
void test_float_neg(void);
void test_ilog2(void);

unsigned long fake_f2i(float f);
float fake_i2f(unsigned long i);

void test_getByte(void);


/*
 * ***** Run all tests ******
 * To implement each puzzle, write your implementation
 * in the corresponding function in puzzles.c.
 *
 * As you start each puzzle,
 * BE SURE TO UNCOMMENT the corresponding
 * tests here to check your work!
 *
 * ***NOTE***: YOU MAY NOT BE REQUIRED TO COMPLETE ALL OF THE
 * PUZZLES LISTED HERE.  SEE YOUR LAB DOCUMENT FOR DETAILS
 * ON WHICH ARE REQUIRED AND WHICH MAY BE EXTRA CREDIT.
 */

void test_all_puzzles(void)
{
      test_linear();
      test_gt20();

      test_clamp();
      test_isLetter();
      test_letterShift();  //help

      test_setBit();
      test_clearBit();
//    test_bitCount();
      test_divpwr2();
      test_getByte();
//    test_swapBytes();
//
      test_isPositive();   // help
      test_negate();
//
      test_over21();
      test_strLength();
      test_caesar();        //do tomorrow morning
//
//    test_bang();
//    test_float_neg();
//    test_i2f();
//    test_ilog2();
}

/* ************* TESTS *************** */

void test_linear(void)
{
    TEST_ASSERT2(linear(0), 4);
    TEST_ASSERT2(linear(1), 6);
    TEST_ASSERT2(linear(-10), -16);
    TEST_ASSERT2(linear(20), 44);
}

void test_gt20(void)
{
    TEST_ASSERT2(gt20(0, 1), 0);
    TEST_ASSERT2(gt20(20, 21), 0);
    TEST_ASSERT2(gt20(42, 145), 1);
}

void test_setBit(void)
{
    TEST_ASSERT2(setBit(0, 0), 0x01);
    TEST_ASSERT2(setBit(0x4444, 15), 0xC444);
    TEST_ASSERT2(setBit(0xFFFF, 2), 0xFFFF);
    TEST_ASSERT2(setBit(0x52, 2), 0x56);
}

void test_clearBit(void)
{
    TEST_ASSERT2(clearBit(0, 0),  0);
    TEST_ASSERT2(clearBit(0xFFFF, 0), 0xFFFE);
    TEST_ASSERT2(clearBit(0x2255, 4), 0x2245);
    TEST_ASSERT2(clearBit(0x5555, 7), 0x5555);
}

void test_bitCount(void)
{
    TEST_ASSERT2(bitCount(0), 0);
    TEST_ASSERT2(bitCount(1), 1);
    TEST_ASSERT2(bitCount(0xff), 8);
    TEST_ASSERT2(bitCount(0xA5), 4);
}


void test_divpwr2(void)
{
    TEST_ASSERT2(divpwr2(0, 4), 0);
    TEST_ASSERT2(divpwr2(16, 2), 4);
    TEST_ASSERT2(divpwr2(-1024, 10), -1);
}

void test_negate(void)
{
    TEST_ASSERT2(negate(0), 0);
    TEST_ASSERT2(negate(1), -1);
    TEST_ASSERT2(negate(-1), 1);
    TEST_ASSERT2(negate(-31224), 31224);
}

void test_isPositive(void)
{
    TEST_ASSERT(isPositive(0));
    TEST_ASSERT(isPositive(1));
    TEST_ASSERT(isPositive(32111));
    TEST_ASSERT(!isPositive(-1));
    TEST_ASSERT(!isPositive(-32111));
}


void test_getByte(void)
{
    TEST_ASSERT2(getByte(0xAABBCCDD, 0), 0xDD);
    TEST_ASSERT2(getByte(0xAABBCCDD, 1), 0xCC);
    TEST_ASSERT2(getByte(0xAABBCCDD, 2), 0xBB);
    TEST_ASSERT2(getByte(0xAABBCCDD, 3), 0xAA);
}


void test_swapBytes(void)
{
    TEST_ASSERT2(swapBytes(0xDEADBEEF), 0xEFBEADDE);
    TEST_ASSERT2(swapBytes(0xAABBCCDD), 0xDDCCBBAA);
}

void test_myMax(void)
{
    TEST_ASSERT2(myMax(0, 1), 1);
    TEST_ASSERT2(myMax(5, 5), 5);
    TEST_ASSERT2(myMax(-1, 1), 1);
    TEST_ASSERT2(myMax(-10, -1), -1);
}

void test_clamp(void)
{
    TEST_ASSERT2(clamp(5, 0, 10), 5);
    TEST_ASSERT2(clamp(-10, 0, 10), 0);
    TEST_ASSERT2(clamp(150, 0, 100), 100);
    TEST_ASSERT2(clamp(12, -10, 10), 10);
}


void test_isLetter(void)
{
    TEST_ASSERT(isLetter('A'));
    TEST_ASSERT(isLetter('g'));
    TEST_ASSERT(isLetter('z'));
    TEST_ASSERT(isLetter('Z'));
    TEST_ASSERT(!isLetter('0'));
    TEST_ASSERT(!isLetter(';'));
    TEST_ASSERT(!isLetter(0x00));
}


void test_average(void)
{
    char v1[2] = {0, 10};
    TEST_ASSERT2(average(v1, 2), 5);

    char v2[6] = {100, 90, 90, 76, 85, 90};
    TEST_ASSERT2(average(v2, 6), 88);
}

void test_over21(void)
{
    char v1[4] = {5, 10, 20, 19};
    TEST_ASSERT2(over21(v1, 4), 0);

    char v2[4] = {5, 10, 20, 24};
    TEST_ASSERT2(over21(v2, 4), 0);

    char v3[6] = {25, 40, 30, 21, 32, 54};
    TEST_ASSERT2(over21(v3, 6), 1);
}

void test_strLength(void)
{
    TEST_ASSERT2(strLength(""), 0);
    TEST_ASSERT2(strLength("a"), 1);
    TEST_ASSERT2(strLength("abcd"), 4);
    TEST_ASSERT2(strLength("Hello world!"), 12);
}

void test_letterShift(void)
{
    TEST_ASSERT2(letterShift('A', 0), 'A');
    TEST_ASSERT2(letterShift('D', 3), 'G');
    TEST_ASSERT2(letterShift('W', 7), 'D');
    TEST_ASSERT2(letterShift('A', 26), 'A');
}

#define STR_MAX 30 // None of the test strings are longer than 30
                   // bytes.  Important to compare up to a maximum
                   // value in case the function being tested does
                   // not null-terminate its output
void test_caesar(void)
{
    char s1[5] = "ABCD"; // 4 chars + 1 for null terminator
    caesar(s1);
    TEST_ASSERT(!strncmp(s1, "DEFG", STR_MAX));

    char s2[5] = "WXYZ";
    caesar(s2);
    TEST_ASSERT(!strncmp(s2, "ZABC", STR_MAX));

    char s3[6] = "APPLE";
    caesar(s3);
    TEST_ASSERT(!strncmp(s3, "DSSOH", STR_MAX));

    // This is another way to declare a string, which has
    // exactly the same result as above
    char s4[3] = {'L', 'V', '\0'};
    caesar(s4);
    TEST_ASSERT(!strncmp(s4, "OY", STR_MAX));
}




void test_ilog2(void)
{
    TEST_ASSERT2(ilog2(1), 0);
    TEST_ASSERT2(ilog2(4), 2);
    TEST_ASSERT2(ilog2(5), 2);
    TEST_ASSERT2(ilog2(16), 4);
    TEST_ASSERT2(ilog2(25), 4);
    TEST_ASSERT2(ilog2(1025), 10);
    TEST_ASSERT2(ilog2(32000), 14);
}

void test_bang(void)
{
    TEST_ASSERT2(bang(1), 0);
    TEST_ASSERT2(bang(0xffff), 0);
    TEST_ASSERT2(bang(0xBEEF), 0);
    TEST_ASSERT(bang(0));
}


void test_float_neg(void)
{
    TEST_ASSERT2(floatNeg(fake_f2i(3.0)),
                 fake_f2i(-3.0));
    TEST_ASSERT2(floatNeg(fake_f2i(-1142.5124)),
                 fake_f2i(1142.5124));
    TEST_ASSERT2(floatNeg(fake_f2i(1e-5)),
                 fake_f2i(-1e-5));
}



void test_i2f(void)
{
    TEST_ASSERT2(i2f(42),     fake_f2i(42.0f));
    TEST_ASSERT2(i2f(-42),    fake_f2i(-42.0f));
    TEST_ASSERT2(i2f(11345),  fake_f2i(11345));
    TEST_ASSERT2(i2f(-32768), fake_f2i(-32768));
    TEST_ASSERT2(i2f(0),      fake_f2i(0));
}

/*
 * Return a 32-bit value containing
 * the floating point representation of f.
 *
 * The purpose of this function is to allow us
 * to manipulate raw floating point values for demonstration
 * purposes--this is not a good idea in practice!
 */
unsigned long fake_f2i(float f)
{
    unsigned long i = * ((unsigned long *) &f);

    return i;
}

/*
 * Return a float given by the single-precision
 * representation in i.
 *
 * The purpose of this function is to allow us to
 * manipulate raw floating point values for demonstration
 * purposes--this is not a good idea in practice!
 */
float fake_i2f(unsigned long i)
{
    float f = *((float *) &i);

    return f;
}
