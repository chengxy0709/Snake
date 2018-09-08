#include "shell.h"
#include "stdio.h"
#include "led.h"
#include "lcd.h"
#include "Pic.h"

char CmdStr[CMD_MAX_LENGTH*CMD_MAX_NUMBER]={0};
char Cmd[CMD_MAX_NUMBER][CMD_MAX_LENGTH];

static int strcpy_s(char *str1,char *str2){
	
	volatile char *pstr1 = str1;
	volatile char *pstr2 = str2;
	
	while( *pstr1 ){
		*pstr2 = *pstr1;
		pstr1++;
		pstr2++;
	}
	*pstr2 = '\0';
	return 1;
	
}

static int strcmp_s(char *str1,char *str2){
	
	volatile char *pstr1 = str1;
	volatile char *pstr2 = str2;
	
	while( *pstr1 && *pstr2 ){
		if(*pstr2 != *pstr1)
			return 1;
		pstr1++;
		pstr2++;
	}
	if(*pstr2 == *pstr1)
		return 0;
	else
		return 1;
	
}

static int CleanArray(char *array ,int length){
	
	char *parray = array;
	
	while(length--){
		*parray = 0;
		parray++;
	}
	
}

static int Str2Num(char *str){
	
	int num=0;
	
	while(*str){
		num = num*10 + (*str-'0');
		str++;
	}
	
	return num;
	
}

static unsigned int SetColor(char *str){
	
	if(!strcmp_s(str,GREEN_SHELL))
		return GREEN;
	else if(!strcmp_s(str,RED_SHELL))
		return RED;
	else if(!strcmp_s(str,BLUE_SHELL))
		return BLUE;
	else if(!strcmp_s(str,BLACK_SHELL))
		return BLACK;
	else if(!strcmp_s(str,WHITE_SHELL))
		return WHITE;
	else if( *str >= '0' && *str <= '9' )
		return (unsigned int)(Str2Num(str));
	else
		return BLACK;
	
}

int Shell_init( void ){
	
	CleanArray(CmdStr ,CMD_MAX_LENGTH);
	CleanArray(Cmd[0] ,CMD_MAX_LENGTH*CMD_MAX_NUMBER);
	
	puts_s("S5PV210's shell\n");
	
}
int AnalyCmd(char *cmdstr,char *str){
	
	char temp[CMD_MAX_LENGTH];
	volatile char *pcmdstr = cmdstr;
	volatile char *pstr = str;
	volatile char *pt = temp;
	
	CleanArray(temp ,CMD_MAX_LENGTH);
	while(1){
		
		if( *pcmdstr == ' ' ){
			*pt = '\0';
			strcpy_s(temp,pstr);
			pstr+=CMD_MAX_LENGTH;
			pt = temp;
			CleanArray(temp ,CMD_MAX_LENGTH);
			pcmdstr++;
		}else if( *pcmdstr == '\0' ){
			*pt = '\0';
			strcpy_s(temp,pstr);
			break;
		}else{
			*pt = *pcmdstr;
			pt++;
			pcmdstr++;
		}
		
	}
	
	return 1;
	
}
int ExeCmd(char *str){
	
	if(!strcmp_s(str,LED_SHELL)){
		if(!strcmp_s(str+CMD_MAX_LENGTH,ON_SHELL)){
			if(!strcmp_s(str+2*CMD_MAX_LENGTH,ALL_SHELL))
				Led( ALL_LED , HIGH );
			else
				Led( (*(str+2*CMD_MAX_LENGTH)-'0') , HIGH );
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,OFF_SHELL)){
			if(!strcmp_s(str+2*CMD_MAX_LENGTH,ALL_SHELL))
				Led( ALL_LED , LOW );
			else
				Led( (*(str+2*CMD_MAX_LENGTH)-'0') , LOW );
		}
		else{
			printf("led on/off\n");
		}
	}else if(!strcmp_s(str,LCD_SHELL)){
		if(!strcmp_s(str+CMD_MAX_LENGTH,ON_SHELL)){
			
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,OFF_SHELL)){
			
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,RECT_SHELL)){
			Draw_Rect(Str2Num(str+2*CMD_MAX_LENGTH),Str2Num(str+3*CMD_MAX_LENGTH),Str2Num(str+4*CMD_MAX_LENGTH),Str2Num(str+5*CMD_MAX_LENGTH),SetColor(str+6*CMD_MAX_LENGTH));
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,POINT_SHELL)){
			Draw_point(Str2Num(str+2*CMD_MAX_LENGTH),Str2Num(str+3*CMD_MAX_LENGTH),SetColor(str+4*CMD_MAX_LENGTH));
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,LINE_SHELL)){
			Draw_Line(Str2Num(str+2*CMD_MAX_LENGTH),Str2Num(str+3*CMD_MAX_LENGTH),Str2Num(str+4*CMD_MAX_LENGTH),Str2Num(str+5*CMD_MAX_LENGTH),SetColor(str+6*CMD_MAX_LENGTH));
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,PIC_SHELL)){
			
			if(!strcmp_s(str+2*CMD_MAX_LENGTH,"head"))
				Draw_Picture(Str2Num(str+3*CMD_MAX_LENGTH),Str2Num(str+4*CMD_MAX_LENGTH),300,300,gImage_head);
			else
				Draw_Picture(Str2Num(str+3*CMD_MAX_LENGTH),Str2Num(str+4*CMD_MAX_LENGTH),1000,599,gImage_Pic);
			
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,CLEAR_SHELL)){
			Draw_background(SetColor(str+2*CMD_MAX_LENGTH));
		}else if(!strcmp_s(str+CMD_MAX_LENGTH,CIR_SHELL)){
			Draw_Circular(Str2Num(str+2*CMD_MAX_LENGTH),Str2Num(str+3*CMD_MAX_LENGTH),Str2Num(str+4*CMD_MAX_LENGTH),SetColor(str+5*CMD_MAX_LENGTH));
		}
		else{
			printf("lcd on/off/line/cir/point/rect/pic/clear\n");
		}
	}else{
		printf("please input correct cmd\n");
	}
	
	CleanArray(Cmd[0] ,CMD_MAX_LENGTH*CMD_MAX_NUMBER);
	
	return 1;
	
}