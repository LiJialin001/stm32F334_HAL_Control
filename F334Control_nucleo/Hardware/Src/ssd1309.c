/*
 * ssd1309.c
 *
 *  Created on: Oct 10, 2022
 *      Author: Lijialin001
 */


#include "ssd1309.h"
#include "spi.h"
#include "sys.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>  // For memcpy


#if defined(SSD1309_USE_I2C)

void ssd1309_Reset(void) {
    /* for I2C - do nothing */
}

// Send a byte to the command register
void ssd1309_WriteCommand(uint8_t byte) {
    HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x00, 1, &byte, 1, HAL_MAX_DELAY);
}

// Send data
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size) {
    HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x40, 1, buffer, buff_size, HAL_MAX_DELAY);
}

#elif defined(SSD1309_USE_SPI)

void ssd1309_Reset(void) {
    // CS = High (not selected)
    HAL_GPIO_WritePin(SSD1309_CS_Port, SSD1309_CS_Pin, GPIO_PIN_SET);

    // Reset the OLED
    HAL_GPIO_WritePin(SSD1309_Reset_Port, SSD1309_Reset_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(SSD1309_Reset_Port, SSD1309_Reset_Pin, GPIO_PIN_SET);
    HAL_Delay(10);
}

// Send a byte to the command register
void ssd1309_WriteCommand(uint8_t byte) {
    HAL_GPIO_WritePin(SSD1309_CS_Port, SSD1309_CS_Pin, GPIO_PIN_RESET); // select OLED
    HAL_GPIO_WritePin(SSD1309_DC_Port, SSD1309_DC_Pin, GPIO_PIN_RESET); // command
    SPI_WriteByte(byte);
    HAL_GPIO_WritePin(SSD1309_CS_Port, SSD1309_CS_Pin, GPIO_PIN_SET); // un-select OLED
}

// Send data
void ssd1309_WriteData(uint8_t* buffer, size_t buff_size) {
    HAL_GPIO_WritePin(SSD1309_CS_Port, SSD1309_CS_Pin, GPIO_PIN_RESET); // select OLED
    HAL_GPIO_WritePin(SSD1309_DC_Port, SSD1309_DC_Pin, GPIO_PIN_SET); // data
    SPI_WriteSomeByte( buffer, buff_size);
    HAL_GPIO_WritePin(SSD1309_CS_Port, SSD1309_CS_Pin, GPIO_PIN_SET); // un-select OLED
}

#else
#error "You should define SSD1309_USE_SPI or SSD1309_USE_I2C macro"
#endif

// Screenbuffer
static uint8_t SSD1309_Buffer[SSD1309_BUFFER_SIZE];

// Screen object
static SSD1309_t SSD1309;


/* Fills the Screenbuffer with values from a given buffer of a fixed length */
SSD1309_Error_t ssd1309_FillBuffer(uint8_t* buf, uint32_t len) {
    SSD1309_Error_t ret = SSD1309_ERR;
    if (len <= SSD1309_BUFFER_SIZE) {
        memcpy(SSD1309_Buffer,buf,len);
        ret = SSD1309_OK;
    }
    return ret;
}


// Initialize the oled screen
void ssd1309_Init(void) {
    // Reset OLED
    ssd1309_Reset();

    // Wait for the screen to boot
    delay_ms(100);

    // Init OLED
    ssd1309_SetDisplayOn(0); //display off

    ssd1309_WriteCommand(0x20); //Set Memory Addressing Mode
    ssd1309_WriteCommand(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
                                // 10b,Page Addressing Mode (RESET); 11b,Invalid

    ssd1309_WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7

#ifdef SSD1309_MIRROR_VERT
    ssd1309_WriteCommand(0xC0); // Mirror vertically
#else
    ssd1309_WriteCommand(0xC8); //Set COM Output Scan Direction
#endif

    ssd1309_WriteCommand(0x00); //---set low column address
    ssd1309_WriteCommand(0x10); //---set high column address

    ssd1309_WriteCommand(0x40); //--set start line address - CHECK

    ssd1309_SetContrast(0xFF);

#ifdef SSD1309_MIRROR_HORIZ
    ssd1309_WriteCommand(0xA0); // Mirror horizontally
#else
    ssd1309_WriteCommand(0xA1); //--set segment re-map 0 to 127 - CHECK
#endif

#ifdef SSD1309_INVERSE_COLOR
    ssd1309_WriteCommand(0xA7); //--set inverse color
#else
    ssd1309_WriteCommand(0xA6); //--set normal color
#endif

// Set multiplex ratio.
#if (SSD1309_HEIGHT == 128)
    // Found in the Luma Python lib for SH1106.
    ssd1309_WriteCommand(0xFF);
#else
    ssd1309_WriteCommand(0xA8); //--set multiplex ratio(1 to 64) - CHECK
#endif

#if (SSD1309_HEIGHT == 32)
    ssd1309_WriteCommand(0x1F); //
#elif (SSD1309_HEIGHT == 64)
    ssd1309_WriteCommand(0x3F); //
#elif (SSD1309_HEIGHT == 128)
    ssd1309_WriteCommand(0x3F); // Seems to work for 128px high displays too.
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1309_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    ssd1309_WriteCommand(0xD3); //-set display offset - CHECK
    ssd1309_WriteCommand(0x00); //-not offset

    ssd1309_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
    ssd1309_WriteCommand(0xF0); //--set divide ratio

    ssd1309_WriteCommand(0xD9); //--set pre-charge period
    ssd1309_WriteCommand(0x22); //

    ssd1309_WriteCommand(0xDA); //--set com pins hardware configuration - CHECK
#if (SSD1309_HEIGHT == 32)
    ssd1309_WriteCommand(0x02);
#elif (SSD1309_HEIGHT == 64)
    ssd1309_WriteCommand(0x12);
#elif (SSD1309_HEIGHT == 128)
    ssd1309_WriteCommand(0x12);
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1309_WriteCommand(0xDB); //--set vcomh
    ssd1309_WriteCommand(0x20); //0x20,0.77xVcc

    ssd1309_WriteCommand(0x8D); //--set DC-DC enable
    ssd1309_WriteCommand(0x14); //
    ssd1309_SetDisplayOn(1); //--turn on SSD1306 panel

    // Clear screen
    ssd1309_Fill(Black);

    // Flush buffer to screen
    ssd1309_UpdateScreen();

    // Set default values for screen object
    SSD1309.CurrentX = 0;
    SSD1309.CurrentY = 0;

    SSD1309.Initialized = 1;
}

// Fill the whole screen with the given color
void ssd1309_Fill(SSD1309_COLOR color) {
    /* Set memory */
    uint32_t i;

    for(i = 0; i < sizeof(SSD1309_Buffer); i++) {
        SSD1309_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
    }
}

// Write the screenbuffer with changed to the screen
void ssd1309_UpdateScreen(void) {
    // Write data to each page of RAM. Number of pages
    // depends on the screen height:
    //
    //  * 32px   ==  4 pages
    //  * 64px   ==  8 pages
    //  * 128px  ==  16 pages
    for(uint8_t i = 0; i < SSD1309_HEIGHT/8; i++) {
        ssd1309_WriteCommand(0xB0 + i); // Set the current RAM page address.
        ssd1309_WriteCommand(0x00 + SSD1309_X_OFFSET_LOWER);
        ssd1309_WriteCommand(0x10 + SSD1309_X_OFFSET_UPPER);
        ssd1309_WriteData(&SSD1309_Buffer[SSD1309_WIDTH*i],SSD1309_WIDTH);
    }
}


//    Draw one pixel in the screenbuffer
//    X => X Coordinate
//    Y => Y Coordinate
//    color => Pixel color
void ssd1309_DrawPixel(uint8_t x, uint8_t y, SSD1309_COLOR color) {
    if(x >= SSD1309_WIDTH || y >= SSD1309_HEIGHT) {
        // Don't write outside the buffer
        return;
    }

    // Draw in the right color
    if(color == White) {
        SSD1309_Buffer[x + (y / 8) * SSD1309_WIDTH] |= 1 << (y % 8);
    } else {
        SSD1309_Buffer[x + (y / 8) * SSD1309_WIDTH] &= ~(1 << (y % 8));
    }
}


// Draw 1 char to the screen buffer
// ch       => char om weg te schrijven
// Font     => Font waarmee we gaan schrijven
// color    => Black or White
char ssd1309_WriteChar(char ch, FontDef Font, SSD1309_COLOR color) {
    uint32_t i, b, j;

    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;

    // Check remaining space on current line
    if (SSD1309_WIDTH < (SSD1309.CurrentX + Font.FontWidth) ||
        SSD1309_HEIGHT < (SSD1309.CurrentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
                ssd1309_DrawPixel(SSD1309.CurrentX + j, (SSD1309.CurrentY + i), (SSD1309_COLOR) color);
            } else {
                ssd1309_DrawPixel(SSD1309.CurrentX + j, (SSD1309.CurrentY + i), (SSD1309_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    SSD1309.CurrentX += Font.FontWidth;

    // Return written char for validation
    return ch;
}


// Write full string to screenbuffer
char ssd1309_WriteString(char* str, FontDef Font, SSD1309_COLOR color) {
    // Write until null-byte
    while (*str) {
        if (ssd1309_WriteChar(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }

        // Next char
        str++;
    }

    // Everything ok
    return *str;
}

// Position the cursor
void ssd1309_SetCursor(uint8_t x, uint8_t y) {
    SSD1309.CurrentX = x;
    SSD1309.CurrentY = y;
}


// Draw line by Bresenhem's algorithm
void ssd1309_Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1309_COLOR color) {
  int32_t deltaX = abs(x2 - x1);
  int32_t deltaY = abs(y2 - y1);
  int32_t signX = ((x1 < x2) ? 1 : -1);
  int32_t signY = ((y1 < y2) ? 1 : -1);
  int32_t error = deltaX - deltaY;
  int32_t error2;

  ssd1309_DrawPixel(x2, y2, color);
    while((x1 != x2) || (y1 != y2))
    {
    ssd1309_DrawPixel(x1, y1, color);
    error2 = error * 2;
    if(error2 > -deltaY)
    {
      error -= deltaY;
      x1 += signX;
    }
    else
    {
    /*nothing to do*/
    }

    if(error2 < deltaX)
    {
      error += deltaX;
      y1 += signY;
    }
    else
    {
    /*nothing to do*/
    }
  }
  return;
}

//Draw polyline
void ssd1309_Polyline(const SSD1309_VERTEX *par_vertex, uint16_t par_size, SSD1309_COLOR color) {
  uint16_t i;
  if(par_vertex != 0){
    for(i = 1; i < par_size; i++){
      ssd1309_Line(par_vertex[i - 1].x, par_vertex[i - 1].y, par_vertex[i].x, par_vertex[i].y, color);
    }
  }
  else
  {
    /*nothing to do*/
  }
  return;
}

/*Convert Degrees to Radians*/
static float ssd1309_DegToRad(float par_deg) {
    return par_deg * 3.14 / 180.0;
}


/*Normalize degree to [0;360]*/
static uint16_t ssd1309_NormalizeTo0_360(uint16_t par_deg) {
  uint16_t loc_angle;
  if(par_deg <= 360)
  {
    loc_angle = par_deg;
  }
  else
  {
    loc_angle = par_deg % 360;
    loc_angle = ((par_deg != 0)?par_deg:360);
  }
  return loc_angle;
}


/*DrawArc. Draw angle is beginning from 4 quart of trigonometric circle (3pi/2)
 * start_angle in degree
 * sweep in degree
 */
void ssd1309_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1309_COLOR color) {
    #define CIRCLE_APPROXIMATION_SEGMENTS 36
    float approx_degree;
    uint32_t approx_segments;
    uint8_t xp1,xp2;
    uint8_t yp1,yp2;
    uint32_t count = 0;
    uint32_t loc_sweep = 0;
    float rad;

    loc_sweep = ssd1309_NormalizeTo0_360(sweep);

    count = (ssd1309_NormalizeTo0_360(start_angle) * CIRCLE_APPROXIMATION_SEGMENTS) / 360;
    approx_segments = (loc_sweep * CIRCLE_APPROXIMATION_SEGMENTS) / 360;
    approx_degree = loc_sweep / (float)approx_segments;
    while(count < approx_segments)
    {
        rad = ssd1309_DegToRad(count*approx_degree);
        xp1 = x + (int8_t)(sin(rad)*radius);
        yp1 = y + (int8_t)(cos(rad)*radius);
        count++;
        if(count != approx_segments)
        {
            rad = ssd1309_DegToRad(count*approx_degree);
        }
        else
        {
            rad = ssd1309_DegToRad(loc_sweep);
        }
        xp2 = x + (int8_t)(sin(rad)*radius);
        yp2 = y + (int8_t)(cos(rad)*radius);
        ssd1309_Line(xp1,yp1,xp2,yp2,color);
    }

    return;
}

//Draw circle by Bresenhem's algorithm
void ssd1309_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r,SSD1309_COLOR par_color) {
  int32_t x = -par_r;
  int32_t y = 0;
  int32_t err = 2 - 2 * par_r;
  int32_t e2;

  if (par_x >= SSD1309_WIDTH || par_y >= SSD1309_HEIGHT) {
    return;
  }

    do {
      ssd1309_DrawPixel(par_x - x, par_y + y, par_color);
      ssd1309_DrawPixel(par_x + x, par_y + y, par_color);
      ssd1309_DrawPixel(par_x + x, par_y - y, par_color);
      ssd1309_DrawPixel(par_x - x, par_y - y, par_color);
        e2 = err;
        if (e2 <= y) {
            y++;
            err = err + (y * 2 + 1);
            if(-x == y && e2 <= x) {
              e2 = 0;
            }
            else
            {
              /*nothing to do*/
            }
        }
        else
        {
          /*nothing to do*/
        }
        if(e2 > x) {
          x++;
          err = err + (x * 2 + 1);
        }
        else
        {
          /*nothing to do*/
        }
    } while(x <= 0);

    return;
}


//Draw rectangle
void ssd1309_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1309_COLOR color) {
  ssd1309_Line(x1,y1,x2,y1,color);
  ssd1309_Line(x2,y1,x2,y2,color);
  ssd1309_Line(x2,y2,x1,y2,color);
  ssd1309_Line(x1,y2,x1,y1,color);

  return;
}


//Draw bitmap - ported from the ADAFruit GFX library

void ssd1309_DrawBitmap(uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1309_COLOR color)
{
    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    if (x >= SSD1309_WIDTH || y >= SSD1309_HEIGHT) {
        return;
    }

    for (uint8_t j = 0; j < h; j++, y++) {
        for (uint8_t i = 0; i < w; i++) {
            if (i & 7)
                byte <<= 1;
            else
                byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
            if (byte & 0x80)
                ssd1309_DrawPixel(x + i, y, color);
        }
    }
    return;
}


void ssd1309_SetContrast(const uint8_t value) {
    const uint8_t kSetContrastControlRegister = 0x81;
    ssd1309_WriteCommand(kSetContrastControlRegister);
    ssd1309_WriteCommand(value);
}

void ssd1309_SetDisplayOn(const uint8_t on) {
    uint8_t value;
    if (on) {
        value = 0xAF;   // Display on
        SSD1309.DisplayOn = 1;
    } else {
        value = 0xAE;   // Display off
        SSD1309.DisplayOn = 0;
    }
    ssd1309_WriteCommand(value);
}

uint8_t ssd1309_GetDisplayOn() {
    return SSD1309.DisplayOn;
}


void ssd1309_TestFPS() {
    ssd1309_Fill(White);

    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    int fps = 0;
    char message[] = "ABCDEFGHIJK";

    ssd1309_SetCursor(2,0);
    ssd1309_WriteString("Testing...", Font_11x18, Black);
    ssd1309_SetCursor(2, 18*2);
    ssd1309_WriteString("0123456789A", Font_11x18, Black);

    do {
        ssd1309_SetCursor(2, 18);
        ssd1309_WriteString(message, Font_11x18, Black);
        ssd1309_UpdateScreen();

        char ch = message[0];
        memmove(message, message+1, sizeof(message)-2);
        message[sizeof(message)-2] = ch;

        fps++;
        end = HAL_GetTick();
    } while((end - start) < 5000);

    HAL_Delay(5000);

    char buff[64];
    fps = (float)fps / ((end - start) / 1000.0);
    snprintf(buff, sizeof(buff), "~%d FPS", fps);

    ssd1309_Fill(White);
    ssd1309_SetCursor(2, 2);
    ssd1309_WriteString(buff, Font_11x18, Black);
    ssd1309_UpdateScreen();
}

void ssd1309_TestFonts() {
    uint8_t y = 0;
    ssd1309_Fill(Black);

    #ifdef SSD1309_INCLUDE_FONT_16x26
    ssd1309_SetCursor(2, y);
    ssd1309_WriteString("Font 16x26", Font_16x26, White);
    y += 26;
    #endif

    #ifdef SSD1309_INCLUDE_FONT_11x18
    ssd1309_SetCursor(2, y);
    ssd1309_WriteString("Font 11x18", Font_11x18, White);
    y += 18;
    #endif

    #ifdef SSD1309_INCLUDE_FONT_7x10
    ssd1309_SetCursor(2, y);
    ssd1309_WriteString("Font 7x10", Font_7x10, White);
    y += 10;
    #endif

    #ifdef SSD1309_INCLUDE_FONT_6x8
    ssd1309_SetCursor(2, y);
    ssd1309_WriteString("Font 6x8", Font_6x8, White);
    #endif

    ssd1309_UpdateScreen();
}

void ssd1309_TestBorder() {
    ssd1309_Fill(Black);

    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    uint8_t x = 0;
    uint8_t y = 0;
    do {
        ssd1309_DrawPixel(x, y, Black);

        if((y == 0) && (x < 127))
            x++;
        else if((x == 127) && (y < (SSD1309_HEIGHT-1)))
            y++;
        else if((y == (SSD1309_HEIGHT-1)) && (x > 0))
            x--;
        else
            y--;

        ssd1309_DrawPixel(x, y, White);
        ssd1309_UpdateScreen();

        HAL_Delay(5);
        end = HAL_GetTick();
    } while((end - start) < 8000);

    HAL_Delay(1000);
}


void ssd1309_TestLine() {

  ssd1309_Line(1,1,SSD1309_WIDTH - 1,SSD1309_HEIGHT - 1,White);
  ssd1309_Line(SSD1309_WIDTH - 1,1,1,SSD1309_HEIGHT - 1,White);
  ssd1309_UpdateScreen();
  return;
}

void ssd1309_TestRectangle() {
  uint32_t delta;

  for(delta = 0; delta < 5; delta ++) {
    ssd1309_DrawRectangle(1 + (5*delta),1 + (5*delta) ,SSD1309_WIDTH-1 - (5*delta),SSD1309_HEIGHT-1 - (5*delta),White);
  }
  ssd1309_UpdateScreen();
  return;
}

void ssd1309_TestCircle() {
  uint32_t delta;

  for(delta = 0; delta < 5; delta ++) {
    ssd1309_DrawCircle(20* delta+30, 15, 10, White);
  }
  ssd1309_UpdateScreen();
  return;
}

void ssd1309_TestArc() {
  ssd1309_DrawArc(30, 30, 30, 20, 270, White);
  ssd1309_UpdateScreen();
  return;
}


void ssd1309_TestPolyline() {
  SSD1309_VERTEX loc_vertex[] =
  {
      {35,40},
      {40,20},
      {45,28},
      {50,10},
      {45,16},
      {50,10},
      {53,16}
  };

  ssd1309_Polyline(loc_vertex,sizeof(loc_vertex)/sizeof(loc_vertex[0]),White);
  ssd1309_UpdateScreen();
  return;
}


void ssd1309_TestAll() {
    ssd1309_Init();
    ssd1309_TestFPS();
    HAL_Delay(3000);
    ssd1309_TestBorder();
    ssd1309_TestFonts();
    HAL_Delay(3000);
    ssd1309_Fill(Black);
    ssd1309_TestRectangle();
    ssd1309_TestLine();
    HAL_Delay(3000);
    ssd1309_Fill(Black);
    ssd1309_TestPolyline();
    HAL_Delay(3000);
    ssd1309_Fill(Black);
    ssd1309_TestArc();
    HAL_Delay(3000);
    ssd1309_Fill(Black);
    ssd1309_TestCircle();
    HAL_Delay(3000);
}



