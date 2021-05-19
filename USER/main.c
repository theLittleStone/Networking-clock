#include "stm32f10x.h"
//start up中SystemInit记得去掉注释
#include "TM1637.h"
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

	RTC_Set(2021, 1, 1, 0, 0, 0);
	RTC_Alarm_Set(2021,1,1,12,26,10);
	RTC_Init();
	showAll();

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
				//showAlarm(NextAlarm);
				RTC_Set(2021,1,2,0,0,0);
			}
			while(KEY_UP == 1);
		}
		
	
		if(KEY0 == 0)                //按下KEY0进行网络校时
		{
			delay_ms(10);
			if(KEY0 == 0)
			{
			
			//LED0_ON;
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
					memset(USART_RX_BUF2,'\0',sizeof(USART_RX_BUF2));// 清空字符串
				}
				else 
				{	
					//Uart_SendCMD(0x12,0,0x11); //提醒校时失败，检查网络环境
					clearMessage(GettingTime);
					showMessage(FailToGetTime);
					delay_ms(3000);
					//while(BUSY!=1);		
					clearMessage(FailToGetTime);	
					memset(USART_RX_BUF2,'\0',sizeof(USART_RX_BUF2));// 清空字符串	
				}			
			}
			while(KEY0 == 0);
			delay_ms(10);
			//LED0_OFF;
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

