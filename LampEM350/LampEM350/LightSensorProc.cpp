#include "HardwareProfile.h"
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#define light_sensor_file "/dev/lightBH1750"
#define light_sensor_sysfs_curLight "BH1750_curLight"
int file_light_sensor;
_Light curLight;
void GetLight(void)
{
	char path[1024];
	int rslt = readlink(light_sensor_sysfs_curLight, path, 1023);
	path[rslt] = '\0';
	int fd= open(light_sensor_sysfs_curLight, O_RDONLY);
	ssize_t r=read(fd, curLight.buf, 4);
	read(file_light_sensor, curLight.buf, 4);
	printf("read light : %d\r\n", curLight.light);
}
/*
* SIGIO信号处理函数
* @param - signum 	: 信号值
* @return 			: 无
*/
// static void light_sensor_signal_func(int signum)
// {
// 	printf("SIGIO : %d\r\n", signum);
// 	//GetPulseCount();
// }

static void light_sensor_signal_func(int signum, siginfo_t *info, void *myact)
{
	if (signum != SIGIO)
	{
		printf("not SIGIO : %d\r\n", info->si_signo);
		return;
	}	
	//GetPulseCount();
	switch (info->si_code)
	{
	case POLL_IN:
		printf("light ok\n");
		break;
	case POLL_ERR:
		printf("light err\n");
		break;
	default:
		break;
	}
}
struct sigaction light_sigaction;
void Init_light_sensor(void)
{
	int flags = 0;
	//设置信号集
	sigemptyset(&light_sigaction.sa_mask);
	sigaddset(&light_sigaction.sa_mask, SIGIO);


	//设置 SIGIO 对应的信号处理函数
	light_sigaction.sa_sigaction = light_sensor_signal_func;
	//当sa_flags包含 SA_SIGINFO 标志时，系统使用sa_sigaction函数作为信号处理函数，否则使用sa_handler.
	light_sigaction.sa_flags = SA_SIGINFO;
	if (sigaction(SIGIO, &light_sigaction, NULL) < 0) {
		printf("install SIGIO sigaction error");
	}
	file_light_sensor = open(light_sensor_file, O_RDWR);
	if (file_light_sensor < 0) {
		printf("Can't open file %s\r\n", light_sensor_file);
	}
	GetLight();
	/* 设置信号SIGIO的处理函数 */
	//signal(SIGIO, light_sensor_signal_func);
	fcntl(file_light_sensor, F_SETOWN, getpid());		/* 设置当前进程接收SIGIO信号 	*/
	flags = fcntl(file_light_sensor, F_GETFL);			/* 获取当前的进程状态 			*/
	fcntl(file_light_sensor, F_SETFL, flags | FASYNC);	/* 设置进程启用异步通知功能 	*/

	fcntl(file_light_sensor, F_SETSIG, SIGIO);
}
