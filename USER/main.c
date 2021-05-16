#include "stm32f10x.h"
//start up中SystemInit记得去掉注释
#include "TM1637.h"
#include "delay.h"
#include "led.h"
#include "rtc.h"
#include "key.h"
#include "lcd.h"

#include "usart.h"
#include "usart3.h"
#include "usart2.h"

#include "MP3.h"
#include "ESP01.h"
#include "display.h"

unsigned char  Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char  DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};


//int time[3]={0x3f,0x3f,0x3f};
//uint8_t thrh[4]={0x66,0x6d,0x7d,0x07};

extern _calendar_obj calendar;

extern unsigned char rec_dat[];

int main()
{
	
	uart_init(115200);  //调试接口
	delay_init();
	RTC_Init();
	//TM_Init();
	led_Init();
	key_Init();
	USART2_Init(); //初始化网络串口
	//MP3_Init();  //串口在其内初始化
	//Uart_SendCMD(0x06,0,0x18);  //音量
	LCD_Init();
	RTC_Set(2021, 1, 1, 0, 0, 0);
	while (1)
	{ 
		showAll();
		delay_ms(100);
		if(KEY0 == 0){
			delay_ms(10);
			if(KEY0 == 0)
				RTC_Set(2021, 1, 1, 0, 0, 0);
		}
		while (KEY1 == 0){
			showMessage(FailToGetTime);
			delay_ms(10);	
		}
		clearMessage(FailToGetTime);
		
		
		//读取时间
		/*if(KEY2==0)
		{
			LED0_ON;
			delay_ms(100);
			Readtime(calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);   //读出时间
			while(KEY2==0);
			delay_ms(10);
			LED0_OFF;
		}*/
		
		
		//网络校时并读时间
		if(KEY0 == 0)
		{
			LED0_ON;
			delay_ms(100);
			showMessage(GettingTime);
			//Uart_SendCMD(0x12,0,0x0f);  //提醒正在校时
			ESP01_Gettime();		
			delay_ms(300);
			
			/*for(uint16_t i=69;i<512;i++)
			{
				USART1_SendByte(USART_RX_BUF2[i]);  //调试
			}*/
			
			if(USART_RX_BUF2[64]==0x32)
			{
				ESP01_Settime();

				//Uart_SendCMD(0x12,0,0x10);  //校时成功
				clearMessage(GettingTime);
				showMessage(GetTimeSuccessfully);
				delay_ms(100);
				//while(BUSY!=1);
				delay_ms(3000);
				clearMessage(GetTimeSuccessfully);
				//Readtime(calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);  //读时间
			}
			else 
			{	
				//Uart_SendCMD(0x12,0,0x11); //提醒校时失败，检查网络环境
				clearMessage(GettingTime);
				showMessage(FailToGetTime);
				delay_ms(3000);
				//while(BUSY!=1);		
				clearMessage(FailToGetTime);		
			}			
			while(KEY0 == 0);
			delay_ms(10);
			LED0_OFF;
		}
		
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

