#include "stm32f10x.h"
#include "key.h"

void key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEY0_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = KEY0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(KEY0_PORT, &GPIO_InitStructure);//初始化KEY0
	
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);//初始化KEY1
	
	GPIO_InitStructure.GPIO_Pin  = KEY_UP_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(KEY_UP_PORT, &GPIO_InitStructure);//初始化KEY_UP
}
