#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal_tim.h"

//#include "stm32f1xx_hal_uart.h"
//#include "CLI.h"

#define PORT  GPIOA   //указать порт, к которому подключены датчики
#define TIMER TIM3    //задаем таймер, используемый для формирования задержек
uint8_t PinNumber = 1;
signed int HS_temp = 0;
void GetTemperature(void);
 
 //код скопипизжен с http://mycontroller.ru/old_site/stm32-ds18b20-izmerenie-temperaturyi/
//*********************************************************************************************
//function  импульс сброса                                                                   //
//argument  маска порта                                                                      //
//return    0 - устройство обнаружен, 1 - не обнаружено, 2 - к.з. на линии                   //
//*********************************************************************************************
uint8_t ds_reset_pulse(uint16_t PinMask)
{
   uint16_t result;   
 
   if((PORT->IDR & PinMask)==0)  
		return 2;         //проверить линию на отсутствие замыкания
   PORT->ODR &= ~PinMask;                          //потянуть шину к земле
   TIMER->CNT=0;
   while(TIMER->CNT<480){};                        //ждать 480 микросекунд
   PORT->ODR |=  PinMask;                          //отпустить шину
   while(TIMER->CNT<550){};                        //ждать 70 микросекунд
   result     =  PORT->IDR & PinMask;              //прочитать шину 
   while(TIMER->CNT<960){};                        //дождаться окончания инициализации
	 //printf("%d \n\r", result);
   if(result) return 1;                            //датчик не обнаружен
   return 0;                                       //датчик обнаружен      
}


	//*********************************************************************************************
//function  передача бита                                                                    //
//argument  значение передаваемого бита,маска порта                                          //
//return    none                                                                             //
//*********************************************************************************************
void ds_write_bit(uint8_t bit,uint16_t PinMask)
{
   TIMER->CNT=0;
   PORT->ODR &= ~PinMask;                          //потянуть шину к земле
   while(TIMER->CNT<2){};                          //ждать 1 микросекунду
   if(bit) PORT->ODR |=  PinMask;                  //если передаем 1, то отпускаем шину
   while(TIMER->CNT<60){};                         //задержка 60 микросекунд 
   PORT->ODR |=  PinMask;                          //отпускаем шину 
}

//*********************************************************************************************
//function  чтение бита                                                                      //
//argument  маска порта                                                                      //
//return    прочитанный бит                                                                  //
//*********************************************************************************************
uint16_t ds_read_bit(uint16_t PinMask)
{
   uint16_t result;
 
   TIMER->CNT=0;
   PORT->ODR &= ~PinMask;                          //потянуть шину к земле
   while(TIMER->CNT<2){};
   PORT->ODR |=  PinMask;                          //отпускаем шину  
   while(TIMER->CNT<15){};                         //задержка 15 микросекунд
   result     =  PORT->IDR & PinMask;              //прочитать шину
   while(TIMER->CNT<60){};                         //оставшееся время 
   return result;                                  //возвратить результат
}

//*********************************************************************************************
//function  запись байта                                                                     //
//argument  передаваемый байт,маска порта                                                    //
//return    none                                                                             //
//*********************************************************************************************
void ds_write_byte(uint8_t byte, uint16_t PinMask)
{
   uint8_t i;
   for(i=0;i<8;i++) ds_write_bit(byte&(1<<i), PinMask);
}
//*********************************************************************************************
//function  чтение байта                                                                     //
//argument  маска порта                                                                      //
//return    прочитанный байт                                                                 //
//*********************************************************************************************
uint8_t ds_read_byte(uint16_t PinMask)
{
   uint8_t i,result = 0;
   for(i=0;i<8;i++) 
   if(ds_read_bit(PinMask)) result |= 1<<i; 
   return result;
}

//*********************************************************************************************
//function  пуск измерения температуры                                                       //
//argument  номер пина порта 0..15                                                           //
//return    0 - пуск выполнен, 1 - датчик не обнаружен, 2 - к.з. на линии                    //
//*********************************************************************************************
uint8_t ds_start_convert_single(uint8_t PinNumb)
{
  uint8_t result;
  result = ds_reset_pulse(1<<PinNumb);       //послать импульс сброса
			 printf("%i \n\r", result); //debug	
  if(result) return result;                  //если ошибка - возвращаем ее код
  ds_write_byte(0xCC,1<<PinNumb);            //разрешить доступ к датчику не используя адрес  
  ds_write_byte(0x44,1<<PinNumb);            //запустить преобразование
  return 0;
}
//*********************************************************************************************
//function  чтение памяти датчика                                                            //
//argument  указатель на массив-приемник данных, номер пина порта 0..15                      //
//return    0 - данные прочитаны, 1 - датчик не обнаружен, 2 - к.з. 3 - ошибка CRC           //
//*********************************************************************************************
uint8_t ds_read_data_single(uint8_t *buff, uint8_t PinNumb)
{
  uint8_t crc = 0;
  uint8_t data;
  uint8_t i,j;
  uint8_t tmp;
 
  tmp = ds_reset_pulse(1<<PinNumb);          //послать импульс сброса
  if(tmp) return tmp;                        //если ошибка - возвращаем ее код
  ds_write_byte(0xCC,1<<PinNumb);            //разрешить доступ к датчику не используя адрес
 
  ds_write_byte(0xBE,1<<PinNumb);            //запрос 9 байт памяти
 
  //прочитать 8 байт и вычислить CRC
  for( i=0; i<8; i++) 
  {
    data = ds_read_byte(1<<PinNumb);         //прочитать очередной байт      
    buff[i] = data;                          //сохранить его в массиве
 
    //вычисление CRC - обрабатываем каждый бит принятого байта
    for( j=0; j<8; j++)         
    {
      tmp = (crc ^ data) & 0x01;
      if (tmp==0x01) crc = crc ^ 0x18;
      crc = (crc >> 1) & 0x7F;
      if (tmp==0x01) crc = crc | 0x80;
      data = data >> 1;
    }		
  }
 
  data = ds_read_byte(1<<PinNumb);          //прочитать CRC датчика
  if(crc==data) return 0;                   //если CRC совпали - значит ошибки нет
  return 3;                                 //CRC не совпали, ошибка принятых данных
}


//*********************************************************************************************
//function  чтение температуры датчика                                                       //
//argument   номер пина порта 0..15                                                          //
//return    1280 - ошибка, иначе - результат измерения                                       //
//*********************************************************************************************
signed int ds_read_temperature(uint8_t PinNumb)
{
  signed char integer = 0;     
  signed char frac;
  signed int  result;
  uint8_t     buff[8];
 
  //прочитать данные из датчика 
  if(ds_read_data_single(&buff[0],PinNumb))  return 1280;
 
  frac    = buff[0] & 0x0f;                            //получить дробную часть      
  integer = (buff[0]>>4) | ((buff[1] & 0x0f)<<4);      //получить целую часть 
 
  //если температура отрицательная
  if(integer<0)
  {
    integer = 0 - integer - 1;
    result  = integer *10;                            //учитываем целую часть
    frac = frac | 0xf0;
    frac = 0 - frac ;                                 
  }
  //если температура положительная
  else     result  = integer *10;                    //учитываем целую часть
 
  result = result + ((frac*10)/16);                  //учитываем дробную часть
 
  return result;
}



void GetTemperature()
 {
	HS_temp = 0;
	ds_start_convert_single(PinNumber);     //запустить измерение температуры   
	 
	//HAL_Delay(1000);
	//HS_temp = ds_read_temperature(PinNumber);   //прочитать результат измерения
 }
 		