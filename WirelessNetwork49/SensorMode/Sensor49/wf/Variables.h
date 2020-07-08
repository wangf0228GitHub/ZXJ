#ifndef   __Variables_h__
#define   __Variables_h__

#include <stdint.h>
#include "main.h"

typedef enum //用于处理A7128_GIO1的下降沿中断
{
	Net_RxData=0U,	//接收数据
	Net_TxComData	,	//发送采集数据
	Net_TxADCData	,	//发送采集数据
	Net_Sleep
}_NetWorkType;
extern volatile _NetWorkType NetWorkType;

extern volatile uint32_t gTempIndex;

typedef union
{	
	struct
	{
		//unsigned bADCDataTX1:1;//当前发送区为1区		
	}Bits;
	uint32_t all;
}_gFlags;
extern volatile _gFlags gFlags;

typedef union
{	
	uint8_t	u8[8];
	uint16_t	u16[4];
	uint32_t	u32[2];
}_ADCData4DMA;
extern volatile _ADCData4DMA ADCData4DMA;

typedef union
{	
	uint8_t	u8[4];
	uint16_t	u16[2];
	uint32_t	u32;
	float f;
}_EEData;

extern _EEData SensorIDData;
extern _EEData Linear_k;
extern _EEData Linear_b;
extern _EEData SensorGain;
extern volatile uint32_t TimeIndex;

extern uint32_t bAbnormal;

extern volatile uint32_t ADCSaveIndex;
extern volatile uint8_t ADCData4[7680+7680];

extern volatile uint32_t ADCData4TxEnd;
extern volatile uint32_t ADCData4TxStart;
extern uint32_t ADCBATData;

extern volatile uint32_t bCalibrationNet;


extern uint32_t TxStartTimeIndex;
extern uint32_t TxEndTimeIndex;
extern uint32_t SensorAddr;

extern uint32_t bNewFrame;
extern uint8_t PCM_TxBuf[50];

#define SensorTypeMax 4
extern uint32_t SensorType;
extern const uint32_t tim2Prescaler[SensorTypeMax];
extern const uint32_t tim2Period[SensorTypeMax];
extern const uint32_t ADCDataMax[SensorTypeMax];
extern const uint32_t ADCDataLen[SensorTypeMax];
#define wfEEPROM_BASE_ADDR    0x08080000 
#define wfEEPROM_ReadWord(Addr) *((uint32_t*)(wfEEPROM_BASE_ADDR+Addr))
#define wfEEPROM_WriteWord(Addr,x) HAL_FLASHEx_DATAEEPROM_Unlock();HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,wfEEPROM_BASE_ADDR + Addr,x);HAL_FLASHEx_DATAEEPROM_Lock()
#endif
