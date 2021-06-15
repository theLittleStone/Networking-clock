
#include "stm32f10x.h"
#include "display.h"
#include "lcd.h"
#include "rtc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "SHT2x.h"
#include "timedit.h"

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

void showWeek(_calendar_obj cal){
    char *str;
    switch(cal.week){
        case 0: str = "Sunday   "; break;
        case 1: str = "Monday   "; break;
        case 2: str = "Tuesday  "; break;
        case 3: str = "Wednesday"; break;
        case 4: str = "Thursday "; break;
        case 5: str = "Friday   "; break;
        case 6: str = "Saturday "; break;
    }
    LCD_ShowString(96,116,240,16,16,str);
}

void clearWeek(void){
    LCD_ShowString(96,116,240,16,16,"         ");
}

void showTime(_calendar_obj cal){
    char str[20];
    sprintf(str, "%02d : %02d : %02d", cal.hour, cal.min, cal.sec);
    LCD_ShowString(48,50,240,24,24,str);
}

void clearTime(void){
    LCD_ShowString(48,50,240,24,24,"                  ");
}

void showDate(_calendar_obj cal){
    char str[20];
    sprintf(str, "%04d.%02d.%02d", (int)cal.w_year, (int)cal.w_month, (int)cal.w_date);
    LCD_ShowString(81,86,240,16,16,str);
}

void clearDate(void){
    LCD_ShowString(81,86,240,16,16,"              ");
}

void showAll(_calendar_obj cal){ 
    showTime(cal);
    showDate(cal);
    showWeek(cal);
}

void clearAll(void){
    clearTime();
    clearDate();
    clearWeek();
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

void clearNextAlarm(void){
    LCD_ShowString(60,240,240,12,12,"                              ");
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
    LCD_ShowString(78,140,240,16,16,str1);
    LCD_ShowString(78,160,240,16,16,str2);
}

//显示闹钟校时时的标志
void showAlarmEditStatus(enum settingPart part){
    switch(part){
        case HOUR:
            LCD_ShowChar(135,252,'*',12,0);
            LCD_ShowChar(195,252,' ',12,0);
            break;
        case MINUTE:
            LCD_ShowChar(165,252,'*',12,0);
            LCD_ShowChar(135,252,' ',12,0);
            break;
        case SECOND:
            LCD_ShowChar(195,252,'*',12,0);
            LCD_ShowChar(165,252,' ',12,0);
            break;
    }
}

void clearAlarmEditStatus(void){
    LCD_ShowChar(135,252,' ',12,0);
    LCD_ShowChar(165,252,' ',12,0);
    LCD_ShowChar(195,252,' ',12,0);
}

void showClockEditStatus(enum settingPart part){
    switch(part){
        case HOUR:
            LCD_ShowChar(195,252,' ',12,0);
            LCD_ShowChar(57,72,'*',16,0);
            break;
        case MINUTE:
            LCD_ShowChar(57,72,' ',16,0);
            LCD_ShowChar(117,72,'*',16,0);
            break;
        case SECOND:
            LCD_ShowChar(117,72,' ',16,0);
            LCD_ShowChar(177,72,'*',16,0);
            break;
        case YEAR:
            LCD_ShowChar(177,72,' ',16,0);
            LCD_ShowChar(93,100,'*',12,0);
            break;
        case MONTH:
            LCD_ShowChar(93,100,' ',12,0);
            LCD_ShowChar(125,100,'*',12,0);
            break;
        case DAY:
            LCD_ShowChar(125,100,' ',12,0);
            LCD_ShowChar(150,100,'*',12,0);
            break;
    }

}
void clearClockEditStatus(void){
    LCD_ShowChar(93,100,' ',12,0);
    LCD_ShowChar(125,100,' ',12,0);
    LCD_ShowChar(150,100,' ',12,0);
}