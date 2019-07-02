#ifndef   __FlagDefine_h__
#define   __FlagDefine_h__
/************************************************************************/
/* 第一个为最低位                                                       */
/************************************************************************/
typedef union   
{
	struct
	{
		unsigned bWork:1;
		unsigned bKey:1;
		unsigned b0Delay:1;
	}Bits;
	unsigned char AllFlag;
} GFlags;        // general flags

#endif
