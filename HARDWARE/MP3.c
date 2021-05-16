#include "MP3.h"
#include "usart3.h"
#include "stm32f10x.h"
#include "delay.h"

static uint8_t Send_buf[10] = {0} ;  

void MP3_Init(void)
{
	USART3_Init();  //初始化其通讯串口
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DoSum( uint8_t *Str, uint8_t len)
{
    uint16_t xorsum = 0;
    uint8_t i;

    for(i=0; i<len; i++)
    {
        xorsum  = xorsum + Str[i];
    }
	xorsum     = 0 -xorsum;
	*(Str+i)   = (uint8_t)(xorsum >>8);
	*(Str+i+1) = (uint8_t)(xorsum & 0x00ff);
}

void SendCmd(uint8_t len)
{
    uint8_t i = 0 ;

    USART3_SendByte(0x7E); //起始
    for(i=0; i<len; i++)//数据
    {
		USART3_SendByte(Send_buf[i]) ;
    }
    USART3_SendByte(0xEF) ;//结束
}

void Uart_SendCMD(uint8_t CMD ,uint8_t feedback , uint16_t dat)
{
    Send_buf[0] = 0xff;    //保留字节 
    Send_buf[1] = 0x06;    //长度
    Send_buf[2] = CMD;     //控制指令
    Send_buf[3] = feedback;//是否需要反馈
    Send_buf[4] = (uint8_t)(dat >> 8);//datah
    Send_buf[5] = (uint8_t)(dat);     //datal
    DoSum(&Send_buf[0],6);        //校验
    SendCmd(8);       //发送此帧数据
}

void Readtime(uint8_t mon,uint8_t day,uint8_t hour, uint8_t min, uint8_t sec)
{
	
	Uart_SendCMD(0x12,0,0x0b);  //现在时间是
	delay_ms(100);  //使MP3模块有时间拉低BUSY信号
	while(BUSY!=1);
	
	//读月份
	if(mon/10!=0)
	{
		Uart_SendCMD(0x12,0,0x0a);
		delay_ms(100);
		while(BUSY!=1);
	}
	
	Uart_SendCMD(0x12,0,mon%10);
	delay_ms(100);
	while(BUSY!=1);
	Uart_SendCMD(0x12,0,0x12);
	delay_ms(100);
	while(BUSY!=1);
	
	//读日
	if(day/10!=0)
	{
		Uart_SendCMD(0x12,0,day/10);
		delay_ms(100);
		while(BUSY!=1);
		Uart_SendCMD(0x12,0,0x0a);
		delay_ms(100);
		while(BUSY!=1);
	}
	
	Uart_SendCMD(0x12,0,day%10);
	delay_ms(100);
	while(BUSY!=1);
	Uart_SendCMD(0x12,0,0x13);
	delay_ms(100);
	while(BUSY!=1);
	
	
	//读时
	if(hour/10!=0)
	{
		Uart_SendCMD(0x12,0,0x0a);
		delay_ms(100);
		while(BUSY!=1);
	}
	
	Uart_SendCMD(0x12,0,hour%10);
	delay_ms(100);
	while(BUSY!=1);
	
	Uart_SendCMD(0x12,0,0x0c);
	delay_ms(100);
	while(BUSY!=1);
	
	//读分
	if(min/10!=0)
	{
		Uart_SendCMD(0x12,0,min/10);
		delay_ms(100);
		while(BUSY!=1);
		Uart_SendCMD(0x12,0,0x0a);
		delay_ms(100);
		while(BUSY!=1);
	}
	
	Uart_SendCMD(0x12,0,min%10);
	delay_ms(100);
	while(BUSY!=1);
	Uart_SendCMD(0x12,0,0x0d);
	delay_ms(100);
	while(BUSY!=1);
	
	//读秒
	if(sec/10!=0)
	{
		Uart_SendCMD(0x12,0,sec/10);
		delay_ms(100);
		while(BUSY!=1);
		Uart_SendCMD(0x12,0,0x0a);
		delay_ms(100);
		while(BUSY!=1);
	}
	Uart_SendCMD(0x12,0,sec%10);
	delay_ms(100);
	while(BUSY!=1);
	
	Uart_SendCMD(0x12,0,0x0e);
	
}
