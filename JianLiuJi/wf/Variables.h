#ifndef   __Variables_h__
#define   __Variables_h__

#include <stdint.h>
#include "main.h"

#define SystemParamLen 10
typedef union
{	
	struct
	{
		uint32_t sum;
		//w5500ÍøÂç²ÎÊı:6
		float V0;
	};
	uint32_t all[SystemParamLen];
	uint8_t allByte[SystemParamLen<<2];
}_SystemParam;

extern _SystemParam SystemParam;
extern uint16_t oldLine[4];
extern uint16_t oldI;
extern const uint16_t ScalePoint[][4];
extern const uint16_t PX1[];
extern const uint16_t PY1[];
extern const uint16_t PX2[];
extern const uint16_t PY2[];

extern const uint16_t NX1[];
extern const uint16_t NY1[];
extern const uint16_t NX2[];
extern const uint16_t NY2[];

extern const unsigned char *NumList[10];
extern const unsigned char *NumPList[10];

extern const unsigned char gImage_NumNull[768];
extern const unsigned char gImage_NumSign[768];
extern const unsigned char gImage_TextBox[9112];


extern const unsigned char gImage_Num0[768];
extern const unsigned char gImage_Num1[768];
extern const unsigned char gImage_Num2[768];
extern const unsigned char gImage_Num3[768];
extern const unsigned char gImage_Num4[768];
extern const unsigned char gImage_Num5[768];
extern const unsigned char gImage_Num6[768];
extern const unsigned char gImage_Num7[768];
extern const unsigned char gImage_Num8[768];
extern const unsigned char gImage_Num9[768];

extern const unsigned char gImage_NumP0[768];
extern const unsigned char gImage_NumP1[768];
extern const unsigned char gImage_NumP2[768];
extern const unsigned char gImage_NumP3[768];
extern const unsigned char gImage_NumP4[768];
extern const unsigned char gImage_NumP5[768];
extern const unsigned char gImage_NumP6[768];
extern const unsigned char gImage_NumP7[768];
extern const unsigned char gImage_NumP8[768];
extern const unsigned char gImage_NumP9[768];

extern const unsigned char gImage_pic[153600];
#endif
