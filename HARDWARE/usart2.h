#ifndef __USART2_H
#define __USART2_H
#include "stm32f10x.h"
#include "stdio.h"

void USART2_Init(void);
void USART2_SendByte(uint8_t ch);
void USART2_SendString(char *str);

//#define USART_REC_LEN  			300 
#define EN_USART1_RX 			1	

extern u8 USART_RX_BUF2[512];
extern u16 USART_RX_STA2;
//extern unsigned char res[];

#endif
