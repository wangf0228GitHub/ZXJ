#ifndef   __FlagDefine_h__
#define   __FlagDefine_h__
/************************************************************************/
/* ��һ��Ϊ���λ                                                       */
/************************************************************************/
typedef union   
{
	struct
	{
		unsigned bWork:1;
		unsigned bReKey:1;
		unsigned bPause : 1;
		unsigned bSecond : 1;
		unsigned bShow : 1;
		unsigned bHalfSecond : 1;
	}Bits;
	unsigned int AllFlag;
} GFlags;        // general flags
#endif
