#ifndef   __FlagDefine_h__
#define   __FlagDefine_h__
#include <stdint.h>
/************************************************************************/
/* ��һ��Ϊ���λ                                                       */
/************************************************************************/
typedef union   
{
	struct
	{
		unsigned bPause:1;
		unsigned bOldAutoMode:1;//0��ɨ��1��ɨ
	};
	uint8_t AllFlag;
} GFlags;        // general flags

#define RomCount 3
typedef union   
{
	struct
	{
		uint8_t sum;//У���
		uint16_t AD0; 	
	};
	uint8_t All[RomCount];
} _RomParams;        // general flags
#endif
