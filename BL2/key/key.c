#include "key.h"
#include "stdio.h"
#include "uart.h"

#define GPH0CON		0xe0200c00
#define GPH0DAT		0xe0200c04
#define GPH2CON 	0xe0200c40
#define GPH2DAT 	0xe0200c44

#define rGPH0CON	*((volatile unsigned int *)GPH0CON)
#define rGPH2CON	*((volatile unsigned int *)GPH2CON)
#define rGPH0DAT	*((volatile unsigned int *)GPH0DAT)
#define rGPH2DAT	*((volatile unsigned int *)GPH2DAT)

//interrupt EINT 2,3,16,17,18,19
#define EXT_INT_0_CON	0xe0200e00
#define EXT_INT_0_MASK	0xe0200f00
#define EXT_INT_0_PEND	0xe0200f40
#define EXT_INT_2_CON	0xe0200e08
#define EXT_INT_2_MASK	0xe0200f08
#define EXT_INT_2_PEND	0xe0200f48

#define rEXT_INT_0_CON	*((unsigned int *)EXT_INT_0_CON)
#define rEXT_INT_0_MASK	*((unsigned int *)EXT_INT_0_MASK)
#define rEXT_INT_0_PEND	*((unsigned int *)EXT_INT_0_PEND)
#define rEXT_INT_2_CON	*((unsigned int *)EXT_INT_2_CON)
#define rEXT_INT_2_MASK	*((unsigned int *)EXT_INT_2_MASK)
#define rEXT_INT_2_PEND	*((unsigned int *)EXT_INT_2_PEND)


#define rMENU		((rGPH2DAT>>3)&0x1)
#define rRIGHT		((rGPH2DAT>>1)&0x1)
#define rBACK		((rGPH2DAT>>2)&0x1)
#define rUP			((rGPH2DAT>>0)&0x1)
#define rLEFT		((rGPH0DAT>>2)&0x1)
#define rDOWN		((rGPH0DAT>>3)&0x1)

void delay_key(void){

	volatile int i=20;
	volatile int j=10000;

	for(;i>0;i--)
		for(j = 10000;j>0;j--);

}

void key_pinit(void){

	rGPH0CON &= ~(0xFF<<8);
	rGPH2CON &= ~(0xFFFF<<0);

}

void key_iinit(unsigned char num){

	if( num<3 && num>0 ){
		rGPH0CON |= (0xf<<(4*(num+1)));
		rEXT_INT_0_CON &= ~(0X7<<(4*(num+1)));
		rEXT_INT_0_CON |= (0X2<<(4*(num+1)));//下降沿触发
		rEXT_INT_0_PEND |= (0x1<<(num+1)); 
		rEXT_INT_0_MASK &= ~(0x1<<(num+1));
	}else if( num<7 && num>0 ){
		rGPH2CON |= (0xf<<(4*(num-3)));
		rEXT_INT_2_CON &= ~(0X7<<(4*(num-3)));
		rEXT_INT_2_CON |= (0X2<<(4*(num-3)));//下降沿触发
		rEXT_INT_2_PEND |= (0x1<<(num-3)); 
		rEXT_INT_2_MASK &= ~(0x1<<(num-3));
	}else if( num == 7 ){
		rGPH0CON |= (0xff<<8);
		rGPH2CON |= (0xffff<<0);
		rEXT_INT_0_CON &= ~(0X77<<8);
		rEXT_INT_0_CON |= (0X22<<8);//下降沿触发
		rEXT_INT_0_PEND |= (0x3<<2); 
		rEXT_INT_0_MASK &= ~(0x3<<2);
		rEXT_INT_2_CON &= ~(0X7777<<0);
		rEXT_INT_2_CON |= (0X2222<<0);//下降沿触发
		rEXT_INT_2_PEND |= (0x0f<<0); 
		rEXT_INT_2_MASK &= ~(0x0f<<0);
	}else{
		
	}

}

void int_clearflag(unsigned char num){

	if( num<3 && num>0 ){
		rEXT_INT_0_PEND |= (0x1<<(num+1)); 
	}else if( num<7 && num>0 ){
		rEXT_INT_2_PEND |= (0x1<<(num-3)); 
	}else if( num == 7 ){
		rEXT_INT_0_PEND |= (0x3<<2); 
		rEXT_INT_2_PEND |= (0x0f<<0); 
	}else{
		
	}

}

//for EINT 16-19
unsigned char check_int(void){
	
	if( rEXT_INT_2_PEND & 0x01 )
		return UP;
	else if( rEXT_INT_2_PEND & 0x02 )
		return RIGHT;
	else if( rEXT_INT_2_PEND & 0x04 )
		return BACK;
	else if( rEXT_INT_2_PEND & 0x08 )
		return MENU;
	else
		return NOKEY;
	
}

unsigned char key_polling(void){

	if( !rMENU ){
		delay_key();
		if( !rMENU ){
			return MENU;
		}
	}
	else if( !rBACK ){
		delay_key();
		if( !rBACK ){
			return BACK;
		}
	}
	else if( !rUP ){
		delay_key();
		if( !rUP ){
			return UP;
		}
	}
	else if( !rDOWN ){
		delay_key();
		if( !rDOWN ){
			return DOWN;
		}
	}
	else if( !rLEFT ){
		delay_key();
		if( !rLEFT ){
			return LEFT;
		}
	}
	else if( !rRIGHT ){
		delay_key();
		if( !rRIGHT ){
			return RIGHT;
		}
	}
	else 
		return NOKEY;

}


/*void isr_key_left(void){
	
	printf("LEFT\n");
	int_clearflag(LEFT);
	
}
void isr_key_down(void){
	
	printf("DOWN\n");
	int_clearflag(DOWN);
	
}
void isr_key_else(void){
	
	if( check_int() == UP )
		printf("UP\n");
	else if( check_int() == RIGHT )
		printf("RIGHT\n");
	else if( check_int() == BACK )
		printf("BACK\n");
	else if( check_int() == MENU )
		printf("MENU\n");
	else
		printf("NOKEY\n");
	int_clearflag(ALL);
	
}*/
















