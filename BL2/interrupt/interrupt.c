#include "stdio.h"
#include "interrupt.h"


//异常处理函数
void reset_exception(void)
{
	printf("reset_exception.\n");
}

void undef_exception(void)
{
	printf("undef_exception.\n");
}

void sotf_int_exception(void)
{
	printf("sotf_int_exception.\n");
}

void prefetch_exception(void)
{
	printf("prefetch_exception.\n");
}

void data_exception(void)
{
	printf("data_exception.\n");
}





//系统初始化异常向量表
void system_init_exception(void){
	
	// 第一阶段处理，绑定异常向量表,简单的处理，并没有对函数跳转与返回做处理
	r_exception_reset = (unsigned int)reset_exception;
	r_exception_undef = (unsigned int)undef_exception;
	r_exception_sotf_int = (unsigned int)sotf_int_exception;
	r_exception_prefetch = (unsigned int)prefetch_exception;
	r_exception_data = (unsigned int)data_exception;
	r_exception_irq = (unsigned int)IRQ_handle;		//汇编中的函数
	r_exception_fiq = (unsigned int)IRQ_handle;		//汇编中的函数
	
	// 初始化中断控制器的基本寄存器
	intc_init();
	
}

//清除所有即将要用的ADDR寄存器
void clear_addr(void){
	
	// VICxADDR:当前正在处理的中断的中断处理函数的地址
    VIC0ADDR = 0;
    VIC1ADDR = 0;
    VIC2ADDR = 0;
    VIC3ADDR = 0;
	
}

//初始化中断控制器
void intc_init(){
	
	//禁止所有中断
	VIC0INTENCLEAR = 0xffffffff;
    VIC1INTENCLEAR = 0xffffffff;
    VIC2INTENCLEAR = 0xffffffff;
    VIC3INTENCLEAR = 0xffffffff;
	//选择所有中断为IRQ
    VIC0INTSELECT = 0x0;
    VIC1INTSELECT = 0x0;
    VIC2INTSELECT = 0x0;
    VIC3INTSELECT = 0x0;	
	
	clear_addr();
	
}

//中断使能控制器
void intenable_init(unsigned int intnum){
	
	unsigned int temp;
	
	if( intnum < 32 ){
		temp = VIC0INTENABLE;
        temp |= (1<<intnum);		// 如果是第一种设计则必须位操作，第二种设计可以
									// 直接写。
        VIC0INTENABLE = temp;
	}else if( intnum < 64 ){
		temp = VIC1INTENABLE;
        temp |= (1<<(intnum-32));		// 如果是第一种设计则必须位操作，第二种设计可以
									// 直接写。
        VIC1INTENABLE = temp;
	}else if( intnum < 96 ){
		temp = VIC2INTENABLE;
        temp |= (1<<(intnum-64));		// 如果是第一种设计则必须位操作，第二种设计可以
									// 直接写。
        VIC2INTENABLE = temp;
	}else if( intnum < NUM_ALL ){
		temp = VIC3INTENABLE;
        temp |= (1<<(intnum-96));		// 如果是第一种设计则必须位操作，第二种设计可以
									// 直接写。
        VIC3INTENABLE = temp;
	}else{
		
		VIC0INTENABLE = 0xFFFFFFFF;	//全部打开
        VIC1INTENABLE = 0xFFFFFFFF;
        VIC2INTENABLE = 0xFFFFFFFF;
        VIC3INTENABLE = 0xFFFFFFFF;
		
	}
	
}
//中断禁止控制器
void intdisable_init(unsigned int intnum){
	
	unsigned int temp;

    if(intnum<32)
    {
        temp = VIC0INTENCLEAR;
        temp |= (1<<intnum);
        VIC0INTENCLEAR = temp;
    }
    else if(intnum<64)
    {
        temp = VIC1INTENCLEAR;
        temp |= (1<<(intnum-32));
        VIC1INTENCLEAR = temp;
    }
    else if(intnum<96)
    {
        temp = VIC2INTENCLEAR;
        temp |= (1<<(intnum-64));
        VIC2INTENCLEAR = temp;
    }
    else if(intnum<NUM_ALL)
    {
        temp = VIC3INTENCLEAR;
        temp |= (1<<(intnum-96));
        VIC3INTENCLEAR = temp;
    }
    // NUM_ALL : disable all interrupt
    else
    {
        VIC0INTENCLEAR = 0xFFFFFFFF;
        VIC1INTENCLEAR = 0xFFFFFFFF;
        VIC2INTENCLEAR = 0xFFFFFFFF;
        VIC3INTENCLEAR = 0xFFFFFFFF;
    }
	
}

//绑定中断服务函数和对应的中断寄存器
void intSetAdd(unsigned int intnum,void (*handler)(void) ){
	
	//VIC0
    if(intnum<32)
    {
        *( (volatile unsigned int *)(VIC0VECTADDR + 4*(intnum-0)) ) = (unsigned)handler;
    }
    //VIC1
    else if(intnum<64)
    {
        *( (volatile unsigned int *)(VIC1VECTADDR + 4*(intnum-32)) ) = (unsigned)handler;
    }
    //VIC2
    else if(intnum<96)
    {
        *( (volatile unsigned int *)(VIC2VECTADDR + 4*(intnum-64)) ) = (unsigned)handler;
    }
    //VIC3
    else
    {
        *( (volatile unsigned int *)(VIC3VECTADDR + 4*(intnum-96)) ) = (unsigned)handler;
    }
    return;
	
}

//判断哪个VIC发生中断了
unsigned int check_VicActive(unsigned int reg){
	
	if(reg == 0)
        return	VIC0IRQSTATUS;
    else if(reg == 1)
        return 	VIC1IRQSTATUS;
    else if(reg == 2)
        return 	VIC2IRQSTATUS;
    else if(reg == 3)
        return 	VIC3IRQSTATUS;
    else
    {}
    return 0;
	
}

//中断服务函数
//ADDR用来存放硬件找到的发生中断的引脚的中断服务函数的地址
//因为有四个ADDR来保存需要执行的中断服务函数，必须先找到是那个ADDR
void irq_handle(void){
	
	unsigned int vicaddr[4] = {VIC0ADDR,VIC1ADDR,VIC2ADDR,VIC3ADDR};
	unsigned int i=0;
	void (*isr)(void) = NULL;
	
	printf("irq_handler.\n");
	
	for( i=0 ; i<4 ; i++ ){
		
		if( check_VicActive(i) != 0 ){
			isr = (void (*)(void))vicaddr[i];	//将相应中断的函数地址给空函数指针
			break;
		}
		
	}
	
	(*isr)();	//取函数地址并执行
	//clear addr flag
	clear_addr();
	
}




