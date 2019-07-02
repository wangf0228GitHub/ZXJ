#ifndef __STDAFX_H__
#define __STDAFX_H__

#include <htc.h>
#define _XTAL_FREQ 4000000
#include "FlagDefine.h"
extern GFlags gFlags;
extern unsigned char WorkIndex;
#define WRITETIMER1(x) ((void)(TMR1H=((x)>>8),TMR1L=((x)&0xFF)))
#define EEPRomSize 4
const unsigned int WORKTIME[7]={65536-8750+88,65536-7500+88,65536-6250+88,65536-5000+88,65536-3750+88,65536-2500+88,65536-1250+88};

#define PWM RC1

#include "Key.h"


#endif
