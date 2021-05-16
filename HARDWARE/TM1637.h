#ifndef   __TM1637_H
#define   __TM1637_H

#include "stm32f10x.h"
//#include "sys.h"

//与库函数操作取一个
#define 	 SDA_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)8<<28;}		//CRL7-0  CRH15-8  从右向左的哪个值为0，对应控制哪个端口
#define 	 SDA_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)3<<28;}  	//第28-31位先清0，后变为1000或0010，代表浮空输入或推挽输出

#define    TM_SCL_PORT    	GPIOA			              
#define    TM_SCL_CLK 	    RCC_APB2Periph_GPIOA		
#define    TM_SCL_PIN		  	GPIO_Pin_5
		
#define    TM_DIO_PORT    	GPIOA		                 
#define    TM_DIO_CLK 	    RCC_APB2Periph_GPIOA		
#define    TM_DIO_PIN				GPIO_Pin_7

#define    TM_SCL 		PAout(5)
#define    TM_SDA 		PAout(7)

#define    READ_SDA 	PAin(7)

void TM_Init(void);
void TM_Start(void);
void TM_Stop(void);
void TM_Wait_Ask(void);
void TM_WriteByte(uint8_t txd);
void TM_Display(uint8_t *discode);
void TM_AdDisplay(uint8_t addr,uint8_t data);
	
//void SDA_IN(void);
//void SDA_OUT(void);

#endif
