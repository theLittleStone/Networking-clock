
#include "stm32f10x.h"
#include "display.h"
#include "lcd.h"
#include "rtc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "SHT2x.h"

extern _calendar_obj calendar; //声明外部变量

void showTest(char *str){
    LCD_ShowString(60, 220,240,12,12,str);
}

void showSPrint(void){
    char str[20]="23.57";
    float a = 23.5679;
    int b = (int)a;
    a -= b;
    a *= 100;
    sprintf(str, "%d.%d",b,(int)a);
    showTest(str);
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
//显示湿度与温度
void showH_T(void){     
    float temp,humi;
    int tmp;
    char str1[20],str2[20];
    temp = SHT2x_MeasureTempPoll();               //由于未知原因, 串口通信后(可能是用过printf)sprintf在转换 
    tmp = (int)temp;                              //float型时会直接把小数部分直接丢掉, 所以使用传统方法进行转换
    temp = 100*(temp-tmp);
    sprintf(str1, "Temp: %02d.%02d", tmp, (int)temp);
    humi = SHT2x_MeasureHumiPoll();
    tmp = (int)humi;
    humi = 100*(humi-tmp);
    sprintf(str2, "Humi: %02d.%02d%%", tmp, (int)humi);
    LCD_ShowString(78,130,240,16,16,str1);
    LCD_ShowString(78,150,240,16,16,str2);
}