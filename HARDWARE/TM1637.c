#include "TM1637.h"
#include "delay.h"



void TM_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(TM_DIO_CLK|TM_SCL_CLK,ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = TM_DIO_PIN | TM_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(TM_DIO_PORT,&GPIO_InitStructure);
	
//	TM_SCL=1;
//	TM_SDA=1;
}

void TM_Start(void)
{
	TM_SDA=1;
	delay_us(2);
	TM_SCL=1;
	delay_us(2);
	TM_SDA=0;
	delay_us(2);
	TM_SCL=0;
	delay_us(2);
}

void TM_Stop(void)
{
	TM_SCL=0;
	delay_us(2);
	TM_SDA=0;
	delay_us(2);
	TM_SCL=1;
	delay_us(2);
	TM_SDA=1;
	delay_us(2);
}

void TM_Wait_Ask(void)
{
	SDA_IN();
	unsigned char i;
	TM_SCL=0;
	delay_us(5);
	while(READ_SDA==1&&(i<250))i++;
	TM_SCL=1;
	delay_us(2);
	TM_SCL=0;
	SDA_OUT();
}

void TM_WriteByte(uint8_t txd)
{
	uint8_t i;
	for(i=0;i<8;i++)
  {
		TM_SCL=0;
		delay_us(2);
		if(txd & 0x01){
			TM_SDA=1;
		}
		else {
			TM_SDA=0;
		}
		delay_us(3);
		txd>>=1;
		TM_SCL=1;
		delay_us(3);
  }
	//TM_Wait_Ask();
}

void TM_Display(uint8_t *discode) 
{
	uint8_t i;
	
	TM_Start();
	TM_WriteByte(0x40);    //40 地址自加模式     44 固定地址模式
	TM_Wait_Ask();
	TM_Stop();
	
	TM_Start();
	TM_WriteByte(0xc0);   //首地址
	TM_Wait_Ask();
	
	for(i=0;i<4;i++)
	{
		TM_WriteByte(*(discode+i));  //依次发送数组数据
		TM_Wait_Ask();
	}
	TM_Stop();
	
	TM_Start();
	TM_WriteByte(0x89);   //亮度
	TM_Wait_Ask();
	TM_Stop();
}

void TM_AdDisplay(uint8_t addr,uint8_t data)
{
	TM_Start();
	TM_WriteByte(0x44);
	TM_Wait_Ask();
	TM_Stop();
	
	TM_Start();
	TM_WriteByte(addr);
	TM_Wait_Ask();
	TM_WriteByte(data);
	TM_Wait_Ask();
	TM_Stop();
	
	TM_Start();
	TM_WriteByte(0x8d);   //亮度
	TM_Wait_Ask();
	TM_Stop();
}
