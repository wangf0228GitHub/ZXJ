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
		unsigned bPause:1;
		unsigned bOldAutoMode:1;//0慢扫，1快扫
	};
	uint8_t AllFlag;
} GFlags;        // general flags

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
