#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>


	//Peripherals
short buttonState; //where the button state stored
short ENC1buttonState = 0; //where the Encoder1 button state stored
short ENC2buttonState = 0; //where the Encoder2 state stored
short StatLed1State = 0;
short StatLed2State = 0;
short PS_ON = 0;
short FAN_EN = 0;
int FAN_PWM = 200; //from 0 to 255 (0 - means max RPM!, fan PWM seems to be inverted)

void PSU_SWITCH(char *arg);
void LED_CLI(char *led_num, char *led_en, char *led_pwm);
void char2short(char* pchar, short* pshort);
void char2int(char* pchar, int* pint);
void GetTemperature(void);
void CliGetTemperature(void);
void FanLogic(char *arg);
void AdcDatahandler(char *arg);
void StatLEDsControl(char *arg1, char *arg2); //status LEDs on\off command function
void ButtonFunctions(short btn_num, short btn_state); //Buttons functionality

char FanLogicArg1[10] = "nc"; //default arg, not change
char AdcDatahandlerArg[10] = "nc"; //default arg, not change
short FanLogicMode = 1; //default on
short btn_state = 0; //this variable store button state
uint32_t LastBtnPress = 0;
short LastBtnPressState = 0;
short CurrentBtnPressState = 0;
uint32_t CurrentBtnPress = 0;


float DeviceInputVoltage = 0;
float BackupBatVoltage = 0;

short FanLogicHist = 10; //value at which current temperature should be less than FanOnThresholdTemp
signed int FanOnThresholdTemp = 355; //Temperature at which fan will start work 
signed int FanOffThresholdTemp = 265; //Temperature at which fan will stop work, if system cooled enough
signed int CriticalLedsTemperature = 855; //When reached, LED's will OFF to prevent damage
signed int LedsTemperatureDiff = 0; //Difference between previous and last measure
short FanHistDiff = 0;

volatile uint32_t AdcCh1Value = 0; //raw data from ADC, ch1
volatile uint32_t AdcCh2Value = 0; //raw data from ADC, ch2

void Auxiliary(void)
{

		
	
TIM2->CCR1 = FAN_PWM; //Set PWM value for fan	
//buttonState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2); //read button state
GetTemperature();	//get temperature value into global variable from DS18B20 sensor
FanLogic(FanLogicArg1); //control fan 
AdcDatahandler(AdcDatahandlerArg); //convert ADC values into voltage values

	
	

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

switch(StatLed1State) //STAT_LED2 switch
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	break;
	default:
break;
}


switch(StatLed2State) //STAT_LED2 switch
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
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



void StatLEDsControl(char *arg1, char *arg2) //status LEDs on\off command function
	{ 
	short ledstate;
	short lednum;

if (arg1 != NULL) //If arg1 not empty, get lednum value
{
	char2short(arg1, &lednum);
}

if (arg2 != NULL) //If arg2 not empty, get ledstate value
{
	char2short(arg2, &ledstate);
}

switch(lednum)
{
	case 0:
		printf("Wrong lednum /r/n");
		break;
	case 1: //If lednum = 1
		if (lednum == 1) 
		{
	switch(ledstate)
	{
		case 0: //If ledstate = 0 (OFF)
			StatLed1State = 0;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		break;
		case 1:
			StatLed1State = 1; //If ledstate = 1 (ON)
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
			break;
		default:
			printf("Wrong ledstate /r/n");
			break;
		}
		break;
	}
	case 2: //If lednum = 2
		if (lednum == 2)
		{
	switch(ledstate)
	{
		case 0:
			StatLed2State = 0; //If ledstate = 0 (OFF)
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		break;
		case 1:
			StatLed2State = 1; //If ledstate = 1 (ON)
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
			break;
		default:
			printf("Wrong ledstate /r/n");
			break;
		}
	break;
	default:
		//printf("Wrong lednum /r/n");
		break;
	}	
}
	return;
}









void FanLogic(char *arg)
{
	
	FanHistDiff = FanOffThresholdTemp - FanLogicHist;
	
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
		FAN_PWM = 150;
		return;
	}
	
	if (LedsTemperature <= FanOffThresholdTemp) 
	{
		//FAN_EN = 1;
		FAN_PWM = 105;
		if (LedsTemperature <= FanHistDiff) 
	{
		FAN_EN = 0;
		FAN_PWM = 205;
		return;
	}			
		return;
	}
	

	
	//if (LedsTemperature <= FanHistDiff) 

	//if any diffrence
	if ((LedsTemperature != OldLedsTemperature) && (LedsTemperature != FanOffThresholdTemp)) //If current temperature differ than previous and != FanOffThresholdTemp
	{
		LedsTemperatureDiff = (LedsTemperature - OldLedsTemperature); //count difference
		if (((LedsTemperatureDiff >= 1) && (FAN_PWM >= 1))) //if diffrence equal or more than 0,1С  
		{
			if (FAN_PWM != 1) 
			{
		FAN_PWM = (FAN_PWM - 1); //increase fan RPM
		LedsTemperatureDiff = 0; //re-zero
				return;
			}
		}
		if ((LedsTemperatureDiff == -1) && (FAN_PWM <= 255)) //if diffrence equal or more than 0,1С  
		{
			//if (FAN_PWM != 254) //If fan pwm value  
			//{
		FAN_PWM = (FAN_PWM + 1); //decrease fan RPM
		LedsTemperatureDiff = 0; //re-zero
			return;
			//}
		}
		LedsTemperatureDiff = 0; //re-zero
		return;
	}
	
	if (LedsTemperature >= CriticalLedsTemperature) //If current temperature equal or above critical 
	{
		LED1_EN = LED2_EN = LED3_EN = LED4_EN = 0; //Off all LED's
		LED1_PWM = LED2_PWM = LED3_PWM = LED4_PWM = 0; //set all LED's PWM to zero
		FAN_PWM = 1; //fan PWM to max value
		FAN_EN = 1; //fan turn on
		return;
	}
	break;
		case 0: //do nothing
	break;
		default:
	break;
	}
	return;
	}

	
void AdcDatahandler(char *arg) //calculate and print voltage values
{
	DeviceInputVoltage = ((AdcCh1Value * 3300) / 4095); //calculate values
	BackupBatVoltage = ((AdcCh2Value * 3300) / 4095); //calculate values
	
	if((strncmp(arg, "v", 2) == 0) && (arg != NULL))  //Mode change code block
	{
	printf("Input Voltage: %f \n\r", DeviceInputVoltage);
	printf("BAT Voltage: %f \n\r", BackupBatVoltage);
	}
	
	if((strncmp(arg, "adc", 3) == 0) && (arg != NULL)) 
	{
	printf("%i ADC CH1(Main Power) \n\r", AdcCh1Value); //debug
	printf("%i ADC CH2(Backup Battery) \n\r", AdcCh2Value); //debug
	}
	
	if((strncmp(arg, "nc", 2) == 0) && (arg != NULL)) 
	{	
		//do nothing
	}		
	
	return;
}
	

void EncoderFunctions()
{
}


//NewTickTime = HAL_GetTick();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) //ENC1_SW External interrupt callback
{
  if(GPIO_Pin == ENC1_SW_Pin) 
		{
		ENC1buttonState = 1;
		ButtonFunctions(1,1); //button of ENC1, state pressed
  }
	
	  if(GPIO_Pin == ENC2_SW_Pin) 
			{
		ENC2buttonState = 1;
		ButtonFunctions(2,1); //button of ENC1, state pressed
  }
}


void ButtonFunctions(short btn_num, short btn_state)
{
		switch (btn_num) //Switch by button number arg
	{
		case 0:
	switch (btn_state) //Switch by button state arg for Button #0(ENC2_SW)
	{
		case 0:
			break;
		case 1:
			break;
	 default:
			break;
		}
			break;
		case 1:
	switch (btn_state) //Switch by button state arg for Button #1(ENC1_SW)
	{
		case 0:
			break;
		case 1:
			
			CurrentBtnPressState = 1;
	if (CurrentBtnPressState != LastBtnPressState)
				{
			PS_ON = 1; //On PSU
			StatLed1State = 1;
			HAL_GPIO_WritePin(STAT_LED1_GPIO_Port, STAT_LED1_Pin, GPIO_PIN_SET); //debug
			LastBtnPressState = 1;
				}
				else
				{
					PS_ON = 0; //Off PSU
					StatLed1State = 0;
					HAL_GPIO_WritePin(STAT_LED1_GPIO_Port, STAT_LED1_Pin, GPIO_PIN_RESET); //debug
					LastBtnPressState = 0;
				}
			break;
	 default:
			break;
		}
	break;
		case 2:
	switch (btn_state) //Switch by button state arg Button #2(ENC2_SW)
	{
		case 0:
			break;
		case 1: //Switch on\off all LED's
	CurrentBtnPressState = 1;
	if (CurrentBtnPressState != LastBtnPressState)
				{
			LED1_EN = LED2_EN = LED3_EN = LED4_EN = 1; //On all LED's
			StatLed2State = 1;
			HAL_GPIO_WritePin(STAT_LED2_GPIO_Port, STAT_LED2_Pin, GPIO_PIN_SET); //debug
			LastBtnPressState = 1;
				}
				else
				{
					LED1_EN = LED2_EN = LED3_EN = LED4_EN = 0; //On all LED's
					StatLed2State = 0;
					HAL_GPIO_WritePin(STAT_LED2_GPIO_Port, STAT_LED2_Pin, GPIO_PIN_RESET); //debug
					LastBtnPressState = 0;
				}
			break;
	 default:
			break;
		}
			break;
			default:
			break;
		}
}


