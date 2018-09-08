#ifndef _RTC_H
#define _RTC_H

//delay function
//delay source is PWM0Timer
void delay_init(void);
void delay_us(unsigned int n);
void delay_ms(unsigned int n);

void PWMOUT2_init(void);
//#define PWMOUT2_freq(x) 	(rTCNTB2 = 128000/x)	//基频128KHz

void WDOG_init(void);

//RTC 
typedef struct RTCTIME{
	
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int date;
	unsigned int hour;
	unsigned int second;
	unsigned int minute;
	
}RtcTime;
extern RtcTime time;
void rtc_read(RtcTime *p);
void rtc_set(const RtcTime *p);
void alarm_isr( void );
void alarm_int_init(void);

#define GPD0CON 	0xe02000a0		//PWMOUT2-GPD0_2
#define rGPD0CON	*((volatile unsigned int *)GPD0CON)

//PWM register
#define TCFG0		0xe2500000
#define TCFG1		0xe2500004
#define TCON		0xe2500008
#define TCNTB0		0xe250000c
#define TCMPB0		0xe2500010
#define TCNTO0		0xe2500014
#define TCNTB2		0xe2500024
#define TCMPB2		0xe2500028
#define TCNTO2		0xe250002c

#define rTCFG0		*((volatile unsigned int *)TCFG0)
#define rTCFG1		*((volatile unsigned int *)TCFG1)
#define rTCON		*((volatile unsigned int *)TCON)
#define rTCNTB0		*((volatile unsigned int *)TCNTB0)
#define rTCMPB0		*((volatile unsigned int *)TCMPB0)
#define rTCNTO0		*((volatile unsigned int *)TCNTO0)
#define rTCNTB2		*((volatile unsigned int *)TCNTB2)
#define rTCMPB2		*((volatile unsigned int *)TCMPB2)
#define rTCNTO2		*((volatile unsigned int *)TCNTO2)

//WDOG register
#define WTCON		0xe2700000
#define WTDAT		0xe2700004
#define WTCNT		0xe2700008
#define WTCLRINT	0xe270000c

#define rWTCON		*((volatile unsigned int *)WTCON)
#define rWTDAT		*((volatile unsigned int *)WTDAT)
#define rWTCNT		*((volatile unsigned int *)WTCNT)
#define rWTCLRINT	*((volatile unsigned int *)WTCLRINT)

//RTC register
#define 	RTC_BASE	 (0xE2800000)
#define		rINTP      	 (*((volatile unsigned long *)(RTC_BASE + 0x30)))
#define		rRTCCON    	 (*((volatile unsigned long *)(RTC_BASE + 0x40)))
#define		rTICCNT    	 (*((volatile unsigned long *)(RTC_BASE + 0x44)))
#define		rRTCALM    	 (*((volatile unsigned long *)(RTC_BASE + 0x50)))
#define		rALMSEC    	 (*((volatile unsigned long *)(RTC_BASE + 0x54)))
#define		rALMMIN    	 (*((volatile unsigned long *)(RTC_BASE + 0x58)))
#define		rALMHOUR  	 (*((volatile unsigned long *)(RTC_BASE + 0x5c)))
#define		rALMDATE     (*((volatile unsigned long *)(RTC_BASE + 0x60)))
#define		rALMMON    	 (*((volatile unsigned long *)(RTC_BASE + 0x64)))
#define		rALMYEAR  	 (*((volatile unsigned long *)(RTC_BASE + 0x68)))
#define		rRTCRST      (*((volatile unsigned long *)(RTC_BASE + 0x6c)))
#define		rBCDSEC    	 (*((volatile unsigned long *)(RTC_BASE + 0x70)))
#define		rBCDMIN   	 (*((volatile unsigned long *)(RTC_BASE + 0x74)))
#define		rBCDHOUR     (*((volatile unsigned long *)(RTC_BASE + 0x78)))
#define		rBCDDATE     (*((volatile unsigned long *)(RTC_BASE + 0x7c)))
#define		rBCDDAY      (*((volatile unsigned long *)(RTC_BASE + 0x80)))
#define		rBCDMON      (*((volatile unsigned long *)(RTC_BASE + 0x84)))
#define		rBCDYEAR     (*((volatile unsigned long *)(RTC_BASE + 0x88)))
#define		rCURTICCNT   (*((volatile unsigned long *)(RTC_BASE + 0x90)))
#define		rRTCLVD    	 (*((volatile unsigned long *)(RTC_BASE + 0x94)))

#endif




















