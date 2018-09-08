#ifndef _INTERRUPT_H
#define _INTERRUPT_H


//函数接口
//初始化中断控制器
void intc_init();
//中断使能控制器
void intenable_init(unsigned int intnum);
//中断禁止控制器
void intdisable_init(unsigned int intnum);
//清除VECT的ADDR寄存器
void clear_addr(void);
//绑定中断服务函数和对应的中断寄存器
void intSetAdd(unsigned int intnum,void (*handler)(void) );
//返回某个VIC的中断状态
unsigned int check_VicActive(unsigned int reg);
//中断服务函数
void irq_handle(void);
//系统初始化异常向量表
void system_init_exception(void); 
//write code in assmible file
//IRQ exception
void IRQ_handle(void);



// Interrupt's base address
#define VIC0_BASE					(0xF2000000)
#define VIC1_BASE					(0xF2100000)
#define VIC2_BASE					(0xF2200000)
#define VIC3_BASE					(0xF2300000)

// VIC0 control
#define		VIC0FIQSTATUS			( *((volatile unsigned int *)(VIC0_BASE + 0x04)) )
#define		VIC0IRQSTATUS			( *((volatile unsigned int *)(VIC0_BASE + 0x00)) )
#define		VIC0INTSELECT			( *((volatile unsigned int *)(VIC0_BASE + 0x0c)) )
#define		VIC0INTENABLE			( *((volatile unsigned int *)(VIC0_BASE + 0x10)) )
#define		VIC0INTENCLEAR			( *((volatile unsigned int *)(VIC0_BASE + 0x14)) )
#define 	VIC0VECTADDR			(VIC0_BASE + 0x100)
#define 	VIC0ADDR				( *((volatile unsigned int *)(VIC0_BASE + 0xf00)) )

// VIC1 control
#define		VIC1IRQSTATUS			( *((volatile unsigned int *)(VIC1_BASE + 0x00)) )
#define		VIC1FIQSTATUS			( *((volatile unsigned int *)(VIC1_BASE + 0x04)) )
#define		VIC1INTSELECT			( *((volatile unsigned int *)(VIC1_BASE + 0x0c)) )
#define		VIC1INTENABLE			( *((volatile unsigned int *)(VIC1_BASE + 0x10)) )
#define		VIC1INTENCLEAR			( *((volatile unsigned int *)(VIC1_BASE + 0x14)) )
#define 	VIC1VECTADDR			(VIC1_BASE + 0x100)
#define 	VIC1ADDR				( *((volatile unsigned int *)(VIC1_BASE + 0xf00)) )

// VIC2 control
#define		VIC2IRQSTATUS			( *((volatile unsigned int *)(VIC2_BASE + 0x00)) )
#define		VIC2FIQSTATUS			( *((volatile unsigned int *)(VIC2_BASE + 0x04)) )
#define		VIC2INTSELECT			( *((volatile unsigned int *)(VIC2_BASE + 0x0c)) )
#define		VIC2INTENABLE			( *((volatile unsigned int *)(VIC2_BASE + 0x10)) )
#define		VIC2INTENCLEAR			( *((volatile unsigned int *)(VIC2_BASE + 0x14)) )
#define 		VIC2VECTADDR			(VIC2_BASE + 0x100)
#define 		VIC2ADDR				( *((volatile unsigned int *)(VIC2_BASE + 0xf00)) )

// VIC3 control
#define		VIC3IRQSTATUS			( *((volatile unsigned int *)(VIC3_BASE + 0x00)) )
#define	 	VIC3FIQSTATUS			( *((volatile unsigned int *)(VIC3_BASE + 0x04)) )
#define	 	VIC3INTSELECT			( *((volatile unsigned int *)(VIC3_BASE + 0x0c)) )
#define	 	VIC3INTENABLE			( *((volatile unsigned int *)(VIC3_BASE + 0x10)) )
#define	 	VIC3INTENCLEAR			( *((volatile unsigned int *)(VIC3_BASE + 0x14)) )
#define 		VIC3VECTADDR			(VIC3_BASE + 0x100)
#define 		VIC3ADDR				( *((volatile unsigned int *)(VIC3_BASE + 0xf00)) )

//异常处理弟地址
#define exception_vector_table_base		0xD0037400
#define exception_reset					(exception_vector_table_base + 0x00)
#define exception_undef					(exception_vector_table_base + 0x04)
#define exception_sotf_int				(exception_vector_table_base + 0x08)
#define exception_prefetch				(exception_vector_table_base + 0x0C)
#define exception_data					(exception_vector_table_base + 0x10)
#define exception_irq					(exception_vector_table_base + 0x18)
#define exception_fiq					(exception_vector_table_base + 0x1C)

#define r_exception_reset		(*(volatile unsigned int *)exception_reset)
#define r_exception_undef		(*(volatile unsigned int *)exception_undef)
#define r_exception_sotf_int	(*(volatile unsigned int *)exception_sotf_int)
#define r_exception_prefetch	(*(volatile unsigned int *)exception_prefetch)
#define r_exception_data		(*(volatile unsigned int *)exception_data)
#define r_exception_irq			(*(volatile unsigned int *)exception_irq)
#define r_exception_fiq			(*(volatile unsigned int *)exception_fiq)


// 中断源编号
#define INT_LIMIT				(96)

//INT NUM - VIC0
#define NUM_EINT0				(0)
#define NUM_EINT1				(1)
#define NUM_EINT2				(2)
#define NUM_EINT3				(3)
#define NUM_EINT4				(4)
#define NUM_EINT5				(5)
#define NUM_EINT6				(6)
#define NUM_EINT7				(7)
#define NUM_EINT8				(8)
#define NUM_EINT9				(9)
#define NUM_EINT10				(10)
#define NUM_EINT11				(11)
#define NUM_EINT12				(12)
#define NUM_EINT13				(13)
#define NUM_EINT14				(14)
#define NUM_EINT15				(15)
#define NUM_EINT16_31			(16)
#define NUM_Reserved17			(17) 
#define NUM_MDMA				(18)
#define NUM_PDMA0				(19)
#define NUM_PDMA1				(20)
#define NUM_TIMER0				(21)
#define NUM_TIMER1				(22)
#define NUM_TIMER2				(23)
#define NUM_TIMER3				(24)
#define NUM_TIMER4				(25)
#define NUM_SYSTIMER			(26)
#define NUM_WDT					(27)
#define NUM_RTC_ALARM			(28)
#define NUM_RTC_TICK			(29)
#define NUM_GPIOINT				(30)
#define NUM_FIMC3				(31)

//INT NUM - VIC1
#define NUM_CORTEX0				(32+0)
#define NUM_CORTEX1				(32+1)
#define NUM_CORTEX2				(32+2)
#define NUM_CORTEX3				(32+3)
#define NUM_CORTEX4				(32+4)
#define NUM_IEM_APC				(32+5)
#define NUM_IEM_IEC				(32+6)
#define NUM_Reserved39			(32+7)
#define NUM_NFC					(32+8)
#define NUM_CFC					(32+9)
#define NUM_UART0				(32+10)
#define NUM_UART1				(32+11)
#define NUM_UART2				(32+12)
#define NUM_UART3				(32+13)
#define NUM_I2C					(32+14)
#define NUM_SPI0				(32+15)
#define NUM_SPI1				(32+16)
#define NUM_SPI2				(32+17)
#define NUM_AUDIO				(32+18)
#define NUM_I2C_PMIC			(32+19)
#define NUM_I2C_HDMI			(32+20)
#define NUM_HSIRX				(32+21)
#define NUM_HSITX				(32+22)
#define NUM_UHOST				(32+23)
#define NUM_OTG					(32+24)
#define NUM_MSM					(32+25)
#define NUM_HSMMC0				(32+26)
#define NUM_HSMMC1				(32+27)
#define NUM_HSMMC2				(32+28)
#define NUM_MIPI_CSI			(32+29)
#define NUM_MIPI_DSI			(32+30)
#define NUM_ONENAND_AUDI		(32+31)

//INT NUM - VIC2
#define NUM_LCD0				(64+0)
#define NUM_LCD1				(64+1)
#define NUM_LCD2				(64+2)
#define NUM_LCD3				(64+3)
#define NUM_ROTATOR				(64+4)
#define NUM_FIMC_A				(64+5)
#define NUM_FIMC_B				(64+6)
#define NUM_FIMC_C				(64+7)
#define NUM_JPEG				(64+8)
#define NUM_2D					(64+9)
#define NUM_3D					(64+10)
#define NUM_MIXER				(64+11)
#define NUM_HDMI				(64+12)
#define NUM_HDMI_I2C			(64+13)
#define NUM_MFC					(64+14)
#define NUM_TVENC				(64+15)
#define NUM_I2S0				(64+16)
#define NUM_I2S1				(64+17)
#define NUM_I2S2				(64+18)
#define NUM_AC97				(64+19)
#define NUM_PCM0				(64+20)
#define NUM_PCM1				(64+21)
#define NUM_SPDIF				(64+22)
#define NUM_ADC 				(64+23)
#define NUM_PENDN				(64+24)
#define NUM_KEYPAD				(64+25)
#define NUM_Reserved90			(64+26) 
#define NUM_HASH				(64+27) 
#define NUM_FEEDCTRL			(64+28) 
#define NUM_PCM2				(64+29)
#define NUM_SDM_IRQ				(64+30)
#define NUM_SMD_FIQ				(64+31)

//INT NUM - VIC3
#define NUM_IPC					(96+0)
#define NUM_HOSTIF				(96+1)
#define NUM_HSMMC3				(96+2)
#define NUM_CEC					(96+3)
#define NUM_TSI					(96+4)
#define NUM_MDNIE0				(96+5)
#define NUM_MDNIE1				(96+6)
#define NUM_MDNIE2				(96+7)
#define NUM_MDNIE3				(96+8)
#define NUM_ADC1				(96+9)
#define NUM_PENDN1				(96+10)
#define NUM_ALL					(200)




#endif
