/*************************************************************************
MODULE:    simulate pump state vibration
CONTAINS:  
COPYRIGHT: 
VERSION:   
--------------------------------------------------------------------------
$LastChangedDate: 
$LastChangedRevision: 
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#define __USE_XOPEN 
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <fcntl.h>

/*----------------------- MACROS -----------------------------------*/
#define _GNU_SOURCE

/*----------------------- typedef -----------------------------------*/
typedef unsigned char uint8_t;

typedef enum { false, true } boolean;

/*----------------------- Variables -----------------------------------*/
char line_buf[700];  
FILE *ascii_file;                   /* Files: binary file  */
FILE *binary_file;
char dumpFileName[700];  

/*----------------------- Functions -----------------------------------*/
const char* getfield(char* line, int num, char* separator);
boolean readln(
  FILE * fptr,                  // Handle to open ASCII file - read access
  char *linestr                 // Pointer to string variable to hold text line
);
void delay(int number_of_seconds);

void replaceCharInLine(char * pString, char toFind, char toReplace);
char *strremove(char *str, const char *sub);



/******************************************************
DESC:        Main function
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
int main
(
  int argc,                     // Counter for number of commandline parameters
  const char *argv[]            // Array of pointers to commandline option strings
)
{
	if (argc < 2)  // at least 1 argument
	{	
		printf("\r\n Incorrect argument!");
		printf("\r\n Correct example: ./convert_ascii_to_float ./seed.tinn");
		printf("\r\n");
		exit(EXIT_SUCCESS);         /* End program: Success */
	}
		
	if ((ascii_file = fopen(argv[1], "r")) == NULL) 
	{printf("\n\r %s is missing\n", argv[1]); exit(EXIT_FAILURE);}
	else
	{printf("\n\r %s is opened\n\r", argv[1]);}
		
		
	strcpy(dumpFileName, argv[1]);	
	replaceCharInLine(dumpFileName, '/', '_');
	replaceCharInLine(dumpFileName, '.', '_');
	
	char *pTrimmed = strremove(dumpFileName, "tinn");
	pTrimmed = strremove(pTrimmed, "_");
  

	strcat(pTrimmed, ".bin");
	binary_file = fopen(pTrimmed,"w+");
		
		
		
	if ((ascii_file = fopen(argv[1], "r")) == NULL) 
	{printf("\n\r %s is missing\n", argv[1]); exit(EXIT_FAILURE);}
	else
	{printf("\n\r %s is opened\n\r", argv[1]);}	
		
		
		
	float data;	
	
	readln(ascii_file, line_buf); // to skip header
	while (readln(ascii_file, line_buf)) 
	{  
		//printf("\r\n %s", line_buf);
		sscanf( line_buf, "%f\n", &data);
		//printf("	%f", data);
		
		fwrite( &data, 1, sizeof(float), binary_file ); // little endian
	
		delay(6);	

	}
	
	
	
	
	
	fclose(ascii_file);
	fclose(binary_file);
	printf("\r\n");
	return 0;
}                               


/******************************************************
DESC:        Removes leading and trailing spaces from a string
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
void delspc(
  char *what                    // Pointer to string to be treated
)
{
  int i;
  char *hilf_beg, *hilf_end;

  hilf_beg = what;
  hilf_end = what + strlen(what) - 1;
  while ((*hilf_beg == ' ') && (*hilf_beg != '\0'))
    ++hilf_beg;
  while ((*hilf_end == ' ') && (hilf_end > what))
    --hilf_end;
  for (i = 0; hilf_beg <= hilf_end; i++, hilf_beg++)
    *(what + i) = *hilf_beg;
  *(what + i) = '\0';
}

/******************************************************
DESC:        Copies a number of characters and terminates
             the destination string with '\0'
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
void getstr(
  char *deststr,                // Destination string - pointer to address to be copied to
  const char *memstr,           // Source string - pointer to address from which to copy
  int cnt                       // Number of characters to copy
)
{
  int zl;

  for (zl = 0; zl < cnt; ++deststr, ++memstr, ++zl)
    *deststr = *memstr;
  *deststr = '\0';
}

/******************************************************
DESC:        
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
unsigned int checkFileLines(char *argv )
{
	FILE *fp;
	char filename[64];
  int count = 0;
	char c;

	strcpy(filename, argv);
	fp = fopen(filename, "r");

  for (c = getc(fp); c != EOF; c = getc(fp))
      if (c == '\n') // Increment count if this character is newline
          count = count + 1;

  fclose(fp);
	return count;
}


/******************************************************
DESC:        
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
boolean readln(
  FILE * fptr,                  // Handle to open ASCII file - read access
  char *linestr                 // Pointer to string variable to hold text line
)
{
  char ch = 0;

  while (((ch = getc(fptr)) != '\n') && (!feof(fptr)))
    *(linestr++) = ch;
  *linestr = '\0';
  
  return (!feof(fptr) || (ch == '\n'));
}

/******************************************************
DESC:        
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}


/******************************************************
DESC:        to remove the specific char in a string
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
void replaceCharInLine(char * pString, char toFind, char toReplace)
{
  unsigned int  i;

  for(i=0;pString[i];i++)
	{  
		if(pString[i]==toFind)
		{
		   pString[i]=toReplace;
	   }
 	}
}

/******************************************************
DESC:        	to remove the string after a specific char
GLOBALS:     _
ASSUMPTIONS: _
HISTORY:     _
LIMITATIONS: _
*******************************************************/
char *strremove(char *str, const char *sub) 
{
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}
