#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> /* provides EXIT_SUCCESS */

#define DEBUG 1
#define MAP_LENGTH 28

enum cipherModeEnum {ENCRYPT, DECRYPT};
enum cipherModeEnum cipherMode;

unsigned long lcg_c;
unsigned long lcg_m;
unsigned long lcg_a;
unsigned long lcg_x;

int status;
const int CLEAR = 0;
const int OK = 1;
const int END_OF_LINE = 2;
const int END_OF_FILE = 4;
const int ERROR = 8;

long productOfUniquePrimeFactors(unsigned long n)
{
	long test = 2;
	long product = 1;
	while (test <= n)
	{
		if (n % test == 0)
		{
			product *= test;
			 while(n % test == 0)
			 {
				n /= test;
			 }	
		}
		test++;
	}
	return product;
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
	char c;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
	if (c == '\n')
	{
		status = END_OF_LINE;
	}
	if (c == EOF)
	{
		status = END_OF_FILE;
	}
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
	int i, j;
	char c;
	for(i = 0; i <= 4; i++)
	{
		data[i] = '\0';
	}

	if (cipherMode == ENCRYPT)
	{
		for(j = 0; j < 4; j++) 
		{
			c = getchar();
			if ((c < 32 || c > 126) && c != '\n')
			{
				return ERROR;
			}
			if (c == EOF)
			{
				return END_OF_FILE;
			}
			if (c == '\n')
			{
				return END_OF_LINE;
			}
			else 
			{
				data[j] = c;
			}
		}
		return OK;
	}
	else 
	{
		return ERROR;
	}

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
  	char c = getchar();
  	if (c == 'e')
  	{
  		cipherMode = ENCRYPT;
  		return OK;
  	}
  	if (c == 'd')
  	{
  		cipherMode = DECRYPT;
  		return OK;
  	}
  	if (c == '\n')
  	{
  		return END_OF_LINE;
  	}
  	if (c == EOF)
  	{
  		return END_OF_FILE;
  	}
  	else return ERROR;
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
  long p = productOfUniquePrimeFactors(LCG_m);
  if (LCG_m % 4 == 0)
  {
  	lcg_a = 1+2*p;
  }
  else 
  {
  	lcg_a = 1+p;
  }
  if (0 < lcg_a < lcg_m)
  {
  	return lcg_a;
  }
  else 
  {
  	return 0;
  }
}

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
unsigned long getLongfromString(char *number)
{
  unsigned long n = strtol(number, NULL, 10);
  return n;
}

unsigned long readPositiveLong(char delimiter)
{ 
	int max = 0;
	char temp[20];
	int i = 0;
	unsigned long n = 0;

	char c = getchar();
	while (c != ',')
	{
		if (max > 20)
		{
			return 0;
		}
		if (c >= '0' && c <= '9')
		{
			temp[i] = c;
			i++;
			max++;
		}
		else 
		{
			return 0;
		}
		c=getchar();
	}
	return n = getLongfromString(temp);  
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
	char delimiter = ',';
	lcg_m = readPositiveLong(delimiter);
	lcg_c = readPositiveLong(delimiter);
	lcg_a = calculateLCG_a(lcg_m);

	lcg_x = lcg_c;

  	return OK;
}


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
      status = readDataBlock(data);
      if (DEBUG) printf("\treadDataBlock::data=%s status=%d\n",data,status);
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