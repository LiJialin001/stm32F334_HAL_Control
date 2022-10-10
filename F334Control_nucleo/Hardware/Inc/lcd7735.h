#ifndef _LCD7735_H
#define _LCD7735_H

#include "sys.h"
#include "stdlib.h"
#include "spi.h"


//通用LCD参数
typedef struct
{
	u16 width;
	u16 height;
	u16 id;
	u8  dir;			  // 横屏OR竖屏  0 OR 1
	u16	 wramcmd;		  // 开始写gram指令
	u16  setxcmd;		  // 写x指令
	u16  setycmd;		  //写y指令
	u8   xoffset;
	u8	 yoffset;
}_lcd_dev;

extern _lcd_dev lcddev;


#define USE_HORIZONTAL  	 0 //屏幕顺时针旋转角度   0->0  1->90  2->180  3->270
#define LCD_W 128
#define LCD_H 160


extern u16  POINT_COLOR;
extern u16  BACK_COLOR;


// LCD端口定义
#define GPIO_TYPE  GPIOB
#define LED      9        		//背光控制    PB9
#define LCD_CS   11       		//片选线      PB11
#define LCD_RS   10       		//数据线      PB10
#define LCD_RST  12       		//复位引脚    PB12

#define	LCD_LED PBout(LED) 		//LCD背光控制     PB9

//GPIO置位
#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST
//GPIO复位
#define	LCD_CS_CLR  GPIO_TYPE->BRR=1<<LCD_CS
#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS
#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST

//颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000
#define BLUE       	0x001F
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0XBC40
#define BRRED 		0XFC07
#define GRAY  		0X8430
#define GRAY0       0xEF7D
#define GRAY1       0x8410
#define GRAY2       0x4208

//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝
#define LIGHTBLUE      	 0X7D7C	//浅蓝
#define GRAYBLUE       	 0X5458 //灰蓝

#define LIGHTGREEN     	 0X841F  //浅绿
#define LIGHTGRAY        0XEF5B  //浅灰(PANNEL)
#define LGRAY 			 0XC618  //浅灰(PANNEL),背景色

#define LGRAYBLUE      	 0XA651  //浅灰蓝(中间层)
#define LBBLUE           0X2B12  //浅棕蓝(选择项)

void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);
u16  LCD_ReadPoint(u16 x,u16 y);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(u8 data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);
u16 LCD_BGR2RGB(u16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction );

#endif
