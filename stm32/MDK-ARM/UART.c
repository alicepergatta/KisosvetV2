#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal_uart.h"
#include "UART.h"


static UART_HandleTypeDef huart3;

char new_receive_data[128];
char str[128];
char chr;
char cmd_name;
char *prompt = "\r\n> ";
char *greeting = "Nya Kawai! \r\n> ";

	//Send one char function, if UART is ready
void UART_Send(char chr) {
	while(1)
		HAL_UART_Transmit_IT(&huart3, &chr, 1);
}

	//Send string, char by char
void UART_Send_String(char* str) {	
short i = 0;
while (str[i])	
	UART_Send(str[i++]);
}

void UART_Receive() {
	uint32_t tmp_flag = 0;
	tmp_flag =(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE));
	if (tmp_flag != RESET)
    {
	HAL_UART_Receive_IT(&huart3, new_receive_data, 128);
    }
	}
	
 //void UART_Send_String(char *greeting);

 //void UART_Send_String(char *prompt);
int UART_ParseCommand() {
     char answer[20]="pisos";
    // if echo
    if(strncmp(new_receive_data	, "sosi ", 5) == 0)
        // huy
        UART_Send_String(answer	 + 5);
		short return_cmdname = 1;
		return 1;
	}

void CommandExecute(char cmd_name) {
	
}
	
	
int UART(void)
{
	
	char *greeting = "Nya Kawai! \r\n> ";
	UART_Send_String(greeting);
	char huy[8] = {"huy \r \n"};
	HAL_UART_Transmit_IT(&huart3, huy, 8);
	void UART_Send_String();
	void UART_Receive();
	int UART_ParseCommand();
	
	while(1)
{	
		
	UART_Receive();
	UART_ParseCommand();
	
	
	
	
	
	
	
	
	}
}