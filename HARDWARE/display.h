#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "rtc.h"
#include "timedit.h"

enum Message{
    GettingTime = 0,
    GetTimeSuccessfully = 1,
    FailToGetTime = 2
};
enum settingType{
    NONE = 0, ALARM_SETTING, CLOCK_SETTING
};
enum settingPart{
    HOUR = 0, MINUTE, SECOND, YEAR, MONTH, DAY
};



void showTime(_calendar_obj cal);
void clearTime(void);
void showDate(_calendar_obj cal);
void clearDate(void);
void showWeek(_calendar_obj cal);
void clearWeek(void);
void showAll(_calendar_obj cal);
void clearAll(void);
void showMessage(enum Message mes);
void clearMessage(enum Message mes);
void showTest(char *str);
void showSPrint(void);
void clearTest(void);
void showNextAlarm(uint8_t hour, uint8_t min, uint8_t sec);
void clearNextAlarm(void);
void showAlarming(void);
void clearAlarming(void);
void showH_T(void);
void showClockEditStatus(enum settingPart part);
void clearClockEditStatus(void);
void showAlarmEditStatus(enum settingPart part);
void clearAlarmEditStatus(void);
#endif
