#ifndef __SimSPI_Conf_h__
#define __SimSPI_Conf_h__

#include "gpio.h"
#include "wfSys.h"

#define SimSPI_SPI3
// #define SimSPI_Delay_Ex
// #define SimSPI_Delay() wfDelay_ms(1);


#define SIMSPI_SCL_Low() HAL_GPIO_WritePin(SPI_CLK_GPIO_Port,SPI_CLK_Pin,GPIO_PIN_RESET)
#define SIMSPI_SCL_High() HAL_GPIO_WritePin(SPI_CLK_GPIO_Port,SPI_CLK_Pin,GPIO_PIN_SET)

#define SIMSPI_SDO_Low() HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port,SPI_MOSI_Pin,GPIO_PIN_RESET)
#define SIMSPI_SDO_High() HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port,SPI_MOSI_Pin,GPIO_PIN_SET)

#define SIMSPI_SDI_Read() HAL_GPIO_ReadPin(SPI_MISO_GPIO_Port,SPI_MISO_Pin)
#endif


