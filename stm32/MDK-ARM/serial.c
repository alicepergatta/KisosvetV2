#include "stm32f1xx_hal.h"
extern UART_HandleTypeDef huart3;
struct __FILE { int handle; /* Add whatever is needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
HAL_UART_Transmit(&huart3, (char *)(&ch),1,1000);
return(ch);
}
