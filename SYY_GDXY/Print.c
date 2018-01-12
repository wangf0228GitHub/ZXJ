#include "HardwareProfile.h"
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include <ctype.h>
void EX_ProcPrint(void)
{
	unsigned char key,x,i;
	unsigned int ix;	
	SetProgress(sID_Print,1,0);
	ConnectWifi();
	if(Wifi_ErrState!=WifiNoErr)
	{
		//gFlags.bEnterDlgJump=1;
		EnterDlgReNum=sID_Menu;
		ShowWifiErr();
		DisconnectWifi();
		return;
	}
	SetProgress(sID_Print,1,50);
	SendMearData();	
	if(Wifi_ErrState!=WifiNoErr)
	{
		//gFlags.bEnterDlgJump=1;
		EnterDlgReNum=sID_Menu;
		ShowWifiErr();
		return;
	}	
	DisconnectWifi();
	//SetProgress(17,1,100);
	//gFlags.bEnterDlgJump=1;
	gFlags.bPrinted=1;
	EnterDlgReNum=sID_Menu;
	ShowEnterDlg(strPrintSeccess);
}
