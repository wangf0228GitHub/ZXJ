#ifndef   __FlagDefine_h__
#define   __FlagDefine_h__
/************************************************************************/
/* 第一个为最低位                                                       */
/************************************************************************/
typedef union   
{
	struct
	{
		unsigned bFastMode:1;
		unsigned bTB:1;
	};
	unsigned char AllFlag;
} GFlags;        // general flags


typedef union   
{
 	struct
 	{
		unsigned bNeedCalcH:1;
		unsigned bNeedGetWifiSet:1;
		unsigned bNeedGetParamSet:1; 
		unsigned bNeedGethCur:1;
		unsigned bNeedGetFACur:1;
		unsigned bNeedGetWorkType:1;
 	};
 	unsigned char AllFlag;
} _GetTxtFlags;        // general flags

typedef union   
{
	struct
	{
		unsigned bFAAuto:1;
		unsigned bFAPrint:1;
		unsigned bGQAuto:1;
		unsigned bGQPrint:1;
		unsigned bPLKPrint:1;
	};
	unsigned char AllFlag;
} _exWorkTepy;        // general flags

#define RomCount 185
typedef union   
{
	struct
	{
		unsigned char sum;//校验和
		unsigned char hWorkCurrent[6];
		float hCorrection[6];
		unsigned char FAWorkCurrent[6];
		float FACorrection[6];
		_exWorkTepy exWorkTepy;
		char SitNum[10];
		char ServerIP[17];
		char ServerPort[8];
		char WifiSSID[50];
		char WifiPASS[50];		
	};
	unsigned char All[RomCount];
} _RomParams;        // general flags
#endif
