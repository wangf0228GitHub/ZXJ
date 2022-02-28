#ifndef   __FlagDefine_h__
#define   __FlagDefine_h__
#include <stdint.h>
/************************************************************************/
/* 第一个为最低位                                                       */
/************************************************************************/
typedef union   
{
	struct
	{		
		unsigned bSetIc : 1;
		unsigned bSetIf : 1;
		unsigned bSetU : 1;

		unsigned bSetIc_Show : 1;
		unsigned bSetIf_Show : 1;
		unsigned bSetU_Show : 1;
	};
	uint8_t AllFlag;
} _gFlags;        // general flags


typedef union
{
	struct
	{
		unsigned bCW1 : 1;
		unsigned bCCW1 : 1;
		unsigned bCW2 : 1;
		unsigned bCCW2 : 1;
		unsigned bCW3 : 1;
		unsigned bCCW3 : 1;
	};
	uint8_t AllFlag;
} _KnobFlags;        // general flags
#define RomCount 3
typedef union   
{
	struct
	{
		uint8_t sum;//校验和
		uint16_t AD0; 	
	};
	uint8_t All[RomCount];
} _RomParams;        // general flags
#endif
