#ifndef _SPI_H
#define _SPI_H

#include "stm32f3xx_hal.h"


//void MX_SPI1_Init(void);
uint8_t SPI_ReadWriteByte(uint8_t TxData);
void SPI_WriteByte(uint8_t TxData);
uint8_t SPI_ReadByte(void);

uint16_t SPI_ReadWrite2Byte(uint16_t TxData);
void SPI_Write2Byte(uint16_t TxData);
uint16_t SPI_Read2Byte(void);

void SPI_WriteSomeByte(uint8_t* TxData, uint16_t u16Size);

#endif
