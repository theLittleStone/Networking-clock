#include "stm32f10x.h"
//start up中SystemInit记得去掉注释
#include "delay.h"
#include "rtc.h"
#include "key.h"
#include "lcd.h"
#include "usart.h"
//#include "usart3.h"
#include "usart2.h"
#include "ESP01.h"
#include "display.h"
#include "string.h"
#include "beep.h"
#include "SHT2x.h"

unsigned char  Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char  DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};


//int time[3]={0x3f,0x3f,0x3f};
//uint8_t thrh[4]={0x66,0x6d,0x7d,0x07};

extern _calendar_obj calendar;

extern unsigned char rec_dat[];

int main()
{
	
	uart_init(115200);  //调试串口
	delay_init();
	//TM_Init();
	key_Init();
	USART2_Init(); //初始化网络串口
	LCD_Init();
	BEEP_Init();
	SHT2x_Init(); //初始化
	RTC_Set(2021, 1, 1, 0, 0, 0);
	RTC_Alarm_Set(2021,1,1,0,0,10);
	RTC_Init();
	showAll();

	//Test_Connect();
	while (1)
	{ 
		
		delay_ms(100);
		
		if(KEY1 == 0){                     //按下KEY1复位时钟
			delay_ms(10);
			if(KEY1 == 0)
				RTC_Set(2021, 1, 1, 0, 0, 0);
			while(KEY1 == 0);
		}
		
		if(KEY_UP == 1){
			delay_ms(10);
			if(KEY_UP == 1){
				//showSPrint();
				showH_T();
			}
			while(KEY_UP == 1);
		}
		
	
		if(KEY0 == 0)                //按下KEY0进行网络校时
		{
			delay_ms(10);
			if(KEY0 == 0)
			{
			
			delay_ms(100);
			getOnlineTime();
				
			}
			while(KEY0 == 0);
			delay_ms(10);
			
		}

		if(calendar.hour==0 && calendar.min==1 && calendar.sec==0){  //每个0点一分联网校对时间
			getOnlineTime();                                         //这个函数放在秒中断函数中会一直连接失败
																	 //初步估计与串口中断的优先级有关. 所以
																	 //直接放在了主循环里
		}
		delay_ms(50);
		//未开放功能
		//获得天气
		/*
		if(KEY4==0)
		{
			LED0_ON;
			delay_ms(100);
			Uart_SendCMD(0x12,0,0x14);  //提醒正在获取天气
			ESP01_Getweather();
			delay_ms(300);
			
			for(uint16_t i=0;i<512;i++)
			{
				USART1_SendByte(USART_RX_BUF2[i]);  //调试
			}
			LED0_OFF;
		}
		*/
		
	}
	

}

