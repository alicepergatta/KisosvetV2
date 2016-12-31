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
char n_line = '\n';
char parsed_line[200];
short parsed_line_length = 0;
short receiveBuffer_length = 0;
char *pisos = receiveBuffer;

void ParseCmdString(void);
void CReturnCmd(void);

void CReturnCmd(void) {

if(stringComplete == true) {
	printf("\n\r"); //Carrier return + newline
	stringComplete = false; //set to false
	startNewLine = true;
	ParseCmdString(); //call function
	}
}

void ParseCmdString(void) {
	receiveBuffer_length = strlen(receiveBuffer);
	parsed_line_length = strlen(parsed_line);
//parsed_line = 
		 //printf( "%i \n\r", receiveBuffer_length);
		startNewLine = false;
}
