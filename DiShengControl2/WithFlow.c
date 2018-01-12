#include "HardwareProfile.h"
void __attribute__((__interrupt__,auto_psv)) _U2RXInterrupt(void)
{	
	unsigned char rx;
	_U2RXIF=0;
	while(U3STAbits.URXDA)
	{
		rx=(unsigned char)U2RXREG;
		ProcRx_CP1616_Master(rx);
	}	
}
void WithFlow_Query(void)
{
	if(CP1616_MasterWaitClientData()==0)
	{
		errFlags.bFlowMiss=1;
		return;
	}
}
