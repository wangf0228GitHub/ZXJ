#ifndef __HardwareProfile_H__
#define __HardwareProfile_H__
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



#define SimSPI2
// #define SimSPI_Delay_Ex
// #define SimSPI_Delay() wfDelay_ms(1);


#define SIMSPI2_SCL_Low() HAL_GPIO_WritePin(AD_SCLK_GPIO_Port,AD_SCLK_Pin,GPIO_PIN_RESET)
#define SIMSPI2_SCL_High() HAL_GPIO_WritePin(AD_SCLK_GPIO_Port,AD_SCLK_Pin,GPIO_PIN_SET)

#define SIMSPI2_SDO_Low() HAL_GPIO_WritePin(AD_MOSI_GPIO_Port,AD_MOSI_Pin,GPIO_PIN_RESET)
#define SIMSPI2_SDO_High() HAL_GPIO_WritePin(AD_MOSI_GPIO_Port,AD_MOSI_Pin,GPIO_PIN_SET)

#define SIMSPI2_SDI_Read() HAL_GPIO_ReadPin(AD_MISO_GPIO_Port,AD_MISO_Pin)


#include "SimSPI.h"

#define ADS8689_CS_Low() HAL_GPIO_WritePin(AD_CS_GPIO_Port,AD_CS_Pin,GPIO_PIN_RESET)
#define ADS8689_CS_High() HAL_GPIO_WritePin(AD_CS_GPIO_Port,AD_CS_Pin,GPIO_PIN_SET)

#define ADS8689_RVS_Read() HAL_GPIO_ReadPin(AD_RVS_GPIO_Port,AD_RVS_Pin)

#define ADS8689_SPIProc(x) SimSPI2_Proc(x)

#define CP1616_Client_AddrLen 0
#define CP1616_Client_DataBufLen 2

#define SetRx_CP1616_Client()
#define SetTx_CP1616_Client()

// #define CP1616_Client_Tx_OneByOne
// #define CP1616_Client_TxByteWithVerify(x)// Uart1_VerifySumAddTxByte(x)
// #define CP1616_Client_TxByte(x)// Uart1_PutChar(x)
#define CP1616_Client_TxProc(pBuf,len) //HAL_UART_Transmit(&huart3,pBuf,len,1000)

#define Verify_Sum
#include "Verify.h"
#define CP1616_Client_VerifyProc(pBuf,len) GetVerify_Sum(pBuf,len)


#define MAX_CP1616_Client_RX 100
#endif
