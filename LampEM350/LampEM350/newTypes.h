#ifndef newTypes_h__
#define newTypes_h__

typedef union {
	struct
	{
		int count;
		int power;
	};
	unsigned char buf[8];
}_PulseCount;

typedef union {
	int light;
	unsigned char buf[4];
}_Light;


#endif // newTypes_h__
