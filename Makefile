all:
	make -C ./BL1
	make -C ./BL2/system
	
clean:
	make clean -C ./BL1
	make clean -C ./BL2/system