
#define		TSADCCON0		( *((volatile unsigned int *)0xE1700000) )
#define		ADCMUX		( *((volatile unsigned int *)0xE170001C) )
#define		TSDATX0		( *((volatile unsigned int *)0xE170000C) )

#define     READ_STATUS_ADC0  ( TSADCCON0 & (1<<15) )

void adc_init(void){
	
	ADCMUX = 0;//选择0
	
	TSADCCON0 |= (1<<16);//选择12bit精度
	TSADCCON0 |= (1<<14);//开分频器
	
	TSADCCON0 &= ~(0xff<<6);
	TSADCCON0 |= (32<<6);//设置采样频率2MHz
	
	TSADCCON0 &= ~(1<<2);//开启ADC
	TSADCCON0 &= ~(1<<1);//Disables start by read operation
	TSADCCON0 |= (1<<0);//开启ADC自动刷新
	
}
unsigned int adc_value(void){

	while( !READ_STATUS_ADC0 );
		return (TSDATX0 & 0xFFF);
	
}
