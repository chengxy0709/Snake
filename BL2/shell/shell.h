#ifndef _S5PV210IO_H
#define _S5PV210IO_H

#define CMD_MAX_LENGTH 20
#define CMD_MAX_NUMBER 10

/************************cmd***************************/
//1st
#define LED_SHELL "led"
#define LCD_SHELL "lcd"
//2st
#define ON_SHELL "on"
#define OFF_SHELL "off"
#define POINT_SHELL "point"
#define RECT_SHELL "rect"
#define CIR_SHELL "cir"
#define LINE_SHELL "line"
#define PIC_SHELL "pic"
#define CLEAR_SHELL "clear"
//3st
#define ALL_SHELL "all"
//else
#define GREEN_SHELL "green"
#define RED_SHELL "red"
#define BLUE_SHELL "blue"
#define BLACK_SHELL "black"
#define WHITE_SHELL "white"
/******************************************************/

extern char CmdStr[CMD_MAX_LENGTH*CMD_MAX_NUMBER];
extern char Cmd[CMD_MAX_NUMBER][CMD_MAX_LENGTH];

int Shell_init( void );
int AnalyCmd(char *cmdstr,char *str);
int ExeCmd(char *str);

#endif