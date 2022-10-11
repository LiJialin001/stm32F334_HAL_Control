#include "spi.h"
#include "main.h"

// 私有变量
//SPI_HandleTypeDef hspi1;


/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
//void MX_SPI1_Init(void)
//{
//
//  /* USER CODE BEGIN SPI1_Init 0 */
//
//  /* USER CODE END SPI1_Init 0 */
//
//  /* USER CODE BEGIN SPI1_Init 1 */
//
//  /* USER CODE END SPI1_Init 1 */
//  /* SPI1 parameter configuration*/
//  hspi1.Instance = SPI1;
//  hspi1.Init.Mode = SPI_MODE_MASTER;
//  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
//  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
//  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
//  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
//  hspi1.Init.NSS = SPI_NSS_SOFT;
//  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
//  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
//  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
//  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//  hspi1.Init.CRCPolynomial = 10;
//  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
//  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
//  if (HAL_SPI_Init(&hspi1) != HAL_OK)
//  {
////    Error_Handler();
//	  __disable_irq();
//	  while (1)
//	  {
//	  }
//  }
//  /* USER CODE BEGIN SPI1_Init 2 */
//
//  /* USER CODE END SPI1_Init 2 */
//
//}


/**
  * @brief SPI1 ReadWriteByte Function
  * @param TxData:要写入的字节
  * @retval 读取到的字节
  */
uint8_t SPI_ReadWriteByte(uint8_t TxData)
{
	uint8_t Rxdata;
	HAL_SPI_TransmitReceive(&hspi1,&TxData,&Rxdata,1, HAL_MAX_DELAY);
	return Rxdata;
}


/**
  * @brief SPI1 WriteByte Function
  * @param TxData:要写入的字节
  * @retval None
  */
void SPI_WriteByte(uint8_t TxData)
{
	HAL_SPI_Transmit(&hspi1,&TxData,1, HAL_MAX_DELAY);
}


/**
  * @brief SPI1 ReadByte Function
  * @param None
  * @retval 读取到的字节
  */
uint8_t SPI_ReadByte(void)
{
	uint8_t Rxdata;
	HAL_SPI_Receive(&hspi1,&Rxdata,1, HAL_MAX_DELAY);
	return Rxdata;
}

/**
  * @brief SPI1 ReadWrite2Byte Function
  * @param TxData:要写入的字 16bit
  * @retval 读取到的字 16bit
  */
uint16_t SPI_ReadWrite2Byte(uint16_t TxData)
{
	uint16_t Rxdata;
	uint8_t RxByte1, RxByte2;
	RxByte1 = SPI_ReadWriteByte(TxData>>8);   // 处理高八位
	RxByte2 = SPI_ReadWriteByte(TxData);
	Rxdata = RxByte1<<8;
	Rxdata += RxByte2;
	return Rxdata;
}

/**
  * @brief SPI1 Write2Byte Function
  * @param TxData:要写入的字
  * @retval None
  */
void SPI_Write2Byte(uint16_t TxData)
{
	SPI_WriteByte(TxData>>8);   // 处理高八位
	SPI_WriteByte(TxData);
}

/**
  * @brief SPI1 Read2Byte Function
  * @param None
  * @retval 读取到的字 16bit
  */
uint16_t SPI_Read2Byte(void)
{
	uint16_t Rxdata;
	uint8_t RxByte1, RxByte2;
	RxByte1 = SPI_ReadByte();   // 接收高八位   Todo: 不一定对
	RxByte2 = SPI_ReadByte();
	Rxdata = RxByte1<<8;
	Rxdata += RxByte2;
	return Rxdata;
}


/**
  * @brief SPI1 Write一组Byte Function
  * @param TxData:要写入的字节
  * @param u16Size:写入几组字节
  * @retval None
  */
void SPI_WriteSomeByte(uint8_t* TxData, uint16_t u16Size)
{
	HAL_SPI_Transmit(&hspi1, TxData, u16Size, HAL_MAX_DELAY);
}

