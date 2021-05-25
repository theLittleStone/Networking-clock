#include "stm32f10x.h"
#include "key.h"

void key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEY0_CLK|KEY1_CLK|KEY_UP_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = KEY0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(KEY0_PORT, &GPIO_InitStructure);//初始化KEY0
	
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);//初始化KEY1
	
	GPIO_InitStructure.GPIO_Pin  = KEY_UP_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
 	GPIO_Init(KEY_UP_PORT, &GPIO_InitStructure);//初始化KEY_UP
}


u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY_UP==0)key_up=1; 	    
 	return 0;// 无按键按下
}
