/*
 *MyLed.c
 *
 *function: blink LED
 *
 */

#define rGPJ0CON *((unsigned int *)0xe0200240)
#define rGPJ0DAT *((unsigned int *)0xe0200244)
#define rGPD0CON *((unsigned int *)0xe02000a0)
#define rGPD0DAT *((unsigned int *)0xe02000a4)

void Delay_Led(void){

	volatile unsigned int i=500000;
	while(i--);

}

void Led_init(void){
	
	rGPJ0CON = (0x111 << 12)|rGPJ0CON;
	rGPD0CON = (0x1 << 4)|rGPD0CON;	
		
}

void Led( unsigned char num , unsigned char flag ){

	if( num<3 )
		if( flag )
			rGPJ0DAT |= ( 1 << (num+3) );
		else
			rGPJ0DAT &= ~( 1 << (num+3) );
	else if( num == 3 )
		if( flag )
			rGPD0DAT |= ( 1 << 1 );
		else
			rGPD0DAT &= ~( 1 << 1 );
	else if( num == 4 ){
		if( flag ){
			rGPJ0DAT |= ( 1 << 3 );
			rGPJ0DAT |= ( 1 << 4 );
			rGPJ0DAT |= ( 1 << 5 );
			rGPD0DAT |= ( 1 << 1 );
		}
		else{
			rGPJ0DAT &= ~( 1 << 3 );
			rGPJ0DAT &= ~( 1 << 4 );
			rGPJ0DAT &= ~( 1 << 5 );
			rGPD0DAT &= ~( 1 << 1 );
		}
	}
	
}


