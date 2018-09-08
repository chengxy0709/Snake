#ifndef _LCD_H
#define _LCD_H

typedef unsigned int u32;
typedef unsigned char u8;

#define GPF0CON			(*(volatile unsigned long *)0xE0200120)
#define GPF1CON			(*(volatile unsigned long *)0xE0200140)
#define GPF2CON			(*(volatile unsigned long *)0xE0200160)
#define GPF3CON			(*(volatile unsigned long *)0xE0200180)

#define GPD0CON			(*(volatile unsigned long *)0xE02000A0)
#define GPD0DAT			(*(volatile unsigned long *)0xE02000A4)

#define CLK_SRC1		(*(volatile unsigned long *)0xe0100204)
#define CLK_DIV1		(*(volatile unsigned long *)0xe0100304)
#define DISPLAY_CONTROL	(*(volatile unsigned long *)0xe0107008)

#define VIDCON0			(*(volatile unsigned long *)0xF8000000)
#define VIDCON1			(*(volatile unsigned long *)0xF8000004)
#define VIDTCON2		(*(volatile unsigned long *)0xF8000018)
#define WINCON0 		(*(volatile unsigned long *)0xF8000020)
#define WINCON2 		(*(volatile unsigned long *)0xF8000028)
#define SHADOWCON 		(*(volatile unsigned long *)0xF8000034)
#define VIDOSD0A 		(*(volatile unsigned long *)0xF8000040)
#define VIDOSD0B 		(*(volatile unsigned long *)0xF8000044)
#define VIDOSD0C 		(*(volatile unsigned long *)0xF8000048)

#define VIDW00ADD0B0 	(*(volatile unsigned long *)0xF80000A0)
#define VIDW00ADD1B0 	(*(volatile unsigned long *)0xF80000D0)

#define VIDW00ADD2 		(*(volatile unsigned long *)0xF8000100)

#define VIDTCON0 		(*(volatile unsigned long *)0xF8000010)
#define VIDTCON1 		(*(volatile unsigned long *)0xF8000014)

#define HSPW 			(40)				// 1~40 DCLK
#define HBPD			(10 - 1)			// 46
#define HFPD 			(240 - 1)			// 16 210 354
#define VSPW			(20)				// 1~20 DCLK
#define VBPD 			(10 - 1)			// 23
#define VFPD 			(30 - 1)			// 7 22 147

// FB地址
#define FB_ADDR			(0x23000000)
#define ROW				(600)
#define COL				(1024)
#define HOZVAL			(COL-1)
#define LINEVAL			(ROW-1)

#define XSIZE			COL
#define YSIZE			ROW

// 常用颜色定义
#define BLUE	0x0000FF
#define RED		0xFF0000
#define GREEN	0x00FF00
#define WHITE	0xFFFFFF
#define BLACK	0x000000

void Lcd_init(void);

void Draw_point(u32 x,u32 y,u32 color);
void Draw_background(u32 color);
void Draw_Rect(u32 x1,u32 y1,u32 x2,u32 y2,u32 color);
void Draw_Line(u32 x1,u32 y1,u32 x2,u32 y2,u32 color);
//画圆函数，圆心坐标是(centerX, centerY)，半径是radius，圆的颜色是color
void Draw_Circular(unsigned int centerX, unsigned int centerY, unsigned int radius, unsigned int color);

void Draw_Picture(u32 x,u32 y,u32 width,u32 highth,u8 *picture);

void Draw_Char_8_16(u32 x,u32 y,u32 color,u8 ch);
void Draw_String_8_16(u32 x,u32 y,u32 color,u8 *ch);
void Draw_Number(u32 x,u32 y,u32 num,u32 color);

#endif