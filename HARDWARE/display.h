#ifndef __DISPLAY_H__
#define __DISPLAY_H__


enum Message{
    GettingTime = 0,
    GetTimeSuccessfully = 1,
    FailToGetTime = 2
};

void showTime(void);
void showDate(void);
void showWeek(void);
void showAll(void);
void showMessage(enum Message mes);
void clearMessage(enum Message mes);
void showTest(char *str);
void showSPrint(void);
void clearTest(void);
void showNextAlarm(uint8_t hour, uint8_t min, uint8_t sec);
void showAlarming(void);
void clearAlarming(void);
void showH_T(void);
#endif
