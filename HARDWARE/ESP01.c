#include "stm32f10x.h"
#include "delay.h"
#include "ESP01.h"
#include "usart2.h"
#include "usart3.h"
#include "rtc.h"
#include "key.h"
#include "MP3.h"
#include "string.h"
#include "stdio.h"
#include "display.h"

unsigned char time_data[19];
extern u16 USART_RX_STA;

u16 year;
u8 month,day,hour,minute,second;


//不使用EN RST，直接上电，简化流程
/*
void ESP01_Init(void)
{
	
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RST_CTRL,&GPIO_InitStructure);
	RST_OFF;
	
	GPIO_InitStructure.GPIO_Pin = EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EN_CTRL,&GPIO_InitStructure);
	EN_OFF;
}
*/
uint8_t Test_Connect(void){
	char str[10];
	memset(USART_RX_BUF2,'\0',sizeof(USART_RX_BUF2));// 清空字符串
	USART_RX_STA2=0x0000;
	printf("AT+CWJAP?\r\n");
	delay_ms(200);
	memmove(str, USART_RX_BUF2+10, 9);
	showTest(str);
	memset(USART_RX_BUF2,'\0',sizeof(USART_RX_BUF2));// 清空字符串
	return 0;
}

void getOnlineTime(void){
	showMessage(GettingTime);
	memset(USART_RX_BUF2,'\0',sizeof(USART_RX_BUF2));// 清空字符串
	//Uart_SendCMD(0x12,0,0x0f);  //提醒正在校时
	ESP01_Gettime();		
	delay_ms(300);
	
	/*for(uint16_t i=69;i<512;i++)
	{
		USART1_SendByte(USART_RX_BUF2[i]);  //调试
	}*/
	
	if(USART_RX_BUF2[64]==0x32)
	{
		ESP01_Settime();

		//Uart_SendCMD(0x12,0,0x10);  //校时成功
		clearMessage(GettingTime);
		showMessage(GetTimeSuccessfully);
		delay_ms(100);
		//while(BUSY!=1);
		delay_ms(3000);
		clearMessage(GetTimeSuccessfully);
		//Readtime(calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);  //读时间
		memset(USART_RX_BUF2,'\0',sizeof(USART_RX_BUF2));// 清空字符串
	}
	else 
	{	
		//Uart_SendCMD(0x12,0,0x11); //提醒校时失败，检查网络环境
		clearMessage(GettingTime);
		showMessage(FailToGetTime);
		delay_ms(3000);
		//while(BUSY!=1);		
		clearMessage(FailToGetTime);	
		memset(USART_RX_BUF2,'\0',sizeof(USART_RX_BUF2));// 清空字符串	
	}		
}

void ESP01_ConnectWiFi(char *name, char *pin)//wifi名, 密码
{
	char *str;
	//EN_ON;
	delay_ms(50);
	
	printf("AT+CWMODE=1\r\n");
	delay_ms(50);
	//RST_ON;
	delay_ms(100);
	//RST_OFF;
	delay_ms(50);
	
	USART_RX_STA2=0x0000;
	printf(str,"AT+CWJAP=\"%s\",\"%s\"\r\n",name,pin);//接入申请
	delay_ms(1000);  //注意delay时间限制
	delay_ms(1000);
	delay_ms(1000);
	
}

void ESP01_Gettime(void)
{
	printf("+++\r\n");
	delay_ms(500);
//	printf("AT+RST\r\n");
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);


	printf("AT+CIPMUX=0\r\n");
	delay_ms(500);
	
	printf("AT+CIPSTART=\"TCP\",\"api.k780.com\",80\r\n");
	delay_ms(1600);
	
	printf("AT+CIPMODE=1\r\n");
	delay_ms(500);
	
	printf("AT+CIPSEND\r\n");
	delay_ms(500);
	USART_RX_STA2=0x0000;  //使数据从数组头开始记录
	printf("GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json&HTTP/1.1\r\n");
	delay_ms(1600);
}

void ESP01_Settime(void)
{
	int ESPyear;
	uint8_t ESPmon,ESPday,ESPhou,ESPmin,ESPsec;
	ESPyear=((USART_RX_BUF2[64]-'0')*1000+(USART_RX_BUF2[65]-'0')*100+(USART_RX_BUF2[66]-'0')*10+(USART_RX_BUF2[67]-'0'));
	ESPmon=((USART_RX_BUF2[69]-'0')*10+(USART_RX_BUF2[70]-'0'));
	ESPday=((USART_RX_BUF2[72]-'0')*10+(USART_RX_BUF2[73]-'0'));
	ESPhou=((USART_RX_BUF2[75]-'0')*10+(USART_RX_BUF2[76]-'0'));
	ESPmin=((USART_RX_BUF2[78]-'0')*10+(USART_RX_BUF2[79]-'0'));
	ESPsec=((USART_RX_BUF2[81]-'0')*10+(USART_RX_BUF2[82]-'0'));
	
	//因为解析完成的时间总比发送时的慢些, 所以手动补偿
	//如果不幸(幸运)地在23:59:56之后校时, 则不进行补偿
	if(ESPsec < 55 && ESPhou != 23){
		ESPsec += 5;
	}
	else{
		ESPsec = ESPsec - 60 + 5;
		if(ESPmin == 59){
			ESPmin = 0;
			ESPhou++;
		}
		else{
			ESPmin++;
		}
	}
	

	RTC_Set(ESPyear,ESPmon,ESPday,ESPhou,ESPmin,ESPsec);
}
