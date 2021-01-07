#include "HardwareProfile.h"

void InitGPIO()
{
	
}

void InitVariable(void)
{
	char temp[50];
	if (GetProfileString(INIPath, "System", "ServerIP", ServerIP) == -1)
	{
		perror("LampConfig.ini is error");
		exit(1);
	}
	if (GetProfileString(INIPath,"System", "ServerPort", temp) == -1)
	{
		perror("LampConfig.ini is error");
		exit(1);
	}
	sscanf(temp, "%d", &ServerPort);
	/************************************************************************/
	/* 初始化信息打印                                                       */
	/************************************************************************/
	printf("Server Info: %s:%d\r\n", ServerIP, ServerPort);
}
void InitSystem(void)
{
	char    cStr[150];
 	InitGPIO();
// 	DS12C887_Init();
 	InitVariable();
	Init_watt_hour_meter();
	Init_light_sensor();
// 	SS5060_Init();
// 	SS5060_Setting(0x01);//启动光照传感器  
// 	WithZigBee_Init();
// 	DS12C887_GetTime();
// 	//SS5060_Setting(0x10);//continuously high resolution mode

	SysLogProc("\n\n********************************************* \n\n");
	time(&timeStart);
	sprintf(cStr, "start time: %s \n", asctime(gmtime(&timeStart)));
	SysLogProc(cStr);
}