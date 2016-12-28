#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>

//extern char receiveBuffer[228];
//extern short receiveBuffer_cnt;
char c_return = '\r';


void ParseCmdString(void);
void CReturnCmd(void);

void CReturnCmd(void) {

if(stringComplete == true) {
	printf("\n\r"); //Carrier return + newline
	stringComplete = false; //set to false
	ParseCmdString(); //call function
	}
}

void ParseCmdString(void) {
	//printf("Your bunny wrote! \n\r"); //debug
	
}
