#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "usart2.h"
#include "stdio.h"
//unsigned char res[100];
u8 USART_RX_BUF2[512];
u16 USART_RX_STA2;

void USART2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //GPIO时钟    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);  //串口外设时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //推挽复用输出        
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;                   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;  //浮空输入       
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;                 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;           
  GPIO_Init(GPIOA,&GPIO_InitStructure); 

	USART_InitStructure.USART_BaudRate = 115200  ;  //波特率,这里改为115200与ESP8266通信 
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;  //数据帧字长 8位  
	USART_InitStructure.USART_StopBits=USART_StopBits_1;  //配置停止位 1个	
	USART_InitStructure.USART_Parity=USART_Parity_No;  //校验位，无校验位  
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  //不使用用硬件流控制    
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  //收发一体                          
	USART_Init(USART2,&USART_InitStructure);  //完成初始化      
	
	USART_Cmd(USART2,ENABLE);  //使能串口
	

	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);  //使能串口中断  
	
	//优先级配置
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 
	NVIC_Init(&NVIC_InitStructure);       
	
}

void USART2_SendByte(uint8_t ch)
{
	//先读取TC值状态，使之读取后清零，避免第一个字节丢失
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	USART_SendData(USART2, ch);//向串口2发送数据
}

void USART2_SendString(char *str)
{
	unsigned int k=0;
	//先执行，后判断  （目前与先判断后执行效果一样）
	do
	{
		USART2_SendByte(*(str+k));
		k++;
	}while(*(str+k)!='\0'); // null字符
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
}

int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}


void USART2_IRQHandler(void)
{
	u8 Res;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		
		if((USART_RX_STA2&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA2&0x4000)//接收到了0x7D}
			{
				if(Res!=0x7D)
					USART_RX_STA2=0;//接收错误,重新开始
				else 
					USART_RX_STA2|=0x8000;	//接收完成了 
			}
			else //还没收到0X7D }
			{	
				if(Res==0x7D)
					USART_RX_STA2|=0x4000;
				else
				{
					USART_RX_BUF2[USART_RX_STA2&0X3FFF]=Res ;
					USART_RX_STA2++;
					if(USART_RX_STA2>(1024-1))USART_RX_STA2=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
    } 

} 
