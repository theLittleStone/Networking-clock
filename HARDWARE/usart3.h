#ifndef __USART3_H
#define __USART3_H
#include "stm32f10x.h"
#include "stdio.h"

extern uint8_t res[];
void USART3_Init(void);
void USART3_SendByte(uint8_t ch);
void USART3_SendString(char *str);

#endif
