
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal_flash.h"

	void FlashTest(void);

#define MY_FLASH_PAGE_ADDR 0x800FC00
uint32_t testdata;


typedef struct
  {
    char Parameter1;        // 1 byte
    uint8_t Parameter2;     // 1 byte
    unsigned char Parameter3;   // 1 byte
 
    uint8_t nothing;        // 1 byte
 
                            // 4 byte = 32 bits.  It's - OK
                            // !!! Full size (bytes) must be a multiple of 4 !!!
  } tpSettings;

void FLASH_Init(void)
{
__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);
	
	}

	
uint32_t Read_Flash(uint32_t Data_adr)
	{
		
		return *(uint32_t*) Data_adr;
	}
	
	
	void FlashTest()
	{
		testdata = Read_Flash(MY_FLASH_PAGE_ADDR);
		printf("%i /r/n", testdata);
	}
	


	
	
	