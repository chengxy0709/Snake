CC	 = arm-linux-gcc
LD	 = arm-linux-ld
OBJCOPY  = arm-linux-objcopy
OBJDUMP  = arm-linux-objdump
AR 	 = arm-linux-ar

CFLAGS		 := -Wall -O2 -fno-builtin
CPPFLAGS	 := -nostdlib -nostdinc 

objs := start.o clock_init.o sdram_init.o sd_relocate.o

BLi1.bin: $(objs)
	$(LD) -Tlink.lds -o BLi1.elf $^
	$(OBJCOPY) -O binary BLi1.elf BLi1.bin
	$(OBJDUMP) -D BLi1.elf > BLi1_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 BLi1.bin BL1.bin

%.o : %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< -c 

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f
	
	
