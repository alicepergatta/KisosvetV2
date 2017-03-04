/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define TEMP_Pin GPIO_PIN_1
#define TEMP_GPIO_Port GPIOA
#define BTN_1_Pin GPIO_PIN_2
#define BTN_1_GPIO_Port GPIOA
#define EXT_L_1_Pin GPIO_PIN_3
#define EXT_L_1_GPIO_Port GPIOA
#define V_SENSE_M_Pin GPIO_PIN_4
#define V_SENSE_M_GPIO_Port GPIOA
#define V_SENSE_BAT_Pin GPIO_PIN_5
#define V_SENSE_BAT_GPIO_Port GPIOA
#define STAT_LED1_Pin GPIO_PIN_6
#define STAT_LED1_GPIO_Port GPIOA
#define STAT_LED2_Pin GPIO_PIN_7
#define STAT_LED2_GPIO_Port GPIOA
#define STAT_LED3_Pin GPIO_PIN_0
#define STAT_LED3_GPIO_Port GPIOB
#define ENC1_SW_Pin GPIO_PIN_15
#define ENC1_SW_GPIO_Port GPIOB
#define LED1_EN_Pin GPIO_PIN_9
#define LED1_EN_GPIO_Port GPIOA
#define LED2_EN_Pin GPIO_PIN_10
#define LED2_EN_GPIO_Port GPIOA
#define LED3_EN_Pin GPIO_PIN_11
#define LED3_EN_GPIO_Port GPIOA
#define LED4_EN_Pin GPIO_PIN_12
#define LED4_EN_GPIO_Port GPIOA
#define FAN_PWM_Pin GPIO_PIN_15
#define FAN_PWM_GPIO_Port GPIOA
#define LED1_PWM_Pin GPIO_PIN_6
#define LED1_PWM_GPIO_Port GPIOB
#define LED2_PWM_Pin GPIO_PIN_7
#define LED2_PWM_GPIO_Port GPIOB
#define LED3_PWM_Pin GPIO_PIN_8
#define LED3_PWM_GPIO_Port GPIOB
#define LED4_PWM_Pin GPIO_PIN_9
#define LED4_PWM_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */



	//PWM values for each LED PM
extern int LED1_PWM;
extern int LED2_PWM;
extern int LED3_PWM;
extern int LED4_PWM;
	//Calibration values, in addition to hardware calibration
extern int LED1_CAL_VALUE;
extern int LED2_CAL_VALUE; 
extern int LED3_CAL_VALUE;
extern int LED4_CAL_VALUE;	
	//Values wich will be transformed into PWM values, considering CAL values
extern int LED1_VALUE;
extern int LED2_VALUE;
extern int LED3_VALUE;
extern int LED4_VALUE;

extern int LED1_ALL_VALUE;
extern int LED2_ALL_VALUE;
extern int LED3_ALL_VALUE;
extern int LED4_ALL_VALUE;	
	//CAL values signs
extern char LED1_CAL_SIGN;
extern char LED2_CAL_SIGN;
extern char LED3_CAL_SIGN;
extern char LED4_CAL_SIGN;

	//Maximum PWM value, for testing purposes
extern int MAX_PWM;
extern int MIN_PWM;
extern short buttonState; //where the button state stored
extern short ENC1buttonState; //where the Encoder1 button state stored
extern short ENC2buttonState; //where the Encoder2 state stored

	//ON-OFF PM's by those values
extern int LED1_EN;
extern int LED2_EN;
extern int LED3_EN;
extern int LED4_EN;
	//FAN PWM value, to control fan speed
extern int FAN_PWM;
extern short FAN_EN;
extern char FanLogicArg1[10];

	//temperature on DS18B20
extern signed int LedsTemperature;	
extern signed int OldLedsTemperature;
//extern uint8_t PinNumber;
	
	//Power ON ATX PSU by KisoSvet)
extern short PS_ON;

	//ADC
extern volatile uint32_t AdcCh1Value; //channel 1 ADC raw value 
extern volatile uint32_t AdcCh2Value; //channel 2 ADC raw value

extern float DeviceInputVoltage; //Voltage which powers Kisosvet
extern float BackupBatVoltage; //Internal battery voltage

	//Buffers for UART
extern char transmitBuffer[128];
extern char receiveBuffer[228];
extern short receiveBuffer_cnt;
extern char ParseBuffer[128];
extern const char CleanBuffer[128];

extern bool stringComplete;
extern bool startNewLine;

extern short L_ECHO;
extern short CMD_ANSWER;

//extern char transmitBuffer[1];
//extern char receiveBuffer[1];

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
