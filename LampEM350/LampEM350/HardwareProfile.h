#ifndef HardwareProfile_h__
#define HardwareProfile_h__
/************************************************************************/
/* ȫ��ͷ�ļ�                                                                     */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <errno.h>   
#include <limits.h> 
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include  <ctype.h>
#include <string.h>
#include "newTypes.h"
/************************************************************************/
/* ϵͳ�ַ���                                                           */
/************************************************************************/
#define INIPath "LampConfig.ini"

#define SYSLOG "SystemLog.txt"

/************************************************************************/
/* ȫ�ֱ�������                                                         */
/************************************************************************/
extern char ServerIP[16];
extern int ServerPort;

extern time_t  timeStart;
extern time_t  timeUse;
/************************************************************************/
/* ȫ�ֺ�������                                                         */
/************************************************************************/
extern _PulseCount PulseCount;
int GetProfileString(const char *profile, const char *AppName, const char *KeyName, char *KeyVal);
void SysLogProc(const char *cStr);
/************************************************************************/
/* ��ȱ����                                                           */
/************************************************************************/
extern _PulseCount PulseCount;
void Init_watt_hour_meter(void);
void GetPulseCount(void);
void ResetPulseCount(void);
void StartCalcPower(unsigned int PowerDown, unsigned int PowerUp);
/************************************************************************/
/* �նȼ����                                                           */
/************************************************************************/
extern _Light curLight;
void Init_light_sensor(void);
void GetLight(void);
#endif // HardwareProfile_h__
