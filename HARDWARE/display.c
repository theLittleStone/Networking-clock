
#include "display.h"

extern _calendar_obj calendar; //声明外部变量

void showTest(char *str){
    LCD_ShowString(60, 220,240,12,12,str);
}
void clearTest(void){
    LCD_ShowString(80,220,240,12,12,"                             ");
}

void showWeek(void){
    char *str;
    switch(calendar.week){
        case 0: str = "Sunday   "; break;
        case 1: str = "Monday   "; break;
        case 2: str = "Tuesday  "; break;
        case 3: str = "Wednesday"; break;
        case 4: str = "Thursday "; break;
        case 5: str = "Friday   "; break;
        case 6: str = "Saturday "; break;
    }
    LCD_ShowString(96,106,240,16,16,str);
    
}

void showTime(void){
    char str[20];
    sprintf(str, "%02d : %02d : %02d", calendar.hour, calendar.min, calendar.sec);
    LCD_ShowString(48,50,240,24,24,str);
}
void showDate(void){
    char str[20];
    sprintf(str, "%04d.%02d.%02d", (int)calendar.w_year, (int)calendar.w_month, (int)calendar.w_date);
    LCD_ShowString(81,86,240,16,16,str);
}

void showAll(void){ 
    showTime();
    showDate();
    showWeek();
}

//显示特定的信息, 想要清除用clearMessage函数, 不要直接覆盖
void showMessage(enum Message mes){
    switch(mes){
        case GettingTime: 
        LCD_ShowString(38,180,240,12,12,"Updating time from internet"); break;
        case GetTimeSuccessfully:
        LCD_ShowString(56,180,240,12,12,"Get time successfully"); break;
        case FailToGetTime:
        LCD_ShowString(70,180,240,12,12,"Fail to get time"); break;
    }
}

//清除showMessage函数
//全是空白字符串才正常
void clearMessage(enum Message mes){
    switch(mes){
        case GettingTime:
        LCD_ShowString(38,180,240,12,12,"                           "); break;
        case GetTimeSuccessfully:
        LCD_ShowString(56,180,240,12,12,"                     "); break;
        case FailToGetTime:
        LCD_ShowString(70,180,240,12,12,"                "); break;
    }
}

void showNextAlarm(uint8_t hour, uint8_t min, uint8_t sec){
    char str[35];
    sprintf(str, "Next alarm: %02d : %02d : %02d", hour, min, sec);
    LCD_ShowString(60,240,240,12,12,str);
}

void showAlarming(void){
    LCD_ShowString(80,260,240,12,12,"Alarming");
}
void clearAlarming(void){
    LCD_ShowString(80,260,240,12,12,"        ");
}