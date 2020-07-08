#ifndef   __A7128_h__
#define   __A7128_h__

#include "HardwareProfile.h"
#include "A7128reg.h"

/************************************************************************/
/* ����֡��ʽ����                                                       */
/************************************************************************/
#define pTargetIDIndex 1
#define pSourceIDIndex 2
#define pCommandIndex	 3
#define pLenIndex		 4
#define pFrameNumIndex 4
#define pBATIndex		 4
#define pDataIndex	 5
/************************************************************************/
/* �豸��ַ����                                                         */
/************************************************************************/
#define MasterAddr	0xf3
#define BroadcastAddr	0xfe

/************************************************************************/
/* ֡�����                                                           */
/************************************************************************/
//�㲥ָ��
#define WakeUpCommand		0x01 //����
#define StartNetCommand	0x02 //�ɼ���������
#define StopNetCommand	0x03 //�ɼ�����ֹͣ
#define FrameSyncCommand	0x04 //֡ͬ��
#define AbnormalAddrListCommand	0x05 //�쳣��ַ����
//�ʴ�ָ��
#define SignInCommand 0x10 //������ǩ����������Ϊ��ص���
#define DataResendCommand 0x11 //�����ش��ɼ����ݣ�����������Ϊ1������Ϊ�����ش���֡��
#define ADCDataSendCommand 0x20 //���߽ڵ������ϴ��������������ֽ�����תΪ����֡�ţ����������ȹ̶�Ϊ60���ֽ�
#define ADCDataSendCommand_BAT 0x21 //���߽ڵ����һ֡�����ϴ���֡�ſ��ɵ�ַ���ɼ������֡�����������������ֽڣ�Ϊ��ص��������������ȹ̶�Ϊ60���ֽ�
#define ADCDataSendCommand_Calibration 0x22//���ڱ궨��ADC����
//����ָ��
#define SetIDCommand 0xf0 //�趨�ڵ�ID
#define SetCalibrationCommand 0xf1 //�趨�궨����
#define GetCalibrationCommand 0xf2 //��ñ궨����

// #define A7128_SCK_Low() HAL_GPIO_WritePin(A7128_SCK_GPIO_Port,A7128_SCK_Pin,GPIO_PIN_RESET)
// #define A7128_SCK_High() HAL_GPIO_WritePin(A7128_SCK_GPIO_Port,A7128_SCK_Pin,GPIO_PIN_SET)
// 
// #define A7128_SDIO_Low() HAL_GPIO_WritePin(A7128_SDIO_GPIO_Port,A7128_SDIO_Pin,GPIO_PIN_RESET)
// #define A7128_SDIO_High() HAL_GPIO_WritePin(A7128_SDIO_GPIO_Port,A7128_SDIO_Pin,GPIO_PIN_SET)
// 
// #define A7128_SDIO_Read() HAL_GPIO_ReadPin(A7128_SDIO_GPIO_Port,A7128_SDIO_Pin)
//
// #define A7128_GIO2_Read() HAL_GPIO_ReadPin(A7128_GIO2_GPIO_Port,A7128_GIO2_Pin)
// 
// #define A7128_SDIO_OUT() GPIO_InitTypeDef GPIO_InitStruct_Out;  \
// 	GPIO_InitStruct_Out.Pin = A7128_SDIO_Pin;  \
// 	GPIO_InitStruct_Out.Mode = GPIO_MODE_OUTPUT_PP;  \
// 	GPIO_InitStruct_Out.Pull = GPIO_PULLUP;  \
// 	GPIO_InitStruct_Out.Speed = GPIO_SPEED_FREQ_LOW;  \
// 	HAL_GPIO_Init(A7128_SDIO_GPIO_Port, &GPIO_InitStruct_Out);	
// 
// #define A7128_SDIO_IN() GPIO_InitTypeDef GPIO_InitStruct_In;  \
// 	GPIO_InitStruct_In.Pin = A7128_SDIO_Pin;  \
// 	GPIO_InitStruct_In.Mode = GPIO_MODE_INPUT;  \
// 	GPIO_InitStruct_In.Pull = GPIO_PULLUP;  \
// 	HAL_GPIO_Init(A7128_SDIO_GPIO_Port, &GPIO_InitStruct_In);


extern volatile uint8_t A7128_TxFIFO[65];
extern volatile uint8_t A7128_RxFIFO[65];

void A7128_Init(void);
void A7128_StrobeCmd(uint8_t cmd);
void A7128_SetCH(uint8_t ch);
void A7128_WriteFIFO(void);
void A7128_WriteFIFO_DMA(void);
void A7128_WriteFIFO_DMA_ADC(uint8_t* pBuf);
void A7128_WriteID(void);
void A7128_ReadID(void);
void A7128_RxPacket(void);
void A7128_RxPacket_DMA(void);
void A7128_WriteReg(uint8_t  addr, uint8_t dataByte);
uint8_t A7128_ReadReg(uint8_t addr);
void A7128_WOREnable(void);
#endif
