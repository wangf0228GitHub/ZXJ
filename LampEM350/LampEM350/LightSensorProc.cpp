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
* SIGIO�źŴ�����
* @param - signum 	: �ź�ֵ
* @return 			: ��
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
	//�����źż�
	sigemptyset(&light_sigaction.sa_mask);
	sigaddset(&light_sigaction.sa_mask, SIGIO);


	//���� SIGIO ��Ӧ���źŴ�����
	light_sigaction.sa_sigaction = light_sensor_signal_func;
	//��sa_flags���� SA_SIGINFO ��־ʱ��ϵͳʹ��sa_sigaction������Ϊ�źŴ�����������ʹ��sa_handler.
	light_sigaction.sa_flags = SA_SIGINFO;
	if (sigaction(SIGIO, &light_sigaction, NULL) < 0) {
		printf("install SIGIO sigaction error");
	}
	file_light_sensor = open(light_sensor_file, O_RDWR);
	if (file_light_sensor < 0) {
		printf("Can't open file %s\r\n", light_sensor_file);
	}
	GetLight();
	/* �����ź�SIGIO�Ĵ����� */
	//signal(SIGIO, light_sensor_signal_func);
	fcntl(file_light_sensor, F_SETOWN, getpid());		/* ���õ�ǰ���̽���SIGIO�ź� 	*/
	flags = fcntl(file_light_sensor, F_GETFL);			/* ��ȡ��ǰ�Ľ���״̬ 			*/
	fcntl(file_light_sensor, F_SETFL, flags | FASYNC);	/* ���ý��������첽֪ͨ���� 	*/

	fcntl(file_light_sensor, F_SETSIG, SIGIO);
}
