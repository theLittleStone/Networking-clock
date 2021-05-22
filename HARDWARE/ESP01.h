#ifndef __ESP01_H
#define __ESP01_H

#define RST_CTRL 		GPIOB
#define EN_CTRL			GPIOB
#define RST_PIN 		GPIO_Pin_4
#define EN_PIN  		GPIO_Pin_3

#define RST_ON 			GPIO_ResetBits(GPIOB,RST_PIN)
#define RST_OFF 		GPIO_SetBits(GPIOB,RST_PIN)

#define EN_ON 			GPIO_SetBits(GPIOB,EN_PIN)
#define EN_OFF 			GPIO_ResetBits(GPIOB,EN_PIN)

void ESP01_Init(void);
//void ESP01_Open(void);
void ESP01_ConnectWiFi(char *name, char *pin);
void ESP01_Gettime(void);
void ESP01_Settime(void);
void ESP01_Getweather(void);
uint8_t Test_Connect(void);

#endif
