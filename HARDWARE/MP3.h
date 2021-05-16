#ifndef __MP3_H
#define __MP3_H
#include "stm32f10x.h"

#define BUSY  	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)

void MP3_Init(void);
void DoSum( uint8_t *Str, uint8_t len);
void SendCmd(uint8_t len);
void Uart_SendCMD(uint8_t CMD ,uint8_t feedback , uint16_t dat);
void Readtime(uint8_t mon,uint8_t day,uint8_t hour, uint8_t min, uint8_t sec);

#endif
