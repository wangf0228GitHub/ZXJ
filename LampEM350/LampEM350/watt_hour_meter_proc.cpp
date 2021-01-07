#include "HardwareProfile.h"
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#define watt_hour_meter_file "/dev/watt_hour_meter"
int file_watt_hour_meter;

_PulseCount PulseCount;

struct _powerlimit {
	unsigned int PowerUp;
	unsigned int PowerDown;
};
_powerlimit powerlimit;
#define ioctlcmd_resetpulse	(_IO('w', 0x1))	/* 关闭定时器 */
#define ioctlcmd_CalcPower	(_IOW('w', 0x2,struct _powerlimit))	/* 打开定时器 */
void GetPulseCount(void)
{
	read(file_watt_hour_meter, PulseCount.buf, 8);
	printf("read pulse count : %d,%d\r\n", PulseCount.count,PulseCount.power);
}
/*
* SIGIO信号处理函数
* @param - signum 	: 信号值
* @return 			: 无
*/
static void watt_hour_meter_signal_func(int signum)
{
	GetPulseCount();
}
void Init_watt_hour_meter(void)
{
	int flags = 0;
	file_watt_hour_meter= open(watt_hour_meter_file, O_RDWR);
	if (file_watt_hour_meter < 0) {
		printf("Can't open file %s\r\n", watt_hour_meter_file);
	}
	GetPulseCount();
	/* 设置信号SIGIO的处理函数 */
	signal(SIGIO, watt_hour_meter_signal_func);
	fcntl(file_watt_hour_meter, F_SETOWN, getpid());		/* 设置当前进程接收SIGIO信号 	*/
	flags = fcntl(file_watt_hour_meter, F_GETFL);			/* 获取当前的进程状态 			*/
	fcntl(file_watt_hour_meter, F_SETFL, flags | FASYNC);	/* 设置进程启用异步通知功能 	*/
}

void ResetPulseCount(void)
{
	ioctl(file_watt_hour_meter, ioctlcmd_resetpulse, 0);
}
void StartCalcPower(unsigned int PowerDown,unsigned int PowerUp)
{
	powerlimit.PowerUp = PowerUp;
	powerlimit.PowerDown = PowerDown;
	ioctl(file_watt_hour_meter, ioctlcmd_CalcPower, (unsigned long)(&powerlimit));
}