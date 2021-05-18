#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0_CLK 	RCC_APB2Periph_GPIOE
#define KEY0_PORT   GPIOE
#define KEY0_PIN 	GPIO_Pin_4

#define KEY1_CLK 	RCC_APB2Periph_GPIOE
#define KEY1_PORT   GPIOE
#define KEY1_PIN 	GPIO_Pin_3

#define KEY2_CLK 	RCC_APB2Periph_GPIOE
#define KEY2_PORT   GPIOE
#define KEY2_PIN 	GPIO_Pin_2

#define KEY_UP_CLK  RCC_APB2Periph_GPIOA
#define KEY_UP_PORT GPIOA
#define KEY_UP_PIN  GPIO_Pin_0

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0, 0为按下
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1, 0为按下
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2, 我的板子上没有这个按键
#define KEY_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(KEY_UP), 1为按下

void key_Init(void);

#endif
