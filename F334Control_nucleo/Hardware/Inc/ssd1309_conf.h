/*
 * ssd1309_conf.h
 *
 *  Created on: 2022年10月10日
 *      Author: Lijialin001
 */

#ifndef INC_SSD1309_CONF_H_
#define INC_SSD1309_CONF_H_


// Choose a bus
//#define SSD1309_USE_I2C
#define SSD1309_USE_SPI

// I2C Configuration
//#define SSD1309_I2C_PORT        hi2c1
//#define SSD1309_I2C_ADDR        (0x3C << 1)

// SPI Configuration
//#define SSD1309_CS_Port         OLED_CS_GPIO_Port
//#define SSD1309_CS_Pin          OLED_CS_Pin
//#define SSD1309_DC_Port         OLED_DC_GPIO_Port
//#define SSD1309_DC_Pin          OLED_DC_Pin
//#define SSD1309_Reset_Port      OLED_Res_GPIO_Port
//#define SSD1309_Reset_Pin       OLED_Res_Pin


// Mirror the screen if needed
// #define SSD1309_MIRROR_VERT
// #define SSD1309_MIRROR_HORIZ

// Set inverse color if needed
// # define SSD1309_INVERSE_COLOR

// Include only needed fonts
#define SSD1309_INCLUDE_FONT_6x8
#define SSD1309_INCLUDE_FONT_7x10
#define SSD1309_INCLUDE_FONT_11x18
#define SSD1309_INCLUDE_FONT_16x26


// Some OLEDs don't display anything in first two columns.
// In this case change the following macro to 130.
// The default value is 128.
// #define SSD1309_WIDTH           130

// The height can be changed as well if necessary.
// It can be 32, 64 or 128. The default value is 64.
// #define SSD1309_HEIGHT          32


#endif /* INC_SSD1306_CONF_H_ */
