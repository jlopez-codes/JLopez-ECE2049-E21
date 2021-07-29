//*****************************************************************************
//
// ustdlib.c - Simple standard library functions.
//
// Copyright (c) 2007-2013 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 10636 of the Stellaris Firmware Development Package.
//
//*****************************************************************************
#include <string.h>
#include "debug_assert.h"

#ifndef UTILS_USTDLIB_H_
#define UTILS_USTDLIB_H_


//*****************************************************************************
//
//! Copies a certain number of characters from one string to another.
//!
//! \param pcDst is a pointer to the destination buffer into which characters
//!   are to be copied.
//! \param pcSrc is a pointer to the string from which characters are to be
//!   copied.
//! \param iNum is the number of characters to copy to the destination buffer.
//!
//! This function copies at most \e iNum characters from the string pointed to
//! by \e pcSrc into the buffer pointed to by \e pcDst.  If the end of \e
//! pcSrc is found before \e iNum characters have been copied, remaining
//! characters in \e pcDst will be padded with zeroes until \e iNum characters
//! have been written.  Note that the destination string will only be NULL
//! terminated if the number of characters to be copied is greater than the
//! length of \e pcSrc.
//!
//! \return Returns \e pcDst.
//
//*****************************************************************************
unsigned char *
ustrncpy (unsigned char *pcDst, const unsigned char *pcSrc, int iNum);

//*****************************************************************************
//
//! A simple vsnprintf function supporting \%c, \%d, \%p, \%s, \%u, \%x, and
//! \%X.
//!
//! \param pcBuf points to the buffer where the converted string is stored.
//! \param ulSize is the size of the buffer.
//! \param pcString is the format string.
//! \param vaArgP is the list of optional arguments, which depend on the
//! contents of the format string.
//!
//! This function is very similar to the C library <tt>vsnprintf()</tt>
//! function.  Only the following formatting characters are supported:
//!
//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%d, \%i, \%p, \%s, \%u, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeroes instead of spaces.
//!
//! The type of the arguments after \e pcString must match the requirements of
//! the format string.  For example, if an integer was passed where a string
//! was expected, an error of some kind will most likely occur.
//!
//! The \e ulSize parameter limits the number of characters that will be stored
//! in the buffer pointed to by \e pcBuf to prevent the possibility of a buffer
//! overflow.  The buffer size should be large enough to hold the expected
//! converted output string, including the null termination character.
//!
//! The function will return the number of characters that would be converted
//! as if there were no limit on the buffer size.  Therefore it is possible for
//! the function to return a count that is greater than the specified buffer
//! size.  If this happens, it means that the output was truncated.
//!
//! \return Returns the number of characters that were to be stored, not
//! including the NULL termination character, regardless of space in the
//! buffer.
//
//*****************************************************************************
int
uvsnprintf(unsigned char *pcBuf, unsigned long ulSize, const unsigned char *pcString,
           va_list vaArgP);


//*****************************************************************************
//
//! A simple sprintf function supporting \%c, \%d, \%p, \%s, \%u, \%x, and \%X.
//!
//! \param pcBuf is the buffer where the converted string is stored.
//! \param pcString is the format string.
//! \param ... are the optional arguments, which depend on the contents of the
//! format string.
//!
//! This function is very similar to the C library <tt>sprintf()</tt> function.
//! Only the following formatting characters are supported:
//!
//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%d, \%i, \%p, \%s, \%u, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeros instead of spaces.
//!
//! The type of the arguments after \e pcString must match the requirements of
//! the format string.  For example, if an integer was passed where a string
//! was expected, an error of some kind will most likely occur.
//!
//! The caller must ensure that the buffer \e pcBuf is large enough to hold the
//! entire converted string, including the null termination character.
//!
//! \return Returns the count of characters that were written to the output
//! buffer, not including the NULL termination character.
//
//*****************************************************************************
int
usprintf(unsigned char *pcBuf, const unsigned char *pcString, ...);

//*****************************************************************************
//
//! A simple snprintf function supporting \%c, \%d, \%p, \%s, \%u, \%x, and
//! \%X.
//!
//! \param pcBuf is the buffer where the converted string is stored.
//! \param ulSize is the size of the buffer.
//! \param pcString is the format string.
//! \param ... are the optional arguments, which depend on the contents of the
//! format string.
//!
//! This function is very similar to the C library <tt>sprintf()</tt> function.
//! Only the following formatting characters are supported:
//!
//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%d, \%i, \%p, \%s, \%u, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeros instead of spaces.
//!
//! The type of the arguments after \e pcString must match the requirements of
//! the format string.  For example, if an integer was passed where a string
//! was expected, an error of some kind will most likely occur.
//!
//! The function will copy at most \e ulSize - 1 characters into the buffer
//! \e pcBuf.  One space is reserved in the buffer for the null termination
//! character.
//!
//! The function will return the number of characters that would be converted
//! as if there were no limit on the buffer size.  Therefore it is possible for
//! the function to return a count that is greater than the specified buffer
//! size.  If this happens, it means that the output was truncated.
//!
//! \return Returns the number of characters that were to be stored, not
//! including the NULL termination character, regardless of space in the
//! buffer.
//
//*****************************************************************************
int
usnprintf(unsigned char *pcBuf, unsigned long ulSize, const unsigned char *pcString, ...);

//*****************************************************************************
//
//! Converts a string into its numeric equivalent.
//!
//! \param pcStr is a pointer to the string containing the integer.
//! \param ppcStrRet is a pointer that will be set to the first character past
//! the integer in the string.
//! \param iBase is the radix to use for the conversion; can be zero to
//! auto-select the radix or between 2 and 16 to explicitly specify the radix.
//!
//! This function is very similar to the C library <tt>strtoul()</tt> function.
//! It scans a string for the first token (that is, non-white space) and
//! converts the value at that location in the string into an integer value.
//!
//! \return Returns the result of the conversion.
//
//*****************************************************************************
unsigned long
ustrtoul(const unsigned char *pcStr, const unsigned char **ppcStrRet, int iBase);

//*****************************************************************************
//
//! Retruns the length of a null-terminated string.
//!
//! \param pcStr is a pointer to the string whose length is to be found.
//!
//! This function is very similar to the C library <tt>strlen()</tt> function.
//! It determines the length of the null-terminated string passed and returns
//! this to the caller.
//!
//! This implementation assumes that single byte character strings are passed
//! and will return incorrect values if passed some UTF-8 strings.
//!
//! \return Returns the length of the string pointed to by \e pcStr.
//
//*****************************************************************************
int
ustrlen(const unsigned char * pcStr);

//*****************************************************************************
//
//! Finds a substring within a string.
//!
//! \param pcHaystack is a pointer to the string that will be searched.
//! \param pcNeedle is a pointer to the substring that is to be found within
//! \e pcHaystack.
//!
//! This function is very similar to the C library <tt>strstr()</tt> function.
//! It scans a string for the first instance of a given substring and returns
//! a pointer to that substring.  If the substring cannot be found, a NULL
//! pointer is returned.
//!
//! \return Returns a pointer to the first occurrence of \e pcNeedle within
//! \e pcHaystack or NULL if no match is found.
//
//*****************************************************************************
unsigned char *
ustrstr(const unsigned char *pcHaystack, const unsigned char *pcNeedle);

//*****************************************************************************
//
//! Compares two strings without regard to case.
//!
//! \param pcStr1 points to the first string to be compared.
//! \param pcStr2 points to the second string to be compared.
//! \param iCount is the maximum number of characters to compare.
//!
//! This function is very similar to the C library <tt>strnicmp()</tt> function.
//! It compares at most \e iCount characters of two strings without regard to
//! case.  The comparison ends if a terminating NULL character is found in
//! either string before \e iCount characters are compared.  In this case, the
//! shorter string is deemed the lesser.
//!
//! \return Returns 0 if the two strings are equal, -1 if \e pcStr1 is less
//! than \e pcStr2 and 1 if \e pcStr1 is greater than \e pcStr2.
//
//*****************************************************************************
int
ustrnicmp(const unsigned char *pcStr1, const unsigned char *pcStr2, int iCount);

//*****************************************************************************
//
//! Compares two strings without regard to case.
//!
//! \param pcStr1 points to the first string to be compared.
//! \param pcStr2 points to the second string to be compared.
//!
//! This function is very similar to the C library <tt>strcasecmp()</tt>
//! function.  It compares two strings without regard to case.  The comparison
//! ends if a terminating NULL character is found in either string.  In this
//! case, the shorter string is deemed the lesser.
//!
//! \return Returns 0 if the two strings are equal, -1 if \e pcStr1 is less
//! than \e pcStr2 and 1 if \e pcStr1 is greater than \e pcStr2.
//
//*****************************************************************************
int
ustrcasecmp(const unsigned char *pcStr1, const unsigned char *pcStr2);

//*****************************************************************************
//
//! Compares two strings.
//!
//! \param pcStr1 points to the first string to be compared.
//! \param pcStr2 points to the second string to be compared.
//! \param iCount is the maximum number of characters to compare.
//!
//! This function is very similar to the C library <tt>strncmp()</tt> function.
//! It compares at most \e iCount characters of two strings taking case into
//! account.  The comparison ends if a terminating NULL character is found in
//! either string before \e iCount characters are compared.  In this case, the
//! shorter string is deemed the lesser.
//!
//! \return Returns 0 if the two strings are equal, -1 if \e pcStr1 is less
//! than \e pcStr2 and 1 if \e pcStr1 is greater than \e pcStr2.
//
//*****************************************************************************
int
ustrncmp(const unsigned char *pcStr1, const unsigned char *pcStr2, int iCount);

//*****************************************************************************
//
//! Compares two strings.
//!
//! \param pcStr1 points to the first string to be compared.
//! \param pcStr2 points to the second string to be compared.
//!
//! This function is very similar to the C library <tt>strcmp()</tt>
//! function.  It compares two strings, taking case into account.  The
//! comparison ends if a terminating NULL character is found in either string.
//! In this case, the shorter string is deemed the lesser.
//!
//! \return Returns 0 if the two strings are equal, -1 if \e pcStr1 is less
//! than \e pcStr2 and 1 if \e pcStr1 is greater than \e pcStr2.
//
//*****************************************************************************
int
ustrcmp(const unsigned char *pcStr1, const unsigned char *pcStr2);

//*****************************************************************************
//
//! Set the random number generator seed.
//!
//! \param ulSeed is the new seed value to use for the random number generator.
//!
//! This function is very similar to the C library <tt>srand()</tt> function.
//! It will set the seed value used in the <tt>urand()</tt> function.
//!
//! \return None
//
//*****************************************************************************
void
usrand(unsigned long ulSeed);

//*****************************************************************************
//
//! Generate a new (pseudo) random number
//!
//! This function is very similar to the C library <tt>rand()</tt> function.
//! It will generate a pseudo-random number sequence based on the seed value.
//!
//! \return A pseudo-random number will be returned.
//
//*****************************************************************************
int
urand(void);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************



#endif /* UTILS_USTDLIB_H_ */
