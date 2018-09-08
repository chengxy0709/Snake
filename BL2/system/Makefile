CC	 = arm-linux-gcc
LD	 = arm-linux-ld
OBJCOPY  = arm-linux-objcopy
OBJDUMP  = arm-linux-objdump
AR 	 = arm-linux-ar

LIB       :=-lgcc -L/usr/local/arm/arm-2009q3/lib/gcc/arm-none-linux-gnueabi/4.4.1

INCDIR  	 := $(shell pwd)/../include
LEDDIR   	 := $(shell pwd)/../led
UARTDIR   	 := $(shell pwd)/../uart
KEYDIR   	 := $(shell pwd)/../key
INTDIR   	 := $(shell pwd)/../interrupt
RTCDIR   	 := $(shell pwd)/../rtc
ADCDIR   	 := $(shell pwd)/../adc
LCDDIR   	 := $(shell pwd)/../lcd
SHELLDIR   	 := $(shell pwd)/../shell
SNAKEDIR   	 := $(shell pwd)/../snake
CURRENTDIR 	 := $(shell pwd)/
CFLAGS		 := -Wall -O2 -fno-builtin
CPPFLAGS	 := -nostdlib -nostdinc -I$(LEDDIR) -I$(INCDIR) -I$(UARTDIR) -I$(KEYDIR) -I$(INTDIR) -I$(RTCDIR) -I$(ADCDIR) -I$(LCDDIR) -I$(SHELLDIR) -I$(SNAKEDIR) 

export CC LD OBJCOPY OBJDUMP AR INCDIR CFLAGS CPPFLAGS

objs := main.o start.o
objs += ../led/led.a
objs += ../lib/libc.a
objs += ../uart/uart.a
objs += ../key/key.a
objs += ../interrupt/interrupt.a
objs += ../rtc/rtc.a
objs += ../adc/adc.a
objs += ../lcd/lcd.a
objs += ../shell/s5pv210io.a
objs += ../snake/snake.a


main.bin: $(objs)
	$(LD) -Tlink.lds -o main.elf $^ $(LIB)
	$(OBJCOPY) -O binary main.elf main.bin
	$(OBJDUMP) -D main.elf > main_elf.dis
	
../lib/libc.a :
	cd ../lib; make; cd ../system
	
../led/led.a :
	cd ../led; make; cd ../system
	
../uart/uart.a :
	cd ../uart; make; cd ../system
	
../key/key.a :
	cd ../key; make; cd ../system
	
../interrupt/interrupt.a :
	cd ../interrupt; make; cd ../system
	
../rtc/rtc.a :
	cd ../rtc; make; cd ../system
	
../adc/adc.a :
	cd ../adc; make; cd ../system
	
../lcd/lcd.a :
	cd ../lcd; make; cd ../system
	
../shell/s5pv210io.a :
	cd ../shell; make; cd ../system

../snake/snake.a :
	cd ../snake; make; cd ../system	

%.o : %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< -c 

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f
	cd ../led; make clean; cd ../system
	cd ../lib; make clean; cd ../system
	cd ../uart; make clean; cd ../system 
	cd ../key; make clean; cd ../system	
	cd ../interrupt; make clean; cd ../system
	cd ../rtc; make clean; cd ../system
	cd ../adc; make clean; cd ../system
	cd ../lcd; make clean; cd ../system	
	cd ../shell; make clean; cd ../system
	cd ../snake; make clean; cd ../system
        
	
	
	
