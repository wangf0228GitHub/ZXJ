#ifndef   __Variables_h__
#define   __Variables_h__

#include <stdint.h>
#include "FlagDefine.h"
extern volatile GFlags gFlags;
extern _RomParams RomParams;
extern volatile uint8_t gTemp1;
extern volatile uint8_t gTemp2;
extern volatile uint16_t SystemTick;
extern volatile uint16_t ManualMeasTick;
extern volatile uint16_t NoWithPCRxTick;
extern volatile uint16_t RPValue;//��λ�����ڵ�ѹ
extern volatile uint16_t IValue;//���ӹܵ���
extern volatile uint16_t Nms;//ms����
#endif

