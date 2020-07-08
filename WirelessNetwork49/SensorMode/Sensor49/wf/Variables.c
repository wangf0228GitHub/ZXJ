#include "Variables.h"

volatile uint32_t gTempIndex;

volatile _NetWorkType NetWorkType;
volatile _gFlags gFlags;
volatile uint32_t TimeIndex;
volatile _ADCData4DMA ADCData4DMA;
volatile uint32_t ADCSaveIndex;
volatile uint8_t ADCData4[7680+7680];

volatile uint32_t ADCData4TxEnd;
volatile uint32_t ADCData4TxStart;

volatile uint32_t bCalibrationNet;

uint32_t bAbnormal;

_EEData SensorIDData;
_EEData Linear_k;
_EEData Linear_b;
_EEData SensorGain;
uint32_t ADCBATData;

uint32_t TxStartTimeIndex;
uint32_t TxEndTimeIndex;//���1֡Ӧ��ADCDataSendCommand_BATָ��ͣ�֡�����������������ֽڣ�Ϊ��ص���
uint32_t SensorAddr;

uint32_t bNewFrame;
uint8_t PCM_TxBuf[50];
/************************************************************************/
/* ��Ƶ����Ƶ����Ƶ������                                             */
/************************************************************************/
uint32_t SensorType;
const uint32_t tim2Prescaler[SensorTypeMax]={0,1,15,999};
const uint32_t tim2Period[SensorTypeMax]={6249,49999,49999,31999};
const uint32_t ADCDataMax[SensorTypeMax]={7680+7680,480+480,60+60,1};
const uint32_t ADCDataLen[SensorTypeMax]={7680,480,60,1};

// void wfFlash_ReadDoubleWords(uint32_t Addr,uint64_t *Buffer,uint32_t Length)  
// {  
// 	uint64_t *wAddr;  
// 	wAddr=(uint64_t*)(wfFlash_BASE_ADDR+Addr);  
// 	while(Length--)
// 	{  
// 		*Buffer++=*wAddr++;  
// 	}     
// }
// void STMFLASH_Write(uint32_t WriteAddr,uint64_t *pBuffer,uint32_t NumToWrite)	
// { 
// 	uint32_t i;
// 	FLASH_EraseInitTypeDef FlashEraseInit;
// 	HAL_StatusTypeDef FlashStatus=HAL_OK;
// 	uint32_t SectorError=0;
// 	HAL_FLASH_Unlock();             //����	
// 	FlashEraseInit.TypeErase=FLASH_TYPEERASE_PAGES;       //�������ͣ�ҳ���� 
// 	FlashEraseInit.Page=FlashPage;   //Ҫ������ҳ����д���ַ
// 	FlashEraseInit.NbPages=1;               //ֻ����һҳ
// 	if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
// 	{
// 		HAL_FLASH_Lock();           //����
// 		return;//����������	
// 	}	
// 	for(i=0;i<NumToWrite;i++)
// 	{
// 		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,wfFlash_BASE_ADDR+WriteAddr,*pBuffer)!=HAL_OK)//д������
// 		{ 
// 			break;	//д���쳣
// 		}
// 		WriteAddr+=8;
// 		pBuffer++;
// 	}
// 	HAL_FLASH_Lock();           //����
// } 