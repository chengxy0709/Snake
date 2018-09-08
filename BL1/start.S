/*
 *start.s
 *
 *start's code using assembly
 *
 */

#define WDOGCON	  0xe2700000
#define SVC_STACK 0xd0037d80

.global _start

_start:

	//set power lock
	ldr r0, =0xE010E81C
	ldr r1, [r0]
	ldr r2, =0x301
	orr r1, r1, r2
	str r1, [r0]

	//close wdog
	ldr r0,=0x0
	ldr r1,=WDOGCON
	str r0,[r1]

	//set clock
	bl clock_init

	//set svc_stack for c
	ldr sp,=SVC_STACK

	//open iCache
	mrc p15,0,r0,c1,c0,0  //read p15's c1 to r0
//	bic r0,r0,#(1<<12)    //close iCache
	orr r0,r0,#(1<<12)    //open iCache
	mcr p15,0,r0,c1,c0,0
	
	//init sdram
	bl sdram_asm_init

	//jump relocate to do
	bl sd_relocate


	b .	

	
	
	
	



