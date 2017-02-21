#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>


	//Peripherals
short buttonState; //where the button state stored
short PS_ON = 0;
short FAN_EN = 0;
int FAN_PWM = 225; //from 0 to 255 (0 - means max RPM!, fan PWM seems to be inverted)

void PSU_SWITCH(char *arg);
void LED_CLI(char *led_num, char *led_en, char *led_pwm);
void char2short(char* pchar, short* pshort);
void char2int(char* pchar, int* pint);
void GetTemperature(void);
void CliGetTemperature(void);
void FanLogic(char *arg);
void AdcDatahandler(void);
	

char FanLogicArg1[10] = "nc"; //default arg, not change
short FanLogicMode = 1; //default on
short btn_state = 0; //this variable store button state

 
signed int FanOnThresholdTemp = 355; //Temperature at which fan will start work 
signed int FanOffThresholdTemp = 255; //Temperature at which fan will stop work, if system cooled enough
signed int CriticalLedsTemperature = 855; //When reached, LED's will OFF to prevent damage
signed int LedsTemperatureDiff = 0; //Difference between previous and last measure

volatile uint32_t AdcCh1Value = 0; //raw data from ADC, ch1
volatile uint32_t AdcCh2Value = 0; //raw data from ADC, ch2

void Auxiliary(void)
{

		
	
TIM2->CCR1 = FAN_PWM; //Set PWM value for fan	
buttonState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2); //read button state
GetTemperature();	//get temperature value into global variable from DS18B20 sensor
FanLogic(FanLogicArg1);

			//switch for button actions
switch (buttonState)
{	
	case 0:
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	printf("Meow! Button pressed. \n\r");
//	if (btn_state == 0) 
//		{
//			strcpy(arg1, "ALL");
//			strcpy(arg2, "ON");
//			strcpy(arg3, "MIN");
//		LED_CLI(arg1, arg2, arg3);
//		btn_state = 1;
//		HAL_Delay(1000);
//		}
//	if (btn_state == 1) 
//		{
//			strcpy(arg1, "ALL");
//			strcpy(arg2, "OFF");
//			strcpy(arg3, "MIN");
//		LED_CLI(arg1, arg2, arg3);
//		btn_state = 0;
//		HAL_Delay(1000);
//		}
		break;
	case 1:
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		break;
	default:
		break;
}
	
	
	

		//switch for PS-ON ATX PSU
switch(PS_ON)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	break;
	default:
break;
}

switch(FAN_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	break;
	default:
break;
}


  /* USER CODE BEGIN 3 */
return;
  }
  /* USER CODE END 3 */
 
void CliGetTemperature()
{
	GetTemperature();
	printf("Current LED's temperature: %d C \t", LedsTemperature);
	printf("  Last: %i C \t", OldLedsTemperature); 
	printf(" \n\r");
}
void PSU_SWITCH(char *arg) { //PSU on\off command function
	if(strncmp(arg, "ON", 2) == 0) {
		PS_ON = 1;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
		printf("PSU has turned ON \n\r");
	}
	if(strncmp(arg, "OFF", 3) == 0) {
		PS_ON = 0;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
		printf("PSU has turned OFF \n\r");
	}
	if(strncmp(arg, "OFF", 3) != 0 && strncmp(arg, "ON", 2) != 0) {
		printf("Syntax error \n\r");
	}
	return;
}

void FAN_SWITCH(char *arg1, char *arg2) { //PSU on\off command function
	int fan_value;
	if(strncmp(arg1, "ON", 2) == 0) 
		{
		FAN_EN = 1;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		printf("FAN has turned ON \n\r");
		}
	if(strncmp(arg1, "OFF", 3) == 0) 
		{
		FAN_EN = 0;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		printf("FAN has turned OFF \n\r");
		}
	if(strncmp(arg1, "OFF", 3) != 0 && strncmp(arg1, "ON", 2) != 0) 
		{
		printf("Syntax error \n\r");
		}
	if (arg2!= NULL) 
		{
			char2int(arg2, &fan_value);
		}
		if (fan_value >=1 && fan_value <= 255)
		{
			FAN_PWM = fan_value;
			printf("OK \n\r");
		}
	TIM2->CCR1 = FAN_PWM;
	return;
}









void FanLogic(char *arg)
{
	if((strncmp(arg, "on", 2) == 0) && (arg != NULL))  //Mode change code block
	{
		FanLogicMode = 1;
		printf("Automatic FAN control turned ON \n\r");
		printf("OK \n\r");
		//printf("%i  \n\r", LedsTemperatureDiff); //debug
	}
	
	if((strncmp(arg, "off", 3) == 0) && (arg != NULL)) 
	{
		FanLogicMode = 0;
		printf("Automatic FAN control turned OFF!!! \n\r");
		printf("OK \n\r");
	}
	
	if((strncmp(arg, "nc", 2) == 0) && (arg != NULL)) 
	{	
		//printf("OK \n\r");
	}																													//Mode change code block end
	
	
	switch (FanLogicMode)
		{
		case 1: //If turned on, make actions
	if (LedsTemperature >= FanOnThresholdTemp) 
	{
		FAN_EN = 1;
		FAN_PWM = 200;
	}
	if (LedsTemperature <= FanOffThresholdTemp) 
	{
		FAN_EN = 0;
		FAN_PWM = 255;
	}													//if any diffrence
	if ((LedsTemperature != OldLedsTemperature) && (LedsTemperature != FanOffThresholdTemp)) //If current temperature differ than previous and != FanOffThresholdTemp
	{
		LedsTemperatureDiff = (LedsTemperature - OldLedsTemperature); //count difference
		if (((LedsTemperatureDiff >= 1) && (FAN_PWM >= 1))) //if diffrence equal or more than 0,1С  
		{
			if (FAN_PWM != 1) 
			{
		FAN_PWM = (FAN_PWM - 10); //increase fan RPM
			}
		}
		if ((LedsTemperatureDiff <= -2) && (FAN_PWM <= 255)) //if diffrence equal or more than 0,1С  
		{
			if (FAN_PWM != 254) 
			{
		FAN_PWM = (FAN_PWM + 5); //decrease fan RPM
			}
		}
	}
	
	if (LedsTemperature >= CriticalLedsTemperature) //If current temperature equal or above critical 
	{
		LED1_EN = LED2_EN = LED3_EN = LED4_EN = 0; //Off all LED's
		LED1_PWM = LED2_PWM = LED3_PWM = LED4_PWM = 0; //set all LED's PWM to zero
		FAN_PWM = 1; //fan PWM to max value
		FAN_EN = 1; //fan turn on
	}
	break;
		case 0: //do nothing
	break;
		default:
	break;
	}
	return;
	}

	
void AdcDatahandler()
{
	printf("%i ADC CH1 \n\r", AdcCh1Value); //debug
	printf("%i ADC CH2 \n\r", AdcCh2Value); //debug
}
	
