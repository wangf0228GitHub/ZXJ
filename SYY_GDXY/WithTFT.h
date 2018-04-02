#ifndef __WithTFT_H__
#define __WithTFT_H__

#define NOTIFY_TOUCH_PRESS      0X01   //触摸屏按下通知
#define NOTIFY_TOUCH_RELEASE  0X03  //触摸屏松开通知
#define NOTIFY_WRITE_FLASH_OK  0X0C  //写FLASH成功
#define NOTIFY_WRITE_FLASH_FAILD  0X0D  //写FLASH失败
#define NOTIFY_READ_FLASH_OK  0X0B  //读FLASH成功
#define NOTIFY_READ_FLASH_FAILD  0X0F  //读FLASH失败
#define NOTIFY_MENU                        0X14  //菜单事件通知
#define NOTIFY_TIMER                       0X43  //定时器超时通知
#define NOTIFY_CONTROL                0XB1  //控件更新通知
#define NOTIFY_SCREEN                   0XB2  //画面切换通知

enum CtrlType
{
	kCtrlUnknown=0x0,
	kCtrlButton=0x10,  //按钮
	kCtrlText,  //文本
	kCtrlProgress,  //进度条
	kCtrlSlider,    //滑动条
	kCtrlMeter,  //仪表
	kCtrlDropList, //下拉列表
	kCtrlAnimation, //动画
	kCtrlRTC, //时间显示
	kCtrlGraph, //曲线图控件
	kCtrlTable, //表格控件
	kCtrlMenu,//菜单控件
	kCtrlSelector,//选择控件
	kCtrlQRCode,//二维码
};
#define MAXWithTFTRX 100
typedef union
{
	struct
	{		
		unsigned char  cmd_head;  //帧头
		unsigned char  cmd_type;  //命令类型(UPDATE_CONTROL)	
		unsigned char  ctrl_msg;   //CtrlMsgType-指示消息的类型
		uint   screen_id;  //产生消息的画面ID
		uint   control_id;  //产生消息的控件ID
		unsigned char    control_type; //控件类型
		unsigned char    data[MAXWithTFTRX-8];
	};
	unsigned char All[MAXWithTFTRX];
}_TFTMsg;
_TFTMsg TFTMsg;
typedef union   
{
	struct
	{		
		unsigned bWithTFTRx:1;
		unsigned bLen:1;
	};
	unsigned char AllFlag;
} _TFTFlags;        // general flags
_TFTFlags TFTFlags;

uint WithTFTRxLen;
unsigned int WithTFTRxCount;
unsigned int WithTFTNeedRxCount;

void InitWithTFT(void);
void EndProcCommandFromTFT(void);
void ProcRxFromTFT(unsigned char rx);
void ProcCommandFromTFT_Main(void);


void SetTxt(unsigned char sID,unsigned char cID,const char* data);
void GetTxt(unsigned char sID,unsigned char cID);
void SetChar(unsigned char sID,unsigned char cID,char data);
void SetTextFlash(unsigned char sID,unsigned char cID,unsigned int time);
void SetButton(unsigned char sID,unsigned char cID,unsigned char status);
void SetScreen(unsigned char sID);
void SetProgress(unsigned char sID,unsigned char cID,unsigned char status);
void DeleteCurve(unsigned char sID,unsigned char cID,unsigned char n);
void AddCurveData(unsigned char sID,unsigned char cID,unsigned char channel,unsigned int data);
void SetCurveVerticalScaling(unsigned char sID,unsigned char cID,unsigned int XScaling,unsigned int YScaling);
void ShowEnterDlg(const char *content);
unsigned char WithTFT_GetTxt(unsigned char sID,unsigned char cID,char* pBuf);
void ShowPic(unsigned char picID,unsigned int x,unsigned int y,unsigned int weight,unsigned int high);
void ShowQueryDlg(const char *content);
#endif
