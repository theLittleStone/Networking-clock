#ifndef __TIMEDIT_H__
#define __TIMEDIT_H__
#include "rtc.h"
extern _calendar_obj setting_calendar;
extern enum settingType type;
extern enum settingPart part;

#define KEYSPEED 200
//设定模式

//设定部分

void editAlarm(void);
void editClock(void);
#endif
