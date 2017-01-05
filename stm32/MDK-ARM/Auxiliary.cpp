#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>


void PSU_SWITCH(char *arg);

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
