/*
 * lab0.h
 *
 *  Created on: Apr 10, 2018
 *      Author: deemer
 */

#ifndef PUZZLES_H_
#define PUZZLES_H_

// Warmup
int linear(int x);
int gt20(int a, int b);

// Bit-twiddling
int setBit(int x, int b);
int clearBit(int x, int b);
int divpwr2(int x, int n);
int bitCount(char x);

// Byte manipulation
char getByte(long x, int n);
unsigned long swapBytes(unsigned long x);

// Two's complement
int negate(int x);
int isPositive(int x);

// ASCII and Logical operators
int myMax(int a, int b);
int clamp(int x, int lower, int upper);
int isLetter(char x);
char letterShift(char c, int shift);

// Loops, Characters and Arrays
char average(char *vals, char num_vals);
int over21(char *vals, char num_vals);
int strLength(char *s);
void caesar(char *s);

// Extra puzzles
int bang(int x);
unsigned int ilog2(unsigned long x);
unsigned long floatNeg(unsigned long f);
unsigned long i2f(int x);



#endif /* PUZZLES_H_ */
