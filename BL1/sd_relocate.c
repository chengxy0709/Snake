
#define SD_START_BLOCK	45
#define SD_BLOCK_CNT	(2048*4)
#define DDR_START_ADDR	0x23E00000

typedef unsigned int bool;

// 通道号：0，或者2
// 开始扇区号：45
// 读取扇区个数：32
// 读取后放入内存地址：0x23E00000
// with_init：0
typedef void (*pCopySDMMCtoMEM)(int, unsigned int, unsigned short, unsigned int*, bool);

typedef void (*runAdd)(void);

void sd_relocate(void){
	
	//调用iROM中三星提供的复制函数
	pCopySDMMCtoMEM pCopy = (pCopySDMMCtoMEM)( *((unsigned int *)0xD0037F98) );
	//定义一个指向BL2代码运行地址的函数指针
	runAdd pRun = (runAdd)(DDR_START_ADDR);
	
	//复制BL2代码到BL1中
	pCopy(2,SD_START_BLOCK,SD_BLOCK_CNT,(unsigned int*)DDR_START_ADDR,0);
	//长跳转到BL2中执行程序
	pRun();
	
}

















