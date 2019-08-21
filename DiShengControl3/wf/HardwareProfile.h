#ifndef __HardwareProfile_H__
#define __HardwareProfile_H__

#include "gpio.h"
#include "wfSys.h"

#define SimI2C_Delay_Ex
#define SimI2C_Delay() wfDelay_ms(1);


#define SIMI2C_SCL_Low() HAL_GPIO_WritePin(SimI2C_CLK_GPIO_Port,SimI2C_CLK_Pin,GPIO_PIN_RESET)
#define SIMI2C_SCL_High() HAL_GPIO_WritePin(SimI2C_CLK_GPIO_Port,SimI2C_CLK_Pin,GPIO_PIN_SET)

#define SIMI2C_SDA_Low() HAL_GPIO_WritePin(SimI2C_DATA_GPIO_Port,SimI2C_DATA_Pin,GPIO_PIN_RESET)
#define SIMI2C_SDA_High() HAL_GPIO_WritePin(SimI2C_DATA_GPIO_Port,SimI2C_DATA_Pin,GPIO_PIN_SET)

#define SIMI2C_SDA_Read() HAL_GPIO_ReadPin(SimI2C_DATA_GPIO_Port,SimI2C_DATA_Pin)

#define SIMI2C_SDA_OUT() GPIO_InitTypeDef GPIO_InitStruct_Out;  \
	GPIO_InitStruct_Out.Pin = SimI2C_DATA_Pin;  \
	GPIO_InitStruct_Out.Mode = GPIO_MODE_OUTPUT_PP;  \
	GPIO_InitStruct_Out.Pull = GPIO_PULLUP;  \
	GPIO_InitStruct_Out.Speed = GPIO_SPEED_FREQ_LOW;  \
	HAL_GPIO_Init(SimI2C_DATA_GPIO_Port, &GPIO_InitStruct_Out);	

#define SIMI2C_SDA_IN() GPIO_InitTypeDef GPIO_InitStruct_In;  \
	GPIO_InitStruct_In.Pin = SimI2C_DATA_Pin;  \
	GPIO_InitStruct_In.Mode = GPIO_MODE_INPUT;  \
	GPIO_InitStruct_In.Pull = GPIO_PULLUP;  \
	HAL_GPIO_Init(SimI2C_DATA_GPIO_Port, &GPIO_InitStruct_In);


#define SimI2C_CLK_Holding() GPIO_InitTypeDef GPIO_InitStruct;  \
	GPIO_InitStruct.Pin = SimI2C_CLK_Pin;  \
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  \
	GPIO_InitStruct.Pull = GPIO_PULLUP;  \
	HAL_GPIO_Init(SimI2C_CLK_GPIO_Port, &GPIO_InitStruct);  \
	wfDelay_ms(1);  \
	while(HAL_GPIO_ReadPin(SimI2C_CLK_GPIO_Port,SimI2C_CLK_Pin)==0);  \
	GPIO_InitStruct.Pin = SimI2C_CLK_Pin;  \
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  \
	GPIO_InitStruct.Pull = GPIO_PULLUP;  \
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  \
	HAL_GPIO_Init(SimI2C_CLK_GPIO_Port, &GPIO_InitStruct);


#define SimSPI_SPI3
// #define SimSPI_Delay_Ex
// #define SimSPI_Delay() wfDelay_ms(1);


#define SIMSPI_SCL_Low() HAL_GPIO_WritePin(SPI_CLK_GPIO_Port,SPI_CLK_Pin,GPIO_PIN_RESET)
#define SIMSPI_SCL_High() HAL_GPIO_WritePin(SPI_CLK_GPIO_Port,SPI_CLK_Pin,GPIO_PIN_SET)

#define SIMSPI_SDO_Low() HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port,SPI_MOSI_Pin,GPIO_PIN_RESET)
#define SIMSPI_SDO_High() HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port,SPI_MOSI_Pin,GPIO_PIN_SET)

#define SIMSPI_SDI_Read() HAL_GPIO_ReadPin(SPI_MISO_GPIO_Port,SPI_MISO_Pin)


#define CP1616_Client_AddrLen 0
#define CP1616_Client_DataBufLen 2

#define SetRx_CP1616_Client()
#define SetTx_CP1616_Client()

#define CP1616_Client_TxByteWithVerify(x)// Uart1_VerifySumAddTxByte(x)
#define CP1616_Client_TxByte(x)// Uart1_PutChar(x)

#define Verify_Sum
#include "Verify.h"
//#define CP1616_Client_VerifyProc(pBuf,nIndex) GetVerify_Sum(pBuf,nIndex)
#define CheckVerify_CP1616_Client()	sum=GetVerify_Sum(CP1616_Client_RxList,CP1616_Client_NeedRxCount-2); \
	if(sum==CP1616_Client_RxList[CP1616_Client_NeedRxCount-2])	\
													{sum=1;}\
												else\
													{sum=0;}


#define MAX_CP1616_Client_RX 100

#endif
