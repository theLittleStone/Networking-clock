#include "stm32f10x.h"
#include "display.h"
#include "lcd.h"
#include "key.h"
#include "delay.h"
#include "rtc.h"



#define MAX 90
#define MIN -10
extern u8 settingType;
_calendar_obj setting_calendar;//定义时间更改日历结构体
extern _calendar_obj alarm_calendar;
extern _calendar_obj calendar;
extern u8 alarmIsOpen;

void editAlarm(void){
    if(type == ALARM_SETTING){      //进入闹钟设置状态
        setting_calendar = alarm_calendar;//临时校时时钟对齐实时时钟
        settingFlag = 1;
        showTest("Editing alarm:       ");
        while(1){
            showAlarmEditStatus(part);
            if(KEY_UP == 1){               //按下KEY_UP进行手动校时模式切换
                delay_ms(10);
                if(KEY_UP == 1){
                    if(part == SECOND){
                        part = HOUR;
                        type = CLOCK_SETTING;  //变成时钟设置模式
                    }
                    else
                        part ++;
                }
                while(KEY_UP == 1);
            }

            else if(KEY1 == 0){          //增加键
                delay_ms(10);
                if(KEY1 == 0){
                    if(part == HOUR){                  //设置小时
                        while(KEY1 == 0){
                            if(setting_calendar.hour == 23);
                            else
                                setting_calendar.hour ++;
                            showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == MINUTE){             //设置分
                        while(KEY1 == 0){
                            if(setting_calendar.min == 59);
                            else
                                setting_calendar.min ++;
                            showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part ==SECOND){             //设置秒  
                        while(KEY1 == 0){
                            if(setting_calendar.sec ==59);
                            else
                                setting_calendar.sec ++;
                            showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
                            delay_ms(KEYSPEED);
                        }
                    }
                }
            }
            else if(KEY0 == 0){              //减少键
                delay_ms(10);
                if(KEY0 == 0){
                    if(part == HOUR){                  //设置小时
                        while(KEY0 == 0){
                            if(setting_calendar.hour == 0);
                            else
                                setting_calendar.hour --;
                            showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == MINUTE){             //设置分
                        while(KEY0 == 0){
                            if(setting_calendar.min == 0);
                            else
                                setting_calendar.min --;
                            showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part ==SECOND){             //设置秒  
                        while(KEY0 == 0){
                            if(setting_calendar.sec ==0);
                            else
                                setting_calendar.sec --;
                            showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
                            delay_ms(KEYSPEED);
                        }
                    }
                }
            }

            if(type != ALARM_SETTING){
                part = HOUR;
                break;
                }

            showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
        }
        RTC_Alarm_Set(setting_calendar.w_year,setting_calendar.w_month,setting_calendar.w_date,setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
        showNextAlarm(setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
        clearAlarmEditStatus();
        showTest("                     ");
        settingFlag = 0;
    }
}
void editClock(void){
    if(type == CLOCK_SETTING){
        setting_calendar = calendar;  //设置时钟对齐实时时钟
        settingFlag = 1;
        showTest("Editing clock:       ");
        while(1){
            showClockEditStatus(part);
            if(KEY_UP == 1){               //按下KEY_UP进行手动校时模式切换
                delay_ms(10);
                if(KEY_UP == 1){
                    if(part == DAY){
                        part = HOUR;
                        type = NONE;  //变成时钟设置模式
                    }
                    else
                        part ++;
                }
                while(KEY_UP == 1);
            }

            else if(KEY1 == 0){          //增加键
                delay_ms(10);
                if(KEY1 == 0){
                    if(part == HOUR){                  //设置小时
                        while(KEY1 == 0){
                            if(setting_calendar.hour == 23);
                            else
                                setting_calendar.hour ++;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == MINUTE){             //设置分
                        while(KEY1 == 0){
                            if(setting_calendar.min == 59);
                            else
                                setting_calendar.min ++;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part ==SECOND){             //设置秒  
                        while(KEY1 == 0){
                            if(setting_calendar.sec ==59);
                            else
                                setting_calendar.sec ++;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == YEAR){
                        while(KEY1 == 0){
                            if(setting_calendar.w_year == 2099);//最大到2099年
                            else
                                setting_calendar.w_year ++;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == MONTH){
                        while(KEY1 == 0){
                            if(setting_calendar.w_month ==12);
                            else
                                setting_calendar.w_month ++;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == DAY){
                        while(KEY1 == 0){
                            if(setting_calendar.w_date == getMaxDayInMonth(setting_calendar.w_year,setting_calendar.w_month));
                            else
                                setting_calendar.w_date ++;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                }
            }
            else if(KEY0 == 0){              //减少键
                delay_ms(10);
                if(KEY0 == 0){
                    if(part == HOUR){                  //设置小时
                        while(KEY0 == 0){
                            if(setting_calendar.hour == 0);
                            else
                                setting_calendar.hour --;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == MINUTE){             //设置分
                        while(KEY0 == 0){
                            if(setting_calendar.min == 0);
                            else
                                setting_calendar.min --;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part ==SECOND){             //设置秒  
                        while(KEY0 == 0){
                            if(setting_calendar.sec ==0);
                            else
                                setting_calendar.sec --;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == YEAR){
                        while(KEY0 == 0){
                            if(setting_calendar.w_year == 2021);//最小到2021年
                            else
                                setting_calendar.w_year --;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == MONTH){
                        while(KEY0 == 0){
                            if(setting_calendar.w_month ==1);
                            else
                                setting_calendar.w_month --;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                    else if(part == DAY){
                        while(KEY0 == 0){
                            if(setting_calendar.w_date == 1);
                            else
                                setting_calendar.w_date --;
                            showAll(setting_calendar);
                            delay_ms(KEYSPEED);
                        }
                    }
                }
            }

            if(type != CLOCK_SETTING)
                break;

            showAll(setting_calendar);
        }
        RTC_Set(setting_calendar.w_year,setting_calendar.w_month,setting_calendar.w_date,setting_calendar.hour,setting_calendar.min,setting_calendar.sec);
        showAll(setting_calendar);
        clearClockEditStatus();
        if(alarmIsOpen)					//立即更改提示
				showTest("Alarm function: Open ");
			else
				showTest("Alarm function: Close");
        settingFlag = 0;
    }
}
