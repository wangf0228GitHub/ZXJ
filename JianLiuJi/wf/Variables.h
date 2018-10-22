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

extern const unsigned char gImage_NumNull[1518];
extern const unsigned char gImage_NumSign[1518];
extern const unsigned char gImage_TextBox[14190];
extern const unsigned char gImage_OverRange[7590];

extern const unsigned char gImage_Num0[1518];
extern const unsigned char gImage_Num1[1518];
extern const unsigned char gImage_Num2[1518];
extern const unsigned char gImage_Num3[1518];
extern const unsigned char gImage_Num4[1518];
extern const unsigned char gImage_Num5[1518];
extern const unsigned char gImage_Num6[1518];
extern const unsigned char gImage_Num7[1518];
extern const unsigned char gImage_Num8[1518];
extern const unsigned char gImage_Num9[1518];

extern const unsigned char gImage_NumP0[1518];
extern const unsigned char gImage_NumP1[1518];
extern const unsigned char gImage_NumP2[1518];
extern const unsigned char gImage_NumP3[1518];
extern const unsigned char gImage_NumP4[1518];
extern const unsigned char gImage_NumP5[1518];
extern const unsigned char gImage_NumP6[1518];
extern const unsigned char gImage_NumP7[1518];
extern const unsigned char gImage_NumP8[1518];
extern const unsigned char gImage_NumP9[1518];

extern const unsigned char gImage_pic[307200];
#endif
