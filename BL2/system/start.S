/*
 *start.s
 *
 *start's code using assembly
 *
 */

#define IRQ_STACK 0xd0037f80

.global _start
.global IRQ_handle

_start:


	//jump main to do
	bl main

	b .	

// 在这个汇编函数中，用来做中断模式下的现场保护和恢复，并且调用真正的中断处理程序
	
IRQ_handle:
	//设置IRQ模式的栈
	ldr sp,=IRQ_STACK
	//保存LR
	sub lr,lr,#4
	//保存r0-r12,lr的值
	stmfd sp!,{r0-r12,lr}
	//跳转到中断程序处
	bl irq_handle
	//执行完中断程序返回r0-r12,lr,cpsr的值
	ldmfd sp!,{r0-r12,pc}^
	
	
	
	



