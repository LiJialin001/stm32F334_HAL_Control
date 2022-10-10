#include "lcd7735.h"

_lcd_dev lcddev;

u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;
u16 DeviceCode;


void LCD_WR_REG(u8 data)
{
   LCD_CS_CLR;
   LCD_RS_CLR;
   SPI_WriteByte(data);
   LCD_CS_SET;
}


void LCD_WR_DATA(u8 data)
{
	LCD_CS_CLR;
	LCD_RS_SET;
	SPI_WriteByte(data);
	LCD_CS_SET;
}



void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}


void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}


void Lcd_WriteData_16Bit(u16 Data)
{
	LCD_CS_CLR;
	LCD_RS_SET;
	SPI_Write2Byte(Data);
	LCD_CS_SET;
}


void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);
	Lcd_WriteData_16Bit(POINT_COLOR);
}



void LCD_Clear(u16 Color)
{
	unsigned int i,m;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
	LCD_CS_CLR;
	LCD_RS_SET;
	for(i=0;i<lcddev.height;i++)
	{
    for(m=0;m<lcddev.width;m++)
    {
			Lcd_WriteData_16Bit(Color);
		}
	}
	 LCD_CS_SET;
}


void LCD_RESET(void)
{
	LCD_RST_CLR;
	delay_ms(100);
	LCD_RST_SET;
	delay_ms(50);
}

void LCD_Init(void)
{
 	LCD_RESET();
	LCD_WR_REG(0x11);    //Sleep exit
	delay_ms (120);
	//ST7735S Frame Rate
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_REG(0xB2);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_REG(0xB3);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_REG(0xB4); //Column inversion
	LCD_WR_DATA(0x07);
	//ST7735S Power Sequence
	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0xA2);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x84);
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0xC5);
	LCD_WR_REG(0xC2);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xC3);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0x2A);
	LCD_WR_REG(0xC4);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0xEE);
	LCD_WR_REG(0xC5); //VCOM
	LCD_WR_DATA(0x0E);
	LCD_WR_REG(0x36); //MX, MY, RGB mode
	LCD_WR_DATA(0xC8);
	//ST7735S Gamma Sequence
	LCD_WR_REG(0xe0);
	LCD_WR_DATA(0x0f);
	LCD_WR_DATA(0x1a);
	LCD_WR_DATA(0x0f);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x2f);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x20);
	LCD_WR_DATA(0x22);
	LCD_WR_DATA(0x1f);
	LCD_WR_DATA(0x1b);
	LCD_WR_DATA(0x23);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x10);
	LCD_WR_REG(0xe1);
	LCD_WR_DATA(0x0f);
	LCD_WR_DATA(0x1b);
	LCD_WR_DATA(0x0f);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x33);
	LCD_WR_DATA(0x2c);
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0x2e);
	LCD_WR_DATA(0x30);
	LCD_WR_DATA(0x30);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x3f);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x10);
	LCD_WR_REG(0x2a);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x7f);
	LCD_WR_REG(0x2b);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x9f);
	LCD_WR_REG(0xF0); //Enable test command
	LCD_WR_DATA(0x01);
	LCD_WR_REG(0xF6); //Disable ram power save mode
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x3A); //65k mode
	LCD_WR_DATA(0x05);
	LCD_WR_REG(0x29);//Display on
  LCD_direction(USE_HORIZONTAL);	// LCD显示方向
	LCD_LED=1;				//背光
	LCD_Clear(WHITE);  //清屏
}



void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
	LCD_WR_REG(lcddev.setxcmd);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(xStar+lcddev.xoffset);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(xEnd+lcddev.xoffset);

	LCD_WR_REG(lcddev.setycmd);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(yStar+lcddev.yoffset);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(yEnd+lcddev.yoffset);

	LCD_WriteRAM_Prepare();  //开始写入GRAM
}



void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);
}




void LCD_direction(u8 direction)
{
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
	switch(direction){
		case 0:
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;
			lcddev.xoffset=2;
			lcddev.yoffset=1;
			LCD_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			lcddev.xoffset=3;
			lcddev.yoffset=2;
			LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		case 2:
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;
      lcddev.xoffset=2;
			lcddev.yoffset=1;
			LCD_WriteReg(0x36,(1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			lcddev.xoffset=1;
			lcddev.yoffset=2;
			LCD_WriteReg(0x36,(1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		default:break;
	}
}

