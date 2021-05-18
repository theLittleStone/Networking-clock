#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "lcd.h"
#include "rtc.h"
#include "stdio.h"
#include "stdlib.h"

enum Message{
    GettingTime = 0,
    GetTimeSuccessfully = 1,
    FailToGetTime = 2
};
enum Alarm{
    Beeping = 0,
    NextAlarm = 1
};

void showTime(void);
void showDate(void);
void showWeek(void);
void showAll(void);
void showMessage(enum Message mes);
void clearMessage(enum Message mes);
void showTest(char *str);
void clearTest(void);
void showAlarm(enum Alarm al);
#endif
