#ifndef _LED_H
#define _LED_H

#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define ALL_LED 4

#define HIGH 0
#define LOW 1

//num led标号
//flag 亮灭
void Led_init(void);
void Led( unsigned char num , unsigned char flag );
void Delay_Led(void);

#endif
