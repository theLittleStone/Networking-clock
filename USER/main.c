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
#include "timedit.h"


unsigned char  Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char  DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};


//int time[3]={0x3f,0x3f,0x3f};
//uint8_t thrh[4]={0x66,0x6d,0x7d,0x07};

enum settingType type;
enum settingPart part;
extern _calendar_obj calendar;
extern _calendar_obj setting_calendar;
extern unsigned char rec_dat[];
u8 alarmIsOpen = 1; //闹钟开关标志位, 1为开

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
	showH_T();
	showAll(calendar);
	showTest("Alarm function: Open ");

	//Test_Connect();
	while (1)//没有进入设置状态的键位: KEY_UP: 进入设置  KEY0: 网络校时
	{ 
		delay_ms(50);
		//闹钟&时钟设置: KEY_UP: 进入/切换时分秒,之后切换模式  KEY_0: 按下递减  KEY_1: 按下递增
		
		editAlarm();	//这两是用来手动校时用的
		editClock();


		if(type == CLOCK_SETTING)               //时钟设置状态
			type = NONE;
		
		if(KEY1 == 0){                     //按下KEY1开关闹钟功能
			delay_ms(10);
			if(KEY1 == 0)
				alarmIsOpen = !alarmIsOpen;
			while(KEY1 == 0);
			if(alarmIsOpen)					//立即更改提示
				showTest("Alarm function: Open ");
			else
				showTest("Alarm function: Close");
		}
		
		if(KEY0 == 0){				  //按下KEY0进行网络校时
			delay_ms(10);
			if(KEY0 == 0){
				getOnlineTime();
			}
			while(KEY0 == 0);
		}
		
		if(KEY_UP == 1)               //按下KEY_UP进行手动校时模式切换
		{
			delay_ms(10);
			if(KEY_UP == 1){
				if(type == 2)  
					type = NONE;
				else
					type ++;
			}
			while(KEY_UP == 1);
		}

		//每个0点一分联网校对时间
		//这个函数放在秒中断函数中会一直连接失败, 初步估计与串口中断的优先级有关. 所以直接放在了主循环里
		if(calendar.hour==0 && calendar.min==1 && calendar.sec==0){  
			getOnlineTime();
		}

		delay_ms(25);
		



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

