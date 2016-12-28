
#include "main.h"
#include "stm32f1xx_hal.h"

	//Direct PWM values which used for TIM4 registers
int LED1_PWM = 0;
int LED2_PWM = 0;
int LED3_PWM = 0;
int LED4_PWM = 0;
	//Enable flags for each LED
int LED1_EN = 1;
int LED2_EN = 1;
int LED3_EN = 1;
int LED4_EN = 1;
	//Calibration values as addition to hardware calibration
int LED1_CAL_VALUE = 10;
int LED2_CAL_VALUE = 10;
int LED3_CAL_VALUE = 10;
int LED4_CAL_VALUE = 10;
	//Values for external logic
int LED1_VALUE = 57020;
int LED2_VALUE = 57020;
int LED3_VALUE = 57020;
int LED4_VALUE = 57020;


int i = 0;
int MAX_PWM = 60400;



 
int LED(int VAL, int CAL)  //Function for setting corrected PWM values
{	
	int PWM = VAL - CAL;
  return PWM;
	}	

void LED_SW() //Set LED's(PM's) on or off by variable values
{
	
		//LED1-4 ON\OFF by variables
switch(LED1_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	default:
break;
}


switch(LED2_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	break;
//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	default:
break;
}


switch(LED3_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
	default:
break;
}


switch(LED4_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
	default:
break;
}
	}
