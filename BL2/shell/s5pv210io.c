#include "stdio.h"
#include "s5pv210io.h"

char  getchar_s(void){
	
	return getc();
	
}
char* gets_s(char *str){
	
	volatile char *pstr = str;
	
	*pstr = getchar_s();
	while( *pstr != '\r' && *pstr != '\n' ){
		if( *pstr == '\b' && pstr > str ){
			putchar_s('\b');
			putchar_s(' ');
			putchar_s('\b');
			*pstr = '\0';
			pstr--;
		}else if( *pstr >= 32 ){
			putchar_s(*pstr);
			pstr++;
		}
		*pstr = getchar_s();
	}
	*pstr = '\0';
	
	return str;
	
}

void putchar_s(char ch){
	
	putc(ch);
	
}

void puts_s(char *ch){
	
	while( *ch ){
		putchar_s(*ch);
		ch++;
	}
	
}