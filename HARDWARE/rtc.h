#ifndef __RTC_H
#define __RTC_H	
#include "sys.h"
//Mini STM32开发板
//RTC实时时钟 驱动代码			 
//正点原子@ALIENTEK
//2010/6/6

//时间结构体
typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//公历日月年周
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;		 
}_calendar_obj;					 

#define RING_TIME 10 //闹钟响铃时间, 单位为秒

extern _calendar_obj calendar;	//日历结构体
extern _calendar_obj alarm_calendar;//闹钟结构体
extern _calendar_obj setting_calendar;
extern u8 settingFlag;

extern u8 const mon_table[12];	//月份日期数据表


u8 RTC_Init(void);        //初始化RTC,返回0,失败;1,成功;
u8 Is_Leap_Year(u16 year);//平年,闰年判断
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置闹钟
u8 RTC_Next_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置给定时间后一天的闹钟
u8 RTC_Get(void);         //更新时间   
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置时间		
void RTC_Alarm_Get(u32 timecount);	
u8 getMaxDayInMonth(u16 year, u8 month); //判断一个月有多少天 
#endif


