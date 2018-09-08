#include "lcd.h"
#include "stdio.h"
#include "ascii.h"

void Lcd_init(void){
	
	// 配置引脚用于LCD功能
	GPF0CON = 0x22222222;
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;
	GPF3CON = 0x22222222;
	
	// 打开背光	GPD0_0（PWMTOUT0）
	GPD0CON &= ~(0xf<<0);
	GPD0CON |= (1<<0);			// output mode
	GPD0DAT &= ~(1<<0);			// output 0 to enable backlight
	
	// 10: RGB=FIMD I80=FIMD ITU=FIMD
	DISPLAY_CONTROL = 2<<0;
	
	// bit[26~28]:使用RGB接口
	// bit[18]:RGB 并行
	// bit[2]:选择时钟源为HCLK_DSYS=166MHz
	VIDCON0 &= ~( (7<<26)|(1<<18)|(1<<2) );
	
	// bit[1]:使能lcd控制器
	// bit[0]:当前帧结束后使能lcd控制器
	VIDCON0 |= ( (1<<0)|(1<<1) );
	
	// bit[4]:选择需要分频
	// bit[6~13]:分频系数为5，即VCLK = 166M/(4+1) = 33M
	VIDCON0 |= 4<<6 | 1<<4;
	
	// H43-HSD043I9W1.pdf(p13) 时序图：VSYNC和HSYNC都是低脉冲
	// s5pv210芯片手册(p1207) 时序图：VSYNC和HSYNC都是高脉冲有效，所以需要反转
	VIDCON1 |= 1<<5 | 1<<6;
	
	// 设置时序
	VIDTCON0 = VBPD<<16 | VFPD<<8 | VSPW<<0;
	VIDTCON1 = HBPD<<16 | HFPD<<8 | HSPW<<0;
	
	// 设置长宽(物理屏幕)
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);
	
	// 设置window0
	// bit[0]:使能
	// bit[2~5]:24bpp（RGB888）
	WINCON0 |= 1<<0;
	WINCON0 &= ~(0xf << 2);
	WINCON0 |= (0xB<<2) | (1<<15);
	
#define LeftTopX     0
#define LeftTopY     0
#define RightBotX   (1023)
#define RightBotY   (599)

	// 设置window0的上下左右
	// 设置的是显存空间的大小
	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
	VIDOSD0C &= ~(3<<24);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1);

	// 设置fb的地址
	VIDW00ADD0B0 = FB_ADDR;
	VIDW00ADD1B0 = FB_ADDR + (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff);

	//VIDW00ADD2[0:12]=800;[13:25]=0;  
	VIDW00ADD2 &= ~(0X3FFFFFF);  
	VIDW00ADD2 |= (0X320<<0);  

	
	// 使能channel 0传输数据
	SHADOWCON = 0x1;

	Draw_background(BLACK);
	
}

void Draw_point(u32 x,u32 y,u32 color){
	
	u32 *pfb = (u32 *)FB_ADDR;
	
	*(pfb + y * COL + x) = color;
	
}
void Draw_background(u32 color){
	
	u32 *pfb = (u32 *)FB_ADDR;
	u32 count = ROW * COL;
	
	while(count--){
		
		*(pfb) = color;
		pfb++;
		
	}
	
}

void Draw_Rect(u32 x1,u32 y1,u32 x2,u32 y2,u32 color){
	
	u32 i,j;
	
	for( i = x1 ; i<x2 ; i++ )
		for( j = y1 ; j<y2 ; j++ )
			Draw_point(i,j,color);
	
}

void Draw_Line(u32 x1,u32 y1,u32 x2,u32 y2,u32 color){
	
	double k;
	int i;

	if( x2 > x1 ){
		k = (y2-y1)*1.0/(x2-x1);
		for( i=x1 ; i<x2 ; i++ )
			Draw_point( i , ((u32)((k*(i-x1))+y1)) , color );
	}else if( x2 < x1 ){
		k = (y2-y1)*1.0/(x1-x2);
		for( i=x2 ; i<x1 ; i++ )
			Draw_point( i , (y2-(u32)(k*(i-x2))) , color );
	}else{
		for( i=y1 ; i<y2 ; i++ )
			Draw_point( x1 , i , color );
	}
	
}


//画圆函数，圆心坐标是(centerX, centerY)，半径是radius，圆的颜色是color
void Draw_Circular(unsigned int centerX, unsigned int centerY, unsigned int radius, unsigned int color)
{
	int x,y ;
	int tempX,tempY;;
    int SquareOfR = radius*radius;

	for(y=0; y<YSIZE; y++)
	{
		for(x=0; x<XSIZE; x++)
		{
			if(y<=centerY && x<=centerX)
			{
				tempY=centerY-y;
				tempX=centerX-x;                        
			}
			else if(y<=centerY&& x>=centerX)
			{
				tempY=centerY-y;
				tempX=x-centerX;                        
			}
			else if(y>=centerY&& x<=centerX)
			{
				tempY=y-centerY;
				tempX=centerX-x;                        
			}
			else
			{
				tempY = y-centerY;
				tempX = x-centerX;
			}
			if ((tempY*tempY+tempX*tempX)<=SquareOfR)
				Draw_point(x, y, color);
		}
	}
}
// glib库中的画线函数，可以画斜线，线两端分别是(x1, y1)和(x2, y2)
void glib_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;  
				while(x1<=x2)
				{
					Draw_point(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					Draw_point(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					Draw_point(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else	 // 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					Draw_point(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					Draw_point(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					Draw_point(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					Draw_point(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					Draw_point(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

void Draw_Char_8_16(u32 x,u32 y,u32 color,u8 ch){
	
	int i,j,count=0;
	
	for( i = y ; i < (y+16) ; i++ ){
		for( j = x ; j < (x+8) ; j++ ){
			if( ascii_8_16[ch-32][i-y] & (1<<(count%8)) )
				Draw_point(j, i, color);
			count++;
		}
	}
	
}
void Draw_String_8_16(u32 x,u32 y,u32 color,u8 *ch){

	u8 *pch = ch;
	
	while( *pch ){
		if( x >= XSIZE-1 ){
			x=0;
			y+=16;
		}
		Draw_Char_8_16(x,y,color,*pch);
		x+=8;
		pch++;
	}
	
}

void Draw_Picture(u32 x,u32 y,u32 width,u32 highth,u8 *picture){

	u8 *pdata = picture;
	u32 *pfb = (u32 *)FB_ADDR;
	u32 i,j;
	
	if( ((x+width) > XSIZE) || ((y+highth) > YSIZE) )
		return;
	
	pfb += (y*COL+x);
	for( i = 0 ; i < highth ; i++ ){
		 
		for( j = 0 ; j < width ; j++ ){
			*(pfb+(i*COL+j)) = ((0<<24)|(*pdata<<16)|(*(pdata+1)<<8)|(*(pdata+2)<<0));
			pdata+=3;
		}
	}
	
}
void Draw_Number(u32 x,u32 y,u32 num,u32 color){

	u8 i=0,ch[20]={0};
	
	ch[0]='0';
	while( num ){
	
		ch[i] = num % 10;
		num /= 10;
		i++;		
	
	}
	Draw_Rect(x,y,x+40,y+16,WHITE);
	for( ; i>0 ; i-- ){
		
		Draw_Char_8_16(x,y,color,ch[i-1]+'0');
		x += 8;
	
	}

}