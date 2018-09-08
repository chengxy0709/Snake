#ifndef _KEY_H
#define _KEY_H

#define NOKEY	0
#define LEFT	1
#define DOWN	2
#define UP		3
#define RIGHT	4
#define BACK	5
#define MENU	6
#define ALL		7

#define INT_LEFT NUM_EINT2
#define INT_DOWN NUM_EINT3
#define INT_ELSE NUM_EINT16_31

void key_pinit(void);//轮询查找初始化
unsigned char key_polling(void);//轮询查找键值
void key_iinit(unsigned char num);
void int_clearflag(unsigned char num);
//for EINT 16-19
unsigned char check_int(void);

void isr_key_left(void);
void isr_key_down(void);
void isr_key_else(void);

#endif