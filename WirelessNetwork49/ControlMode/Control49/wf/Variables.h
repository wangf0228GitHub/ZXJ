#ifndef   __Variables_h__
#define   __Variables_h__

#include <stdint.h>
#include "main.h"

typedef enum //���ڴ���A7128_GIO1���½����ж�
{
	A7128Work_FrameSync = 0U,//����ͬ��
	A7128Work_RxADCData,	//����ADC����
	A7128Work_RxComData,	//����ָ������
	A7128Work_AbnormalTx, //�쳣����������ɺ�ת���յȴ��ʴ�����
	A7128Work_AbnormalRx, //�쳣����������ɺ��ټ������������쳣
	A7128Work_OnlyTx,		//�����ͣ�����ֹͣ���硢�������硢���ѵȲ���
}_A7128Work;
extern volatile _A7128Work A7128Work;


typedef enum //���ڴ���A7128_GIO1���½����ж�
{
 	Net_Start,//����Ҫ����������
 	Net_Stop,//����Ҫ��ֹͣ����
}_NetWorkMode;
extern volatile _NetWorkMode NetWorkMode;

extern volatile uint32_t gTempIndex;

typedef union
{	
	struct
	{
		unsigned bCarIR:1;		
	}Bits;
	uint32_t all;
}_gFlags;
extern volatile _gFlags gFlags;

typedef union
{	
	struct
	{
		uint8_t H[4][128][60];
		uint8_t M[6][8][60];
		uint8_t L[90][60];		
	};
	uint32_t all[9750];
}_ADCData;
extern _ADCData ADCData4TX1;//7680*4+480*6+60*90
extern _ADCData ADCData4TX2;
extern _ADCData* ADCData4TXBuf;
extern _ADCData* ADCData4SaveBuf;

typedef union
{	
	struct
	{
		uint8_t H[4][128];
		uint8_t M[6][8];
		uint8_t L[92];//90		
	};
	uint32_t all[163];
}_ADCDataTag;
extern _ADCDataTag ADCDataTag;

typedef union
{	
	struct
	{
		uint8_t H[4];
		uint8_t M[8];//6
		uint8_t L[92];//90		
	};
	uint32_t all[26];
}_SensorBAT;
extern _SensorBAT SensorBAT;


typedef union
{	
	struct
	{
		uint8_t H[4];
		uint8_t M[8];//6
		uint8_t L[92];//90		
	};
	uint32_t all[26];
}_SensorSignIn;
extern _SensorSignIn SensorSignIn;//�ڵ��Ƿ����

extern volatile uint32_t TimeIndex;

extern volatile uint32_t gMEMDMA2;


#define PCM_RxFrameLen 9
extern uint8_t PCM_RxBuf[PCM_RxFrameLen];//16 16 cc 00 02 p1 p2 sum 0d 
extern uint8_t PCM_TxBuf[50];//16 16 cc len len 
extern uint8_t PCM_TxBuf_Ender[1];//0d

extern uint32_t ADCDataLen;

//extern volatile uint32_t bNetWoking;//�����Ƿ�����
extern volatile uint32_t bNewFrame;//�µ�һ֡����
extern volatile uint32_t bNewADCData;//�Ƿ��������ݵ���
extern volatile uint32_t bRxFrame;
extern volatile uint32_t waitConfirmCommand;
#endif
