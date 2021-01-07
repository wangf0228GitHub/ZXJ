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
	Net_Start_Calibration//��ǰΪ�궨����
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

extern volatile uint32_t bCalibrationNet;
extern volatile uint32_t bA7128Reseted;
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
		uint8_t addr;
		uint8_t fIndex;		
	};
	uint32_t all;
}_AbnormalFrame;
extern _AbnormalFrame AbnormalFrameList[115];
extern uint32_t AbnormalFrameCount;
extern uint32_t AbnormalFrameIndex;
extern uint32_t AbnormalAddrCount;
extern uint32_t AbnormalFrameErr;
extern uint8_t AbnormalAddr[60];
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



extern uint32_t ADCDataLen;
extern uint32_t ADCDataLen_Calibration;

//extern volatile uint32_t bNetWoking;//�����Ƿ�����
extern volatile uint32_t bNewFrame;//�µ�һ֡����
extern volatile uint32_t bNewADCData;//�Ƿ��������ݵ���

extern uint8_t huart1Rx;
//extern volatile uint32_t waitConfirmCommand;
#endif
