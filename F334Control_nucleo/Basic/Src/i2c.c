#include "i2c.h"
#include "main.h"

//I2C_HandleTypeDef hi2c1;


/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
//void MX_I2C1_Init(void)
//{
//
//  /* USER CODE BEGIN I2C1_Init 0 */
//
//  /* USER CODE END I2C1_Init 0 */
//
//  /* USER CODE BEGIN I2C1_Init 1 */
//
//  /* USER CODE END I2C1_Init 1 */
//  hi2c1.Instance = I2C1;
//  hi2c1.Init.Timing = 0x2000090E;
//  hi2c1.Init.OwnAddress1 = 0;
//  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
//  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//  hi2c1.Init.OwnAddress2 = 0;
//  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
//  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
//  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
//  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Analogue filter
//  */
//  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Digital filter
//  */
//  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN I2C1_Init 2 */
//
//  /* USER CODE END I2C1_Init 2 */
//
//}


void I2C1_WriteBytes(uint16_t DevAddress, uint8_t TxData, uint16_t u16Size)
{
	HAL_I2C_Master_Transmit(&hi2c1, DevAddress, (uint8_t*)TxData, u16Size, HAL_MAX_DELAY);

}

uint8_t I2C1_ReadByte(uint16_t DevAddress, uint16_t u16Size)
{
	uint8_t RXData;
	HAL_I2C_Master_Receive(&hi2c1, DevAddress, &RXData, u16Size, HAL_MAX_DELAY);
	return RXData;
}


//void I2C1_Mem_Write_8(uint16_t DevAddress)
//{
//	HAL_I2C_Mem_Write(&hi2c1, DevAddress, i, I2C_MEMADD_SIZE_8BIT,&(I2C_Buffer_Write[i]),8, 1000);
//}
//








