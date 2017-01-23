#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>


void PSU_SWITCH(char *arg);
void LED_CLI(char *led_num, char *led_en, char *led_pwm);


short btn_state = 0;
 char arg1[20] = "0";
 char arg2[20] = "0";
 char arg3[20] = "0";

void Auxiliary(void)
{

		
	//Set PWM value for fan
TIM2->CCR1 = FAN_PWM;
		
buttonState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2); //read button state
		
	

			//switch for button actions
switch (buttonState)
{	
	case 0:
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	printf("Meow! Button pressed. \n\r");
	if (btn_state == 0) 
		{
			strcpy(arg1, "ALL");
			strcpy(arg2, "ON");
			strcpy(arg3, "MIN");
		LED_CLI(arg1, arg2, arg3);
		btn_state = 1;
		HAL_Delay(1000);
		}
	if (btn_state == 1) 
		{
			strcpy(arg1, "ALL");
			strcpy(arg2, "OFF");
			strcpy(arg3, "MIN");
		LED_CLI(arg1, arg2, arg3);
		btn_state = 0;
		HAL_Delay(1000);
		}
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



  /* USER CODE BEGIN 3 */
return;
  }
  /* USER CODE END 3 */
 
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
