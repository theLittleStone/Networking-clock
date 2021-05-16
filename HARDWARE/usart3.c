#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "usart3.h"
#include "stdio.h"

uint8_t res[20];

void USART3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //GPIO时钟    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);  //串口外设时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //推挽复用输出        
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;                   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;  //浮空输入       
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;                 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;           
  GPIO_Init(GPIOB,&GPIO_InitStructure); 

	USART_InitStructure.USART_BaudRate = 9600  ;  //波特率,这里改为9600以和MP3默认波特率匹配  
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;  //数据帧字长 8位  
	USART_InitStructure.USART_StopBits=USART_StopBits_1;  //配置停止位 1个	
	USART_InitStructure.USART_Parity=USART_Parity_No;  //校验位，无校验位  
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  //不使用用硬件流控制    
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  //收发一体                          
	USART_Init(USART3,&USART_InitStructure);  //完成初始化      
	
	USART_Cmd(USART3,ENABLE);  //使能串口
	
}

void USART3_SendByte(uint8_t ch)
{
	//先读取TC值状态，使之读取后清零，避免第一个字节丢失
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
	USART_SendData(USART3, ch);//向串口3发送数据
}

void USART3_SendString(char *str)
{
	unsigned int k=0;
	//先执行，后判断  （目前与先判断后执行效果一样）
	do
	{
		USART3_SendByte(*(str+k));
		k++;
	}while(*(str+k)!='\0'); // null字符
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
}
