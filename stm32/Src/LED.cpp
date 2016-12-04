
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

	
