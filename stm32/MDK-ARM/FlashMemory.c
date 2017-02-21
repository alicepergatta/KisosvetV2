
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f1xx_hal_tim.h"

//#define FLASH_KEY1 ((uint32_t)0x45670123)
//#define FLASH_KEY2 ((uint32_t)0xCDEF89AB)

//скопипизжено с http://easystm32.ru/for-beginners/38-flash-stm32


//uint8_t page_num = 126;


//uint8_t flash_ready(void) {
//	return !(FLASH->SR & FLASH_SR_BSY);
//}

//void flash_erase_all_pages(void) {
//    FLASH->CR |= FLASH_CR_MER;
//    FLASH->CR |= FLASH_CR_STRT;
//    while(!flash_ready())
//    	;
//    FLASH->CR &= FLASH_CR_MER;
//}

//void flash_erase_page(uint32_t address) {
//    FLASH->CR|= FLASH_CR_PER;
//    FLASH->AR = address;
//    FLASH->CR|= FLASH_CR_STRT;
//    while(!flash_ready())
//    	;
//    FLASH->CR&= ~FLASH_CR_PER;
//}


//void flash_unlock(void) {
//	  FLASH->KEYR = FLASH_KEY1;
//	  FLASH->KEYR = FLASH_KEY2;
//}

//void flash_lock() {
//	FLASH->CR |= FLASH_CR_LOCK;
//}


//void flash_write(uint32_t address,uint32_t data) {

//	FLASH->CR |= FLASH_CR_PG;
//	while(!flash_ready())
//		;
//    *(__IO uint16_t*)address = (uint16_t)data;
//	while(!flash_ready())
//		;
//	address+=2;
//	data>>=16;
//    *(__IO uint16_t*)address = (uint16_t)data;
//	while(!flash_ready())
//		;
//    FLASH->CR &= ~(FLASH_CR_PG);

//}

//uint32_t flash_read(uint32_t address) {
//	return (*(__IO uint32_t*) address);
//}



//uint8_t read_number(void) {
//	uint8_t i=0;
//	uint8_t data;
//	uint8_t nubm[]={0x00,0x00,0x00,0x00};
//}



//void flash_test()
//{
//	
//	uint32_t st_address = FLASH_BASE + page_num * 1024;
//					uint8_t i,j;
//				uint8_t st[16];
//	st[j]=flash_read(st_address);
//						st[j+1]=flash_read(st_address)>>8;
//						st[j+2]=flash_read(st_address)>>16;
//						st[j+3]=flash_read(st_address)>>24;
//	
//}


