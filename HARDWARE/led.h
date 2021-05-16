#ifndef __LED_H
#define __LED_H



#define LED_CTRL0 		GPIOA
#define LED0_PIN 			GPIO_Pin_12

//�˴��������ΪON
#define LED0_OFF 			GPIO_ResetBits(LED_CTRL0,LED0_PIN)
#define LED0_ON 			GPIO_SetBits(LED_CTRL0,LED0_PIN)

void led_Init(void);

#endif
