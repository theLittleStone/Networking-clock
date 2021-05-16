#include "stm32f10x.h"
#include "led.h"

void led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能外设时钟
	
	GPIO_InitStructure.GPIO_Pin = LED0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_CTRL0,&GPIO_InitStructure);  //初始化GPIO
	LED0_OFF;

}

