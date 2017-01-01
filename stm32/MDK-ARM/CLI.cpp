#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>

//extern char receiveBuffer[228];
//extern short receiveBuffer_cnt;
const char c_return = '\r';
const char n_line = '\n';
const char space_char = ' ';
char parsed_line[200];
char command[20];

char argument1[20];
char argument2[20];

char *ptr;
char *ptr1;



short parsed_line_length = 0;
short receiveBuffer_length = 0;
short ret_pos;


void ParseCmdString(void);
void CReturnCmd(void);
void substring_cut(void);
void string_wipe(char *stringtowipe);


void CReturnCmd(void) { 

if(stringComplete == true) //if we got carrier return we know than string is completed
	{ 
		ret_pos = receiveBuffer_cnt; //carrier return will be a last string element
		printf("\n\r"); //Carrier return + newline, for writing new string
		stringComplete = false; //set flag to false
		ParseCmdString(); //call function which parses received string
	}
	return;
}

void ParseCmdString(void) {
	receiveBuffer_length = strlen(receiveBuffer);
	parsed_line_length = strlen(parsed_line);
	ptr = strrchr(receiveBuffer, '\r'); //find carrier return and replace to null-terminating character
	if (ptr != NULL) {
    //*ptr = ' ';
		*ptr = '\0';
 }
	substring_cut(); //call function which parses received text to command and arguments
	memset(receiveBuffer,0,receiveBuffer_cnt); //clear secondary(global) receive buffer
	return;
}

void substring_cut(void)
{		
		memset(parsed_line,0,parsed_line_length); //clear last received string by measured string length
		strncpy(parsed_line, receiveBuffer, strlen(receiveBuffer)); //copy receivedBuffer content to parsed_line content
		parsed_line_length = strlen(parsed_line); //update parsed_line string length
 		memset(command,0,sizeof(command)); //clear command string
		strncpy(command, parsed_line, parsed_line_length + 1); //copy command part of parsed_line
		
		return;
}


void string_wipe(char *stringtowipe)
{ 
	//char stringtowipe;
	short string_length = ret_pos;
	short i;
	for (i=0; i < string_length; i++)
{
  stringtowipe[i] = 0;
}
	return;;
}
