#include "HardwareProfile.h"
void SysLogProc(const char *cStr)
{
	int iFd;
	iFd = open(SYSLOG, O_APPEND | O_RDWR | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(iFd, cStr, strlen(cStr));
	close(iFd);
}