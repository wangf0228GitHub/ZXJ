#include "HardwareProfile.h"
#include "string.h"
#include "stdio.h"
#include <ctype.h>
#include "stdlib.h"
void InitWifi(void)
{
	Wifi_ErrState=WifiNoErr;
	if(ATCommand_SendCmd("AT\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissAT;
		return;
	}
	if(ATCommand_SendCmd("AT+CWMODE=1\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWMODE;
		return;
	}
	if(ATCommand_SendCmd("AT+CWQAP\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWQAP;
		return;
	}
	if(ATCommand_SendCmd("AT+CWAUTOCONN=0\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWQAP;
		return;
	}
}
void DisconnectWifi(void)
{
	Wifi_ErrState=WifiNoErr;
	if(ATCommand_SendCmd("AT+CWQAP\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWQAP;
		return;
	}	
}
void ConnectWifi(void)
{
	unsigned char retry,i;
	char *strx=0;
	unsigned char res=0;
	Wifi_ErrState=WifiNoErr;
	if(ATCommand_SendCmd("AT\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissAT;
		return;
	}	
	if(ATCommand_SendCmd("AT+CWQAP\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWQAP;
		return;
	}
	ATCommand_PutString("AT+CWJAP=\"\0");
	ATCommand_PutString(RomParams.WifiSSID);
	ATCommand_PutString("\",\"\0");
	ATCommand_PutString(RomParams.WifiPASS);
	ATCommand_PutString("\"\r\n\0");
	ATCommand_WaitACKTimes=400;
	strcpy(ATCommand_ErrString,"FAIL");
	res=ATCommand_WaitData();
	if(res!=ATACK_OK)
	{
		Wifi_ErrState=MissWifi;
		return;
	}	
}
void StartSetWifi(unsigned char type)
{
	unsigned char retry,i;
	char *strx=0;
	Wifi_ErrState=WifiNoErr;
 	if(ATCommand_SendCmd("AT\0")!=ATACK_OK)
 	{
 		Wifi_ErrState=MissAT;
 		return;
 	}
	if(ATCommand_SendCmd("AT+CWQAP\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWQAP;
		return;
	}
	if(type==1)//apk
	{
		if(ATCommand_SendCmd("AT+CWSMARTSTART=1\0")!=ATACK_OK)
		{
			Wifi_ErrState=MissCWSMARTSTART;
			return;
		}	
	}
	else//微信
	{
		if(ATCommand_SendCmd("AT+CWSMARTSTART=2\0")!=ATACK_OK)
		{
			Wifi_ErrState=MissCWSMARTSTART;
			return;
		}	
	}
}
void StopSetWifi(void)
{
	unsigned char retry,i;
	char *strx=0;
	Wifi_ErrState=WifiNoErr;
	if(ATCommand_SendCmd("AT+CWSMARTSTOP\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWSMARTSTOP;
		return;
	}	
	if(ATCommand_SendCmd("AT+CWQAP\0")!=ATACK_OK)
	{
		Wifi_ErrState=MissCWQAP;
		return;
	}
}

void SendMearData(void)
{
	unsigned char res=0; 
	unsigned char i,j,n;
	char tx[50];
	unsigned int len;
	char* pStr1;
	char* pStr2;
	char* pStr3;
	Wifi_ErrState=WifiNoErr;
	sprintf(tx,"AT+CIPSTART=\"TCP\",\"%s\",%s\0",RomParams.ServerIP,RomParams.ServerPort);
	if(ATCommand_SendCmd(tx)!=ATACK_OK)
	{
		Wifi_ErrState=MissServer;
		return;
	}
	/************************************************************************/
	/* 调试用，初始化模拟数据                                               */
	/************************************************************************/
// 	RomParams.exWorkTepy.bFAAuto=1;
// 	RomParams.exWorkTepy.bFAPrint=1;
// 	RomParams.exWorkTepy.bGQAuto=1;
// 	RomParams.exWorkTepy.bGQPrint=0;
// 	RomParams.exWorkTepy.bPLKPrint=0;
// 	for(i=0;i<6;i++)
// 	{
// 		Curve1Flags[i]=1;
// 		for(j=0;j<101;j++)
// 			CurveData_FATX[i][j]=j+i;
// 		fUs[i]=i+0.05;
// 		ManVAIndex[i]=i*2+10;
// 	}
// 	for(i=0;i<4;i++)
// 	{
// 		Curve2Flags[i]=1;
// 		for(j=0;j<101;j++)
// 			CurveData_GDLGQ[i][j]=j+i;
// 		ManGQIndex[i]=i*i+5;
// 	}
// 	fUs[0]=1.414;
// 	fUs[1]=1.039;
// 	fUs[2]=0.750;
// 	fUs[3]=0.472;
// 	fUs[4]=0.400;
// 	fUs[5]=0.341;
// 	fH_K=0.386;
// 	fH_B=-1.522;
// 	fH=6.184;
	/************************************************************************/
	/* 第1帧：@01,座位号|班级|学号|实验设定$                                 */
	/************************************************************************/
	strcpy(ATCommand_OkString,">");
	len=10;
	len+=strlen(RomParams.SitNum);
	len+=strlen(StudentClass);
	len+=strlen(StudentNum);
	sprintf(tx,"AT+CIPSEND=%d\0",len);
	if(ATCommand_SendCmd(tx)!=ATACK_OK)
	{
		Wifi_ErrState=MissCIPSEND;
		return;
	}	
	ATCommand_PutString("@01,");
	ATCommand_PutString(RomParams.SitNum);
	ATCommand_TxByte('|');
	ATCommand_PutString(StudentClass);
	ATCommand_TxByte('|');
	ATCommand_PutString(StudentNum);
	ATCommand_TxByte('|');
	sprintf(DisplayLine,"%02d",RomParams.exWorkTepy.AllFlag);
	ATCommand_PutString(DisplayLine);
	ATCommand_TxByte('$');
	strcpy(ATCommand_OkString,"SEND OK");
	res=ATCommand_WaitData();
	if(res!=ATACK_OK)
	{
		Wifi_ErrState=SendTimeOut;
		return;
	}
	ATCommand_WaitACKTimes=600;
	strcpy(ATCommand_OkString,"+IPD,7:@01,OK$");
	res=ATCommand_WaitData();
	if(res!=ATACK_OK)
	{
		Wifi_ErrState=ServerACKTimeOut;
		return;
	}
	SetProgress(sID_Print,1,54);	
	/************************************************************************/
	/* VA数据帧:02~07:@n,count,00000|00000|....$                            */
	/************************************************************************/
	if(RomParams.exWorkTepy.bFAPrint)
	{
		for(n=0;n<6;n++)
		{
			strcpy(ATCommand_OkString,">");
			if(RomParams.exWorkTepy.bFAAuto)
			{	
				if(Curve1Flags[n]==0)
					continue;
				if(ATCommand_SendCmd("AT+CIPSEND=614\0")!=ATACK_OK)
				{
					Wifi_ErrState=MissCIPSEND;
					return;
				}
				ATCommand_TxByte('@');
				ATCommand_TxByte('0');
				ATCommand_TxByte(n+2+'0');
				ATCommand_PutString(",101,\0");
				for(i=0;i<100;i++)
				{
					//CurveData_FATX[n-2][i]=i+n*100;
					sprintf(tx,"%05d|\0",CurveData_FATX[n][i]);
					ATCommand_PutString(tx);
				}
				//CurveData_FATX[n-2][99]=99+n*100;
				sprintf(tx,"%05d\0",CurveData_FATX[n][100]);
				ATCommand_PutString(tx);
				ATCommand_TxByte('$');
			}
			else
			{
				if(ManVAIndex[n]==0xff)
					continue;
				sprintf(tx,"AT+CIPSEND=%d\0",13+ManVAIndex[n]*6);
				if(ATCommand_SendCmd(tx)!=ATACK_OK)
				{
					Wifi_ErrState=MissCIPSEND;
					return;
				}
				ATCommand_TxByte('@');
				ATCommand_TxByte(n+2+'0');
				ATCommand_TxByte(',');
				sprintf(tx,"%03d,\0",ManVAIndex[n]+1);
				ATCommand_PutString(tx);
				for(i=0;i<ManVAIndex[n];i++)
				{
					//CurveData_FATX[n-2][i]=i+n*100;
					sprintf(tx,"%05d|\0",CurveData_FATX[n][i]);
					ATCommand_PutString(tx);
				}
				//CurveData_FATX[n-2][99]=99+n*100;
				sprintf(tx,"%05d\0",CurveData_FATX[n][ManVAIndex[n]]);
				ATCommand_PutString(tx);
				ATCommand_TxByte('$');
			}
			strcpy(ATCommand_OkString,"SEND OK");
			res=ATCommand_WaitData();
			if(res!=ATACK_OK)
			{
				Wifi_ErrState=SendTimeOut;
				return;
			}
			ATCommand_WaitACKTimes=600;
			sprintf(tx,"+IPD,7:@%02d,OK$",n+2);
			strcpy(ATCommand_OkString,tx);
			res=ATCommand_WaitData();
			if(res!=ATACK_OK)
			{
				Wifi_ErrState=ServerACKTimeOut;
				return;
			}
			SetProgress(sID_Print,1,54+4*n);
		}
	}
	SetProgress(sID_Print,1,74);	
	/************************************************************************/
	/* GQ数据帧:08~11:@n,count,00000|00000|....$                             */
	/************************************************************************/
	if(RomParams.exWorkTepy.bGQPrint)
	{
		for(n=0;n<4;n++)
		{			
			strcpy(ATCommand_OkString,">");
			if(RomParams.exWorkTepy.bGQAuto)
			{	
				if(Curve2Flags[n]==0)
					continue;
				if(ATCommand_SendCmd("AT+CIPSEND=614\0")!=ATACK_OK)
				{
					Wifi_ErrState=MissCIPSEND;
					return;
				}
				sprintf(tx,"@%02d,101,\0",n+8);
				ATCommand_PutString(tx);
				for(i=0;i<100;i++)
				{
					//CurveData_FATX[n-2][i]=i+n*100;
					sprintf(tx,"%05d|\0",CurveData_GDLGQ[n][i]);
					ATCommand_PutString(tx);
				}
				//CurveData_FATX[n-2][99]=99+n*100;
				sprintf(tx,"%05d\0",CurveData_GDLGQ[n][100]);
				ATCommand_PutString(tx);
				ATCommand_TxByte('$');
			}
			else
			{
				if(ManGQIndex[n]==0xff)
					continue;
				sprintf(tx,"AT+CIPSEND=%d\0",14+ManGQIndex[n]*6);
				if(ATCommand_SendCmd(tx)!=ATACK_OK)
				{
					Wifi_ErrState=MissCIPSEND;
					return;
				}
				sprintf(tx,"@%02d,%03d,\0",n+8,ManGQIndex[n]+1);
				ATCommand_PutString(tx);
				for(i=0;i<ManGQIndex[n];i++)
				{
					//CurveData_FATX[n-2][i]=i+n*100;
					sprintf(tx,"%05d|\0",CurveData_GDLGQ[n][i]);
					ATCommand_PutString(tx);
				}
				//CurveData_FATX[n-2][99]=99+n*100;
				sprintf(tx,"%05d\0",CurveData_GDLGQ[n][ManGQIndex[n]]);
				ATCommand_PutString(tx);
				ATCommand_TxByte('$');
			}
			strcpy(ATCommand_OkString,"SEND OK");
			res=ATCommand_WaitData();
			if(res!=ATACK_OK)
			{
				Wifi_ErrState=SendTimeOut;
				return;
			}
			ATCommand_WaitACKTimes=600;
			sprintf(tx,"+IPD,7:@%02d,OK$",n+8);
			strcpy(ATCommand_OkString,tx);
			res=ATCommand_WaitData();
			if(res!=ATACK_OK)
			{
				Wifi_ErrState=ServerACKTimeOut;
				return;
			}
			SetProgress(sID_Print,1,78+4*n);
		}
	}
	SetProgress(sID_Print,1,94);	
	/************************************************************************/
	/* PLK数据帧:12:@12,0.000|0.000|....$                             */
	/************************************************************************/
	if(RomParams.exWorkTepy.bPLKPrint && bCalcH!=0)
	{
		strcpy(ATCommand_OkString,">");
		if(ATCommand_SendCmd("AT+CIPSEND=60\0")!=ATACK_OK)
		{
			Wifi_ErrState=MissCIPSEND;
			return;
		}
		ATCommand_PutString("@12,\0");
		for(i=0;i<6;i++)
		{
			//CurveData_FATX[n-2][i]=i+n*100;
			sprintf(tx,"%.3f|\0",fUs[i]);
			ATCommand_PutString(tx);
		}
		//CurveData_FATX[n-2][99]=99+n*100;
		sprintf(tx,"%+.3f|\0",fH_K);
		ATCommand_PutString(tx);
		sprintf(tx,"%+.3f|\0",fH_B);
		ATCommand_PutString(tx);
		sprintf(tx,"%.3f\0",fH);
		ATCommand_PutString(tx);
		ATCommand_TxByte('$');
		strcpy(ATCommand_OkString,"SEND OK");
		res=ATCommand_WaitData();
		if(res!=ATACK_OK)
		{
			Wifi_ErrState=SendTimeOut;
			return;
		}
		ATCommand_WaitACKTimes=600;
		sprintf(tx,"+IPD,7:@12,OK$");
		strcpy(ATCommand_OkString,tx);
		res=ATCommand_WaitData();
		if(res!=ATACK_OK)
		{
			Wifi_ErrState=ServerACKTimeOut;
			return;
		}
	}
	SetProgress(sID_Print,1,98);
	/************************************************************************/
	/* 第99帧为请求打印帧                                                  */
	/************************************************************************/
	strcpy(ATCommand_OkString,">");
	sprintf(tx,"AT+CIPSEND=7\0",len);
	if(ATCommand_SendCmd(tx)!=ATACK_OK)
	{
		Wifi_ErrState=MissCIPSEND;
		return;
	}
	ATCommand_PutString("@99,99$");	
	strcpy(ATCommand_OkString,"SEND OK");
	res=ATCommand_WaitData();
	if(res!=ATACK_OK)
	{
		Wifi_ErrState=SendTimeOut;
		return;
	}
	ATCommand_WaitACKTimes=600;
	strcpy(ATCommand_OkString,"+IPD,7:@99,OK$");
	res=ATCommand_WaitData();
	if(res!=ATACK_OK)
	{
		Wifi_ErrState=ServerACKTimeOut;
		return;
	}
	SetProgress(sID_Print,1,100);
// 	pStr1=strstr((const char*)ATCommand_RxList,"+IPD,");
// 	pStr2=strstr((const char*)pStr1,":#$");
// 	pStr3=strstr((const char*)pStr2,"$#");
// 	if(pStr1==0 || pStr2==0 || pStr3==0)
// 	{
// 		Wifi_ErrState=MissWifi;
// 		return;
// 	}
// 	len=pStr3-pStr2-3;
// 	sprintf(tx,"AT+CIPSEND=%d\0",len);
// 	if(ATCommand_SendCmd(tx)!=ATACK_OK)
// 	{
// 		Wifi_ErrState=MissAT;
// 	}
// 	for(i=0;i<len;i++)
// 		ATCommand_TxByte(*(pStr2+3+i));
// 	strcpy(ATCommand_OkString,"SEND OK");
// 	res=ATCommand_WaitData();
// 	if(res!=ATACK_OK)
// 		return;
}
void ShowWifiErr(void)
{
	switch(Wifi_ErrState)
	{
	case MissAT:
		ShowEnterDlg(strNo8266);
		break;
	case MissCWQAP:
		ShowEnterDlg("MissCWQAP");
		break;
	case MissCWSMARTSTART:
		ShowEnterDlg("MissCWSMARTSTART");
		break;
	case MissCWSMARTSTOP:
		ShowEnterDlg("MissCWSMARTSTOP");
		break;
	case MissCWMODE:
		ShowEnterDlg("MissCWMODE");
		break;
	case MissWifi:
		ShowEnterDlg(strNoWifi);
		break;
	case MissServer:
		ShowEnterDlg(strNoServer);
		break;
 	case MissCIPSEND:
 		ShowEnterDlg("MissCIPSEND");
 		break;
	case ServerACKTimeOut:
		ShowEnterDlg("ServerACKTimeOut");
		break;
	case SendTimeOut:
		ShowEnterDlg("SendTimeOut");
		break;
	}
}
