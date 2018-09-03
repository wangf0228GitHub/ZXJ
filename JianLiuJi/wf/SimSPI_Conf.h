#ifndef __SimSPI_Conf_h__
#define __SimSPI_Conf_h__

#include "gpio.h"
#include "wfSys.h"

//#define SimSPI_SPI3

#define SIMSPI_SCL_Low() HAL_GPIO_WritePin(AD_SCLK_GPIO_Port,AD_SCLK_Pin,GPIO_PIN_RESET)
#define SIMSPI_SCL_High() HAL_GPIO_WritePin(AD_SCLK_GPIO_Port,AD_SCLK_Pin,GPIO_PIN_SET)

#define SIMSPI_SDO_Low() HAL_GPIO_WritePin(AD_MOSI_GPIO_Port,AD_MOSI_Pin,GPIO_PIN_RESET)
#define SIMSPI_SDO_High() HAL_GPIO_WritePin(AD_MOSI_GPIO_Port,AD_MOSI_Pin,GPIO_PIN_SET)

#define SIMSPI_SDI_Read() HAL_GPIO_ReadPin(AD_MISO_GPIO_Port,AD_MISO_Pin)

#endif


