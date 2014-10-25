/***********************************************************************/
/* Program: Cipher program template                                    */
/* Course:  CS241                                                      */
/* Original Author: Joel Castellanos                                   */
/* Updates by Brooke Chenoweth                                         */
/*                                                                     */
/* Updated 2013-10-8: Better comment format (M-x comment-box is neat!) */
/*                    Fix some spelling errors that were bothering me. */
/* Updated 2013-10-23: Fix a couple more typos.                        */
/***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* provides EXIT_SUCCESS */

#define DEBUG 0
#define MAP_LENGTH 28

enum cipherModeEnum {ENCRYPT, DECRYPT};
enum cipherModeEnum cipherMode;

/*
The different status codes are flags.
Since each is a power of 2, they can be turned on or off independently.
*/
int status;
const int CLEAR = 0;
const int OK = 1;
const int END_OF_LINE = 2;
const int END_OF_FILE = 4;
const int ERROR = 8;

unsigned long lcg_c;
unsigned long lcg_m;
unsigned long lcg_a;
unsigned long lcg_x;
int cipherMap[MAP_LENGTH];



/******************************************************************************/
/* readPositiveLong(char delimiter)                                           */
/*   Reads characters from the standard input stream until either             */
/*   the character read equals the delimiter or until an error.               */
/*                                                                            */
/*   This is a reusable utility function.                                     */
/*   It does not access any global variables.                                 */
/*   It can be moved to a different file.                                     */
/*                                                                            */
/*   An error occurs if:                                                      */
/*    1) A character is read that is not a digit (0-9) and not the delimiter. */
/*    2) More than 20 digits are read                                         */
/*    3) The compiler's representation of an unsigned long is <64 bits.       */
/*                                                                            */
/*   Returns                                                                  */
/*    If no error, returns an unsigned long defined by the digits read.       */
/*    If an error, returns 0.                                                 */
/******************************************************************************/
unsigned long readPositiveLong(char delimiter)
{ 
  return 0;
}


/**********************************************************************/
/*  setUniquePrimeFactors                                             */
/*    This is a reusable utility function.                            */
/*    It does not access any global variables.                        */
/*    It can be moved to a different file.                            */
/*                                                                    */
/* Parameters:                                                        */
/*    n:         Number of which the unique prime factors are found.  */
/*    prime[]:   pointer to output array of unique prime numbers.     */
/*                  Each element of prime[] from 0 to maxPrimes-1 is  */
/*                  initialized to 0.                                 */
/*    maxPrimes: Size of prime[] array.                               */
/*                                                                    */
/* Returns:                                                           */
/*    The number of unique prime factors placed in prime[].           */
/*    0 if there is an error.                                         */
/**********************************************************************/
int setUniquePrimeFactors(unsigned long n, int prime[], int maxPrimes)
{ 
  return 0;
}


/********************************************************************************/
/*  calculateLCG_a(unsigned long LCG_m)                                         */
/*    Given m of a Linear Congruential Generator (LCG): Xn+1 = (aXn + c) mod m  */
/*      This method finds an a that will yield a full period.                   */
/*      The value of a is:                                                      */
/*        a = 1+2p, if 4 is a factor of m, otherwise, a = 1+p.                  */
/*        p = (product of m's unique prime factors).                            */
/*        0 < a < m (otherwise error).                                          */
/*                                                                              */
/*    This is a reusable utility function.                                      */
/*    It does not access any global variables.                                  */
/*    It can be moved to a different file.                                      */
/*                                                                              */
/* Parameters:                                                                  */
/*    LCG_m:     m of an LCG.                                                   */
/*                                                                              */
/* Returns:                                                                     */
/*    a of the LCG or 0 if there was an error.                                  */
/********************************************************************************/
unsigned long calculateLCG_a(unsigned long LCG_m)
{
  return 0;
}


/**********************************************************************/
/* skipToEndOfLine(void)                                              */
/* Helper function that reads characters from the                     */
/* standard input stream (stdin) until '\n' or EOF.                   */
/*                                                                    */
/* None of the characters read are saved.                             */
/*                                                                    */
/* If '\n' is read, sets the END_OF_LINE flag of global field status. */
/* If EOF is read, sets the END_OF_FILE flag of global field status.  */
/**********************************************************************/
void skipToEndOfLine(void)
{
}


/******************************************************************************/
/*  readDataBlock(char data[])                                                */
/*    Reads one block of cipher data from the standard input stream.          */
/*    Reading stops when a full block is read or when '\n' is read.           */
/*    An error is triggered if any byte code (other than '\n') is read        */
/*      that is not a printable ASCII character: [32, 126].                   */
/*                                                                            */
/* Parameters:                                                                */
/*    data[]: a null-terminated array of size 5 into which the data is read.  */
/*      All elements of data are initialized to '\0'.                         */
/*      If global variable cipherMode == ENCRYPT, then each legal character   */
/*        read is copied into data[].                                         */
/*      If global variable cipherMode == DECRYPT, then character codes [0,31] */
/*        and 127 might be represented as two-byte codes starting with '*'.   */
/*      This function converts any such two-character codes to the single     */
/*        ASCII code [0,127]. Therefore, this function may read as many as    */
/*        eight characters form the standard input stream.                    */
/*                                                                            */
/* Returns:                                                                   */
/*   OK | END_OF_LINE | END_OF_FILE | ERROR                                   */
/******************************************************************************/
int readDataBlock(char data[])
{ 
  return OK;
}


/***********************************************************************/
/* readCipherMode(void)                                                */
/*   Reads one character from the standard input stream.               */
/*   Sets the global variable cipherMode to ENCRYPT or DECRYPT if the  */
/*     character read is an 'e' or a 'd'.                              */
/*                                                                     */
/* Returns:                                                            */
/*   OK if an 'e' or 'd' was read.                                     */
/*   END_OF_LINE if '\n' was read.                                     */
/*   END_OF_FILE if EOF was read.                                      */
/*   otherwise ERROR.                                                  */
/***********************************************************************/
int readCipherMode(void)
{ 
  return OK;
}

/****************************************************************/
/* readKey(void)                                                */
/*                                                              */
/*   Calls readPositiveLong and sets the global variable lcg_m. */
/*   Calls readPositiveLong and sets the global variable lcg_c. */
/*   Calls calculateLCG_a and sets the global variable lcg_a.   */
/*   Sets the global variable lcg_x.                            */
/*                                                              */
/* Return: OK | ERROR                                           */
/****************************************************************/
int readKey(void)
{  
  return OK;
}


/***************************************************************************/
/* buildMap(void)                                                          */
/*                                                                         */
/* Uses the global variables lcg_a, lcg_c, lcg_m and lcg_x to define the   */
/*   global array: cipherMap[] such that cipherMap[i] = k indicates that   */
/*   on encryption, bit i is moved to bit k and the reverse on decryption. */
/*                                                                         */
/* When this function returns, lcg_x will have been updated 28 steps       */
/*   in the LCG.                                                           */
/*                                                                         */
/* This method does not return a value because there is no reason for it   */
/*   to fail.                                                              */
/***************************************************************************/
void buildMap(void)
{ 
}


/*****************************************************************************/
/* encrypt(char data[])                                                      */
/*   Uses the global variable cipherMap to encrypt the data block in data[]. */
/*   The encrypted data is sent to the standard output stream.               */
/*   The encrypted data will always be 4 to 8 bytes long.                    */
/*   Encrypted byte codes [0,31], 127 and '*' are converted to 2-byte        */
/*     printable ASCII characters.                                           */
/*                                                                           */
/* Parameters: data[]: Must be a null terminated char[] of size 5.           */
/*                                                                           */
/* Return: OK | ERROR                                                        */
/*****************************************************************************/
int encrypt(char data[])
{ 
  return OK;
}



/********************************************************************************/
/* decrypt(char data[])                                                         */
/*   Uses the global variable cipherMap to decrypt the data block in data[].    */
/*   The decrypted data is sent to the standard output stream.                  */
/*   The decrypted data will always be 1 to 4 bytes long.                       */
/*   If a decrypted character is '\0' it means that the data block was a        */
/*     parcial block from the end of the line. '\0' characters are not printed. */
/*   Any other decrypted byte that is not a printable ASCII character is an     */
/*     error.                                                                   */
/*                                                                              */
/* Parameters: data[]: Must be a null terminated char[] of size 5.              */
/*                                                                              */
/* Return: OK | ERROR                                                           */
/********************************************************************************/
int decrypt(char data[])
{ 
  return OK;
}

/*****************************************************************/
/* main encrypts and decrypts lines until end of file is reached */
/*****************************************************************/
int main()
{ 

  int inputLineNumber = 0;
  status = CLEAR;

  char data[5];
  data[4] = '\0';

  while (status != END_OF_FILE)
  {
    status = CLEAR;
    inputLineNumber++;

    status = readCipherMode();
    if (DEBUG) printf("readCipherMode::mode=%d status=%d\n",cipherMode,status);

    if ((status & END_OF_FILE) == 0) 
    { 
      printf("%5d) ", inputLineNumber);
    }
    if (status == OK)
    { 
      status = readKey();
      if (DEBUG)
      { 
        printf ("\tKey: m=%lu c=%lu a=%lu x=%lu status=%d\n", 
          lcg_m, lcg_c, lcg_a, lcg_x, status);
      }
    }

    while (status == OK) 
    {
      buildMap();
      status = readDataBlock(data);
      if (DEBUG) printf("\treadDataBlock::data=%s status=%d\n",data,status);
      if ((status & ERROR) == 0)
      { 
        if (cipherMode == ENCRYPT) status |= encrypt(data);
        else status |= decrypt(data);
      }
    }
    
    if (status & ERROR)
    { 
      puts("Error");
      skipToEndOfLine();
    }
    else puts("");
  }
  return EXIT_SUCCESS;
}
