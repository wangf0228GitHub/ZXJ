#include "ADS131M06.h"
#include "gpio.h"
#include "spi.h"

uint8_t spiTxList[FrameLen];
uint8_t spiRxList[FrameLen];
uint32_t SPS;
uint32_t myOSRMax;
uint32_t myOSR;
void ADS131_Init(void)
{
	uint32_t i;
	uint16_t reg03;
	HAL_GPIO_WritePin(REST_GPIO_Port, REST_Pin, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(REST_GPIO_Port, REST_Pin, GPIO_PIN_SET);
	for (i = 0; i < FrameLen; i++)
		spiTxList[i] = 0;
	osrADC[0] = 0;
	osrADC[1] = 0;
	osrADC[2] = 0;
	ADS131_SetSPS();
}
void ADS131_ReadADC(void)
{
	while (HAL_GPIO_ReadPin(DRDY_GPIO_Port, DRDY_Pin) != GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);	
	HAL_SPI_TransmitReceive(&hspi1, spiTxList, spiRxList, FrameLen, 100);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}
void ADS131_ReadReg(uint16_t addr)
{
	uint32_t i;
	uint16_t cmd;
	while (HAL_GPIO_ReadPin(DRDY_GPIO_Port, DRDY_Pin) != GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	cmd = 0xa000;
	cmd |= (addr << 7);
	spiTxList[0] = (uint8_t)(cmd >> 8);
	spiTxList[1] = (uint8_t)(cmd);
	HAL_SPI_TransmitReceive(&hspi1, spiTxList, spiRxList, FrameLen, 100);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	spiTxList[0] = 0;
	spiTxList[1] = 0;
	while (HAL_GPIO_ReadPin(DRDY_GPIO_Port, DRDY_Pin) != GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, spiTxList, spiRxList, FrameLen, 100);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	spiTxList[0] = 0;
	spiTxList[1] = 0;
}
void ADS131_SetSPS(void)
{
	uint32_t i;
	uint16_t cmd;
	uint16_t reg03;
	ADS131_ReadReg(0x03);
	reg03 = MAKE_SHORT(spiRxList[0], spiRxList[1]);	
	ADS131_WriteCMD(0x0655);//UNLOCK
	reg03 &= 0xffe3;
	if (SPS == 500)
	{
		reg03 |= (OSR500 << 2);
		myOSRMax = myOSR500;
	}
	else if (SPS == 200)
	{
		reg03 |= (OSR200 << 2);
		myOSRMax = myOSR200;
	}
	else
	{
		reg03 |= (OSR100 << 2);
		myOSRMax = myOSR100;
	}
	ADS131_WriteReg(0x03, reg03);
	ADS131_WriteCMD(0x0555);//LOCK
	myOSR = 0;
}
void ADS131_WriteCMD(uint16_t cmd)
{
	while (HAL_GPIO_ReadPin(DRDY_GPIO_Port, DRDY_Pin) != GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	spiTxList[0] = (uint8_t)(cmd >> 8);
	spiTxList[1] = (uint8_t)(cmd);
	HAL_SPI_TransmitReceive(&hspi1, spiTxList, spiRxList, FrameLen, 100);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	spiTxList[0] = 0;
	spiTxList[1] = 0;
}
void ADS131_WriteReg(uint16_t addr,uint16_t data)
{
	uint16_t cmd;
	while (HAL_GPIO_ReadPin(DRDY_GPIO_Port, DRDY_Pin) != GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	cmd = 0x6000;
	cmd |= (addr << 7);
	spiTxList[0] = (uint8_t)(cmd >> 8);
	spiTxList[1] = (uint8_t)(cmd);
	spiTxList[3] = (uint8_t)(data >> 8);
	spiTxList[4] = (uint8_t)(data);
	HAL_SPI_TransmitReceive(&hspi1, spiTxList, spiRxList, FrameLen, 100);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	spiTxList[0] = 0;
	spiTxList[1] = 0;
}
