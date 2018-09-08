
#include "stdio.h"
#include "led.h"
#include "uart.h"
#include "interrupt.h"
#include "key.h"
#include "lcd.h"
#include "rtc.h"
#include "s5pv210io.h"
#include "snake.h"

char DirFlag = UP;
char Rand[10];
char rand_i;

void SnakeDelayMs(uint32 time){
	
	delay_ms(time);
	
}

int16 Snake_Random(){
		
	rand_i = (rand_i+1)%10;
	
	return Rand[rand_i];
	
}

void ShowPoint( uint16 x, uint16 y , uint8 sw  ){
	if( sw )
		Draw_point(x,y,GREEN);
	else
		Draw_point(x,y,BLACK);
}
void ShowString( uint16 x, uint16 y , uint8 *str ){
	Draw_String_8_16(x,y,BLUE,str);
}
void ShowNum( uint16 x, uint16 y , uint32 num ){
	Draw_Number(x,y,num,RED);
}
int8 GetInstruction(){
	
	return DirFlag;
	
}

void main(){
	
	system_init_exception();
	Led_init();
	uart_init();
	Lcd_init();
	key_iinit(ALL);
	intenable_init(INT_LEFT);
	intenable_init(INT_DOWN);
	intenable_init(INT_ELSE);
	intSetAdd(INT_LEFT,isr_key_left );
	intSetAdd(INT_DOWN,isr_key_down );
	intSetAdd(INT_ELSE,isr_key_else );
	DirFlag = UP;
	Rand[0] = 175;Rand[0] = 100;Rand[0] = 125;Rand[0] = 200;Rand[0] = 300;
	Rand[0] = 25;Rand[0] = 75;Rand[0] = 150;Rand[0] = 50;Rand[0] = 250;
	rand_i = 0;
    while(1){
		BulidMap( 10 , 10 , WALL_W );
		GameInit();
		GameIng();
	}
	
	
}
void isr_key_left(void){
	
	DirFlag = SLEFT;
	int_clearflag(LEFT);
	
}
void isr_key_down(void){
	
	DirFlag = SDOWN;
	int_clearflag(DOWN);
	
}
void isr_key_else(void){
	
	if( check_int() == UP )
		DirFlag = SUP;
	else if( check_int() == RIGHT )
		DirFlag = SRIGHT;
	else if( check_int() == BACK )
		DirFlag = SENDGAME;
	else if( check_int() == MENU ){
		DirFlag = SPAUSE;
	}
	else
		printf("NOKEY\n");
	int_clearflag(ALL);
	
}

int raise(int signum){
	
	return 0;
	
}