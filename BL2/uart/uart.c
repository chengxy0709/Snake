#define GPA0CON		0xe0200000
#define ULCON0		0Xe2900000
#define UCON0		0xe2900004 
#define UFCON0		0xe2900008
#define UMCON0		0xe290000C
#define UTRSTAT0	0xe2900010
#define UERSTAT0	0xe2900014
#define UFSTAT0		0xe2900018
#define UMSTAT0		0xe290001C
#define UTXH0		0xe2900020
#define URXH0		0xe2900024
#define UBRDIV0		0xe2900028
#define UDIVSLOT0	0xe290002C
#define UINTP0		0xe2900030
#define UINTSP0		0xe2900034
#define UINTM0		0xe2900038

#define rGPA0CON         *((unsigned int *)GPA0CON)
#define rULCON0          *((unsigned int *)ULCON0)
#define rUCON0           *((unsigned int *)UCON0) 
#define rUFCON0          *((unsigned int *)UFCON0)
#define rUMCON0          *((unsigned int *)UMCON0)
#define rUTRSTAT0        *((unsigned int *)UTRSTAT0)
#define rUERSTAT0        *((unsigned int *)UERSTAT0)
#define rUFSTAT0         *((unsigned int *)UFSTAT0)
#define rUMSTAT0         *((unsigned int *)UMSTAT0)
#define rUTXH0           *((volatile unsigned int *)UTXH0)
#define rURXH0           *((unsigned int *)URXH0)
#define rUBRDIV0         *((unsigned int *)UBRDIV0)
#define rUDIVSLOT0       *((unsigned int *)UDIVSLOT0)
#define rUINTP0          *((unsigned int *)UINTP0)
#define rUINTSP0         *((unsigned int *)UINTSP0)
#define rUINTM0          *((unsigned int *)UINTM0)



void uart_init(void){

	rGPA0CON = 0x00000022;
	rULCON0 = 0x00000003;
	rUCON0 = (1<<0)|(1<<2);
	rUMCON0 = 0x00000000;

	rUBRDIV0 = 35;
	rUDIVSLOT0 = 0x0888;

}

char getc(void){

	while( !( rUTRSTAT0 & (1<<0) ) );
	return (rURXH0 & 0Xff); 

}

void putc(char ch){

	if(ch == '\n'){
		while( !( rUTRSTAT0 & (1<<1) ) );
		rUTXH0 = '\r';
	}
	while( !( rUTRSTAT0 & (1<<1) ) );
	rUTXH0 = ch;

}









