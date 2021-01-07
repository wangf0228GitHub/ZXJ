#include "HardwareProfile.h"
#include <stdio.h>
void InitSystem(void);
int main(int argc, char *argv[])
{
	int i = 0;
	InitSystem();
	StartCalcPower(1000, 2000);
	while (1)
	{
		//GetPulseCount();
		sleep(1);
// 		i++;
// 		if (i > 10)
// 		{
// 			i = 0;
// 			ResetPulseCount();
// 		}
	}

	printf("\r\nLampEM350 Normal Exit\r\n\r\n");
	return 0;
}