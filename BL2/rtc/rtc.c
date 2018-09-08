#include "rtc.h"
#include "stdio.h"

RtcTime time = {2017,12,1,1,0,0,0};

/**********************************************************/
//start PWM function
void PWMOUT2_init(void){
	
	//set GPD0_2 to PWMOUT mode
	rGPD0CON &= ~(0xf<<8);
	rGPD0CON |= (0x2<<8);
	//set prescaler1 to 66   this is 1MHz
	rTCFG0 &= ~(0xff<<8);
	rTCFG0 |= (65<<8);
	//set timer2's second prescaler to 2,this is 500KHz
	rTCFG1 &= ~(0xf<<8);
	rTCFG1 |= (1<<8);

    //set auto reload
    rTCON |= (1<<15);	
	//set PWM2 freq
	rTCNTB2 = 50;
	//set PWM2 width
	rTCMPB2 = 25;
	
	//set timer2 inverter on/off
	rTCON &= ~(1<<14);
	//set manual update
	rTCON |= (1<<13);
	rTCON &= ~(1<<13);

	//open timer2
	rTCON |= (1<<12);
	
}
//end PWM function
/**********************************************************/

/**********************************************************/
//start watch dog function
void WDOG_init(void){
	
	rWTCON = 0x00000000;
	//set prescaler1 to 65,this is 1MHz
	rWTCON &= ~(0xff<<8);
	rWTCON |= (65<<8);
	//set second prescaler to 32,this is 1/32 MHz=31250Hz
	rWTCON &= ~(0x3<<3);
	rWTCON |= (1<<3);
	
	
	rWTDAT = 31250;
	rWTCNT = 31250;
	
	
	//disable WatchDog Timer Interrupt 
	rWTCON |= (1<<2);
	//asserts reset while watchDog timer out
	rWTCON |= (1<<0);
	
	//open WatchDog Timer 
	rWTCON |= (1<<5);
	
}
//end watch dog function 
/*********************************************************/

/*********************************************************/
//start rtc function
static unsigned int BCDtoNUM(unsigned int bcd){
	
	return ((bcd&0x0f)+((bcd&0xf0)>>4)*10);
}

static unsigned int NUMtoBCD(unsigned int num){
	
	return (((num/10)<<4)|(num%10));
}

void rtc_read(RtcTime *p){

	//open rtc read write switch
	rRTCCON |= (1<<0);
	
	p->second = BCDtoNUM(rBCDSEC);
	p->minute = BCDtoNUM(rBCDMIN);
	p->hour = BCDtoNUM(rBCDHOUR);
	p->date = BCDtoNUM(rBCDDATE);
	p->day = BCDtoNUM(rBCDDAY);
	p->month = BCDtoNUM(rBCDMON);	
	p->year = BCDtoNUM(rBCDYEAR)+2000;
	
	//close rtc read write switch
	rRTCCON &= ~(1<<0);

}

void rtc_set(const RtcTime *p){
	
	//open rtc read write switch
	rRTCCON |= (1<<0);
	
	rBCDSEC = NUMtoBCD(p->second);
	rBCDMIN = NUMtoBCD(p->minute);
	rBCDHOUR = NUMtoBCD(p->hour);
	rBCDDATE = NUMtoBCD(p->date);
	rBCDDAY = NUMtoBCD(p->day);
	rBCDMON = NUMtoBCD(p->month);	
	rBCDYEAR = NUMtoBCD(p->year-2000);
	
	//close rtc read write switch
	rRTCCON &= ~(1<<0);
	
}

//rtc interrupt init
void alarm_int_init(void){
	
	rALMSEC = NUMtoBCD(10);
	//open second interrupt
	rRTCALM |= (1<<0);
	//open all interrupt
	rRTCALM |= (1<<6);
	
}

//rtc alarm interrupt isr
void alarm_isr( void ){
	
	printf("alarm is belling\n");
	printf("time is  10 seconds\n");
	
	//clear alarm interrupt flag
	rINTP |= (1<<1);

}

//end rtc function
/************************************************************/

/************************************************************/
//start delay function
void delay_init(void){
	
	//set prescaler0 to 33   this is 2MHz
	rTCFG0 &= ~(0xff<<0);
	rTCFG0 |= (32<<0);
	//set timer0's second prescaler to 2,this is 1MKHz
	rTCFG1 &= ~(0xf<<0);
	rTCFG1 |= (2<<0);
	
	//close auto reload
    rTCON &= ~(1<<3);	
	//set PWM0 freq
	rTCNTB0 = 0;

	//close timer0
	rTCON &= ~(1<<0);
	
}

void delay_us(unsigned int n){
	
	//set PWM0 freq
	rTCNTB0 = n;
	//set manual update
	rTCON |= (1<<1);
	rTCON &= ~(1<<1);
	//open timer0
	rTCON |= (1<<0);
	while( rTCNTO0 );
	//close timer0
	rTCON &= ~(1<<0);
	
}

void delay_ms(unsigned int n){
	
	while(n--){
		delay_us(1000);
	}
	
}
//end delay function
/************************************************************/





