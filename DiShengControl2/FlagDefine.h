#ifndef   __FlagDefine_h__
#define   __FlagDefine_h__
/************************************************************************/
/* 第一个为最低位                                                       */
/************************************************************************/
typedef union   
{
	struct
	{
		unsigned bNet:1;
	};
	unsigned int AllFlag;
} GFlags;        // general flags
typedef union   
{
	struct
	{
		
	};
	unsigned int AllFlag;
} ErrFlags;        // general flags

#endif
