#include "Variables.h"

volatile uint32_t gTempIndex;
volatile uint32_t gMEMDMA2;
volatile _A7128Work A7128Work;
volatile _NetWorkMode NetWorkMode;
volatile _gFlags gFlags;
volatile uint32_t TimeIndex;

_ADCData ADCData4TX1;//7680*4+480*6+60*90
_ADCData ADCData4TX2;
_ADCData* ADCData4TXBuf;
_ADCData* ADCData4SaveBuf;

volatile uint32_t bCalibrationNet;

_ADCDataTag ADCDataTag;

_SensorBAT SensorBAT;

_SensorSignIn SensorSignIn;




uint32_t ADCDataLen;
uint32_t ADCDataLen_Calibration;
//volatile uint32_t bNetWoking;//�����Ƿ�����
volatile uint32_t bNewFrame;//�µ�һ֡����
volatile uint32_t bNewADCData;//�Ƿ��������ݵ���

uint8_t huart1Rx;
//volatile uint32_t waitConfirmCommand;