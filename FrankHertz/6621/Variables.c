#include "Variables.h"
volatile GFlags gFlags;
_RomParams RomParams;
volatile uint8_t gTemp1;
volatile uint8_t gTemp2;
volatile uint16_t SystemTick;
volatile uint16_t ManualMeasTick;
volatile uint16_t NoWithPCRxTick;
volatile uint16_t RPValue;//��λ�����ڵ�ѹ
volatile uint16_t IValue;//���ӹܵ���
volatile uint16_t Nms;//ms����