#ifndef _I2C_H
#define _I2C_H


#include "stm32f3xx_hal.h"



//void MX_I2C1_Init(void);

void I2C1_WriteBytes(uint16_t DevAddress, uint8_t TxData, uint16_t u16Size);
uint8_t I2C1_ReadByte(uint16_t DevAddress, uint16_t u16Size);

//void I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t TxData, uint16_t Size);


#endif
