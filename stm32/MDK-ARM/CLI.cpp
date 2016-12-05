#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal_uart.h"
#include "CLI.h"

//defines & variables
void SystemClock_Config(void);
void Error_Handler(void);
static UART_HandleTypeDef huart3;
void HMX_USART3_UART_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
extern HAL_StatusTypeDef  HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, char *pData, uint16_t Size);

short result;
short cmd_num; //command id
short reply_buffer_cnt;
short rec_len;

char Clean[128] = {"  "};
char newBuffer[128] = {"  "};
char oldBuffer[128] = {"  "};
char answer[512] = {"  "};
char deb_string[64] = {"ExecuteCmd\r \n  "};
char buffer1[] = {"HUY! \n\r"}; //test buffer

//functions


//short ParseCmd(char *newBuffer)
short ParseCmd() {
rec_len = sizeof(receiveBuffer) / sizeof(char); //count buffer size
strncpy(newBuffer, receiveBuffer, rec_len);
newBuffer[rec_len++]=0;	
if (strncmp(newBuffer, "sosi", 5) == 0)
    {
		snprintf(oldBuffer, 128, "%s", newBuffer);
		strcpy(newBuffer, CleanBuffer);  
		result = 1; 
    }
if (strncmp(newBuffer, "meow", 5) == 0)
    {	
		snprintf(oldBuffer, 128, "%s", newBuffer);
		strcpy(newBuffer, CleanBuffer);  
		result = 2; 
    }

if (strncmp(newBuffer, " ", 1) == 0)
	{
	snprintf(oldBuffer, 128, "%s", newBuffer);	
	strcpy(newBuffer, CleanBuffer);  
	result = 3;
	}
else 
	{
	result = 0;
	}
	
	strcpy(receiveBuffer, CleanBuffer);  
	rec_len = 0;
	return result;

}

void ExecuteCmd(short cmd_num)
{


reply_buffer_cnt = sizeof(deb_string) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, deb_string, reply_buffer_cnt);

//return;	
	switch(cmd_num)
{
case 1:
{
char answer[512] = {"case 1 \r \n"};
reply_buffer_cnt = sizeof(answer) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, answer, reply_buffer_cnt);
	//strcpy(receiveBuffer, CleanBuffer);
	break;
}
case 2:
{
char answer[512] = {"case 2 \r \n"};
reply_buffer_cnt = sizeof(answer) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, answer, reply_buffer_cnt);
	return;
}
case 3:
{
char answer[512] = {"case 3 \r \n"};
reply_buffer_cnt = sizeof(answer) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, answer, reply_buffer_cnt);
	return;
}
case 0:
{
char answer[512] = {"Nihuya? \r \n"};
reply_buffer_cnt = sizeof(answer) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, answer, reply_buffer_cnt);
	break;
	}
case 4:
{
	char answer[512] = {"Nihuya2 \r \n"};
reply_buffer_cnt = sizeof(answer) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, answer, reply_buffer_cnt);
	break;
}
default:
{
char answer[512] = {"ExecuteCmd\r \n"};
reply_buffer_cnt = sizeof(answer) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, answer, reply_buffer_cnt);

return;

}
	}

char answer[512] = {"ExecuteCmd\r \n"};
reply_buffer_cnt = sizeof(answer) / sizeof(char); //count buffer size
HAL_UART_Transmit_IT(&huart3, answer, reply_buffer_cnt);

	return;
}



void PrintToUART(char *text) {
//HAL_Init();
//HMX_USART3_UART_Init();	
char promt[] = {"\r \n"};
short text_cnt = sizeof(text) / sizeof(char); //count buffer size
text_cnt = sizeof(text) / sizeof(char); //count buffer size
text_cnt = (text_cnt * 2 + 2);
HAL_UART_Transmit_IT(&huart3, text, text_cnt);
//text_cnt = sizeof(*buffer1) / sizeof(char); //count buffer size
//HAL_UART_Transmit_IT(&huart3, buffer1, text_cnt); //debug
return;
}

void HMX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
//  huart3.Init.BaudRate = 115200;
//  huart3.Init.WordLength = UART_WORDLENGTH_8B;
//  huart3.Init.StopBits = UART_STOPBITS_1;
//  huart3.Init.Parity = UART_PARITY_NONE;
//  huart3.Init.Mode = UART_MODE_TX_RX;
//  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
return;
}
