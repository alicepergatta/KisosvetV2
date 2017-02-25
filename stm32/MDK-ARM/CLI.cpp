#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>


const char c_return = '\r';
const char n_line = '\n';
const char space_char = ' ';
char parsed_line[200];
char command[20];

char argument1[20];
char argument2[20];
char argument3[20];
char argument4[20];

char *ptr;
char *ptr1;



short parsed_line_length = 0;
short receiveBuffer_length = 0;
short ret_pos;

short testshort; //test
int testint; //test


void ParseCmdString(void);
void CReturnCmd(void);
void substring_cut(void);
void string_wipe(char *stringtowipe);
void SliceCmd(void);
void ClearCmdAndArguments(void);
void GetCommands(void);

void LED_CLI(char *led_num, char *led_en, char *led_pwm);
void LED_SW(void);
int LED_ValuebyNum (int lednum);
int LED_PWMbyNum(int lednum);
int LED_StatebyNum(int lednum);
void PSU_SWITCH(char *arg);
void FAN_SWITCH(char *arg1, char *arg2);
void ESP_UART_alt(void);
void CLI_toogleEcho(void);
void Status(void);
void CliGetTemperature(void);
void char2short(char* pchar, short* pshort);
void char2int(char* pchar, int* pint);
//void GetTemp(void);
void GetTemperature(void);
void FanLogic(char *arg);
void AdcDatahandler(char *arg);


void CReturnCmd(void) { 

if(stringComplete == true) //if we got carrier return we know than string is completed
	{ 
		//ClearCmdAndArguments(); //wipe parsed strings before writing new data
		printf("\n\r"); //Carrier return + newline, for writing new string
		stringComplete = false; //set flag to false
		ClearCmdAndArguments(); //wipe parsed strings before writing new data
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
	memset(receiveBuffer,0,sizeof(receiveBuffer)); //clear secondary(global) receive buffer
	return;
}

void substring_cut(void)
{		
		//memset(parsed_line,0,parsed_line_length + 1); //clear last received string by measured string length
		memset(parsed_line,0,sizeof(parsed_line)); //clear last received string by measured string length
		strncpy(parsed_line, receiveBuffer, strlen(receiveBuffer)); //copy receivedBuffer content to parsed_line content
		parsed_line_length = strlen(parsed_line); //update parsed_line string length
		SliceCmd();
		GetCommands();
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
	return;
}

void SliceCmd(void) //function wich provide cutting seperate words to command and her arguments
{
	short tkn_cnt;
	tkn_cnt = 0; //start from zero
	char *token;
	token = strtok(parsed_line, &space_char); //words are separated by space
	
		 while( token != NULL && tkn_cnt < 5 ) 
   { 
		 switch(tkn_cnt) //write arguments in separate strings by counter value
	{
		case 0:
		//strncpy(command, token, strlen(token) + 1); //copy command part of parsed_line
		strncpy(command, token, strlen(token)); //copy command part of parsed_line
		break;
		case 1:
		//strncpy(argument1, token, strlen(token) + 1);
		strncpy(argument1, token, strlen(token));
		break;
		case 2:
		//strncpy(argument2, token, strlen(token) + 1);
		strncpy(argument2, token, strlen(token));
		break;
		case 3:
		//strncpy(argument3, token, strlen(token) + 1);
		strncpy(argument3, token, strlen(token));
		break;
		case 4:
		//strncpy(argument4, token, strlen(token) + 1);
		strncpy(argument4, token, strlen(token));
		break;
			default:
break;
	}
	tkn_cnt++; //increment counter
	token = strtok(NULL, &space_char);
   } 
	
	return;
}

void ClearCmdAndArguments(void) //function which clears parsed command and arguments strings
{
	memset(command,0,sizeof(command)); //clear command string
	memset(argument1,0,sizeof(argument1)); //clear argument1 string
	memset(argument2,0,sizeof(argument2)); //clear argument1 string
	memset(argument3,0,sizeof(argument3)); //clear argument1 string
	memset(argument4,0,sizeof(argument4)); //clear argument1 string
//	testshort = 0;
//	testint = 0;
	
	return;
}

void GetCommands(void) {
	
		if(strncmp(command, "LED", 3) == 0) {
			LED_CLI(argument1, argument2, argument3);
			}
		if(strncmp(command, "FAN", 3) == 0) { //FAN on\off command
		FAN_SWITCH(argument1, argument2);
			}
		if(strncmp(command, "PSU", 3) == 0) { //PSU on\off command
		PSU_SWITCH(argument1);
			}
		if(strncmp(command, "STATUS", 6) == 0) {
			Status();
			}
		if(strncmp(command, "uart_alt", 8) == 0) {
			ESP_UART_alt();
			}
		if(strncmp(command, "toogleEcho", 10) == 0) {
			CLI_toogleEcho();
			}
		if(strncmp(command, "gettemp", 7) == 0) {
			CliGetTemperature();
			}
		if(strncmp(command, "fanlogic", 8) == 0) {
			FanLogic(argument1);
			}
		if(strncmp(command, "getadcdata", 8) == 0) {
			AdcDatahandler(argument1);
			}
		
//		else {
//			printf("Uknown command \n\r"); //Carrier return + newlin,
//		}
			
}


void char2short(char* pchar, short* pshort) //char to short conversion function
{
	*pshort = strtol(pchar, NULL, 10);

}

void char2int(char* pchar, int* pint) //char to int conversion function
{
	*pint = strtol(pchar, NULL, 10);

}

void Status(void) {
//	LED_ValuebyNum(1);
// LED_PWMbyNum(int lednum);
// LED_StatebyNum(int lednum);
	printf(" \n\r");
	printf("LED1: %d ", LED_ValuebyNum(1));
	printf("PWM: %d \t", LED_PWMbyNum(1));
	printf("State: %d \t", LED_StatebyNum(1));
	printf(" \n\r");
	printf("LED2: %d ", LED_ValuebyNum(2));
	printf("PWM: %d \t", LED_PWMbyNum(2));
	printf("State: %d \t", LED_StatebyNum(2));
	printf(" \n\r");
	printf("LED3: %d ", LED_ValuebyNum(3));
	printf("PWM: %d \t", LED_PWMbyNum(3));
	printf("State: %d \t", LED_StatebyNum(3));
	printf(" \n\r");
	printf("LED4: %d ", LED_ValuebyNum(4));
	printf("PWM: %d \t", LED_PWMbyNum(4));
	printf("State: %d \t", LED_StatebyNum(4));
	printf(" \n\r");
	printf("PSU: %d \t", PS_ON);
	printf(" \n\r");
	printf("FAN: %d \t", FAN_EN); 
	printf("  PWM: %i \t", FAN_PWM); 
	printf(" \n\r");
	printf("Current LED's temperature: %d C \t", LedsTemperature);
	printf("  Last: %i C \t", OldLedsTemperature); 
	printf(" \n\r");
	printf("Input Voltage: %f \n\r", DeviceInputVoltage);
	printf("BAT Voltage: %f \n\r", BackupBatVoltage);
	printf(" \n\r");
}

void ESP_UART_alt(void) { //switch UART pins on ESP8266, for debug
	
	//printf(" \n\r");
	printf("uart_alt ");
}

void CLI_toogleEcho(void) { //switch CLI ECHO
	switch (L_ECHO) 
	{
		case 1:
	L_ECHO = 0; 
	printf("CLI ECHO is OFF \n\r");
	break;
		case 0:
	L_ECHO = 1;
	printf("CLI ECHO is ON \n\r");
	break;
		default:
	break;
		}
}



