// 时钟控制器基地址
#define ELFIN_CLOCK_POWER_BASE		0xE0100000	

// 时钟相关的寄存器相对时钟控制器基地址的偏移值
#define APLL_LOCK_OFFSET		0x00		
#define MPLL_LOCK_OFFSET		0x08

#define APLL_CON0_OFFSET		0x100
#define APLL_CON1_OFFSET		0x104
#define MPLL_CON_OFFSET			0x108

#define CLK_SRC0_OFFSET			0x200
#define CLK_SRC1_OFFSET			0x204
#define CLK_SRC2_OFFSET			0x208
#define CLK_SRC3_OFFSET			0x20c
#define CLK_SRC4_OFFSET			0x210
#define CLK_SRC5_OFFSET			0x214
#define CLK_SRC6_OFFSET			0x218
#define CLK_SRC_MASK0_OFFSET	0x280
#define CLK_SRC_MASK1_OFFSET	0x284

#define CLK_DIV0_OFFSET			0x300
#define CLK_DIV1_OFFSET			0x304
#define CLK_DIV2_OFFSET			0x308
#define CLK_DIV3_OFFSET			0x30c
#define CLK_DIV4_OFFSET			0x310
#define CLK_DIV5_OFFSET			0x314
#define CLK_DIV6_OFFSET			0x318
#define CLK_DIV7_OFFSET			0x31c

#define CLK_DIV0_MASK			0x7fffffff

// 这些M、P、S的配置值都是查数据手册中典型时钟配置值的推荐配置得来的。
// 这些配置值是三星推荐的，因此工作最稳定。如果是自己随便瞎拼凑出来的那就要
// 经过严格测试，才能保证一定对。
#define APLL_MDIV      	 		0x7d		// 125
#define APLL_PDIV       		0x3
#define APLL_SDIV       		0x1

#define MPLL_MDIV				0x29b		// 667
#define MPLL_PDIV				0xc
#define MPLL_SDIV				0x1

#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)
#define APLL_VAL			set_pll(APLL_MDIV,APLL_PDIV,APLL_SDIV)
#define MPLL_VAL			set_pll(MPLL_MDIV,MPLL_PDIV,MPLL_SDIV)

.global clock_init

clock_init:

	ldr r1,=ELFIN_CLOCK_POWER_BASE
	//close PLL
	ldr r0,=0x0
	str r0,[r1,#CLK_SRC0_OFFSET]

	//set lock time
	ldr r0,=0x0000FFFF
	str r0,[r1,#MPLL_LOCK_OFFSET]
	str r0,[r1,#APLL_LOCK_OFFSET]

	//set frequency division
	ldr r0,[r1,#CLK_DIV0_OFFSET]
	ldr r2,=CLK_DIV0_MASK
	bic r0,r0,r2
	ldr r2,=0x14131440
	orr r0,r0,r2
	str r0,[r1,#CLK_DIV0_OFFSET]

	//set PLL
	//FOUT = MDIV*FIN/(PDIV*2^(SDIV-1))
	ldr r0,=APLL_VAL
	str r0,[r1,#APLL_CON0_OFFSET]
	//FOUT = MDIV*FIN/(PDIV*2^SDIV)
	ldr r0,=MPLL_VAL
	str r0,[r1,#MPLL_CON_OFFSET]

	//set kinds of clock's switch,use PLL
	ldr r0,=0x10001111
	ldr r2,[r1,#CLK_SRC0_OFFSET]
	orr r0,r0,r2
	str r0,[r1,#CLK_SRC0_OFFSET]

	mov pc,lr











