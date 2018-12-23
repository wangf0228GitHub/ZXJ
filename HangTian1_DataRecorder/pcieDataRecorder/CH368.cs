using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

using BOOL = System.Int32; 
using ULONG = System.UInt32;
using UCHAR = System.Byte; 
using HANDLE = System.IntPtr; 
using PVOID = System.IntPtr;
 
// using PUCHAR = System.Char[]; 
// using ULONG = System.UInt32;  
namespace pcieDataRecorder
{
	[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
	public struct _CH367_IO_REG
	{	                //CH367芯片的I/O空间寄存器
		[MarshalAs(UnmanagedType.ByValArray , SizeConst = 0xe8)]
        public UCHAR[] mCH367IoPort;                     //00H-E7H,共232字节为标准的I/O端口
        public UCHAR mCH367GPOR;	                        //E8H 通用输出寄存器
        public UCHAR mCH367GPVR;	                        //E9H 通用变量寄存器
        public UCHAR mCH367GPIR;	                        //EAH 通用输入寄存器
        public UCHAR mCH367IntCtr;	                        //EBH 中断控制寄存器
		[MarshalAs(UnmanagedType.ByValArray , SizeConst = 4)]
        public UCHAR[] mCH367IoBuf;
// 		union{
// 			UCHAR mCH367IoBuf8;                     //ECH 8位被动并行接口数据缓冲区
// 			ULONG mCH367IoBuf32;                    //ECH 32位被动并行接口数据缓冲区
// 		};
		[MarshalAs(UnmanagedType.ByValArray , SizeConst = 2)]
        public UCHAR[] mCH368MemAddr;

// 		union{
// 			USHORT mCH368MemAddr;                   //F0H 存储器接口: A15-A0地址设定寄存器 ??
// 			struct{
// 				UCHAR mCH368MemAddrL;               //F0H 存储器接口: A7-A0地址设定寄存器
// 				union{
// 					UCHAR mCH368MemAddrH;           //F1H 存储器接口: A15-A8地址设定寄存器
// 					UCHAR mCH367GPOR2;              //F1H 通用输出寄存器2 ??
// 				};
// 			}ASR;
// 		};
        public UCHAR mCH367IORESV2;                        //F2H
        public UCHAR mCH368MemData;                        //F3H 存储器接口: 存储器数据存取寄存器
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public UCHAR[] mCH367DataSta;
// 		union{
// 			UCHAR mCH367Data8Sta;                   //F4H D7-D0端口状态寄存器
// 			ULONG mCH367SData32Sta;                 //F4H D31-D0端口状态寄存器
// 		};
        public UCHAR mCH367Status;                         //F8H 杂项控制和状态寄存器
        public UCHAR mCH367IO_RESV3;                       //F9H
        public UCHAR mCH367Speed;                          //FAH 读写速度控制寄存器
        public UCHAR mCH367PDataCtrl;                      //FBH 被动并行接口控制寄存器
        public UCHAR mCH367IoTime;                         //FCH 硬件循环计数寄存器
        public UCHAR mCH367SPICtrl;                        //FDH SPI控制寄存器
        public UCHAR mCH367SPIData;                        //FEH SPI数据寄存器
        public UCHAR mCH367IO_RESV4;                       //FFH
	}
	[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
	public struct _CH368_MEM_REG 
	{				// CH367芯片的存储器空间
		[MarshalAs(UnmanagedType.ByValArray , SizeConst = 0x8000)]
		UCHAR[]	mCH368MemPort;		// 0000H-7FFFH,共32768字节为标准的存储器单元		
	}

	public class CH368
	{
        // WIN32应用层接口命令
/*public const ULONG		IOCTL_CH367_COMMAND		( FILE_DEVICE_UNKNOWN << 16 | FILE_ANY_ACCESS << 14 | 0x0f36 << 2 | METHOD_BUFFERED )	// 专用接口*/

//public const ULONG		mWIN32_COMMAND_HEAD		mOFFSET( mWIN32_COMMAND, mBuffer )	// WIN32命令接口的头长度

public const ULONG		mCH367_MAX_NUMBER	=	16;			// 最多同时连接的CH367数

public const ULONG mMAX_BUFFER_LENGTH = 0x8000;//Math.Max(System.Runtime.InteropServices.Marshal.SizeOf(_CH367_IO_REG), System.Runtime.InteropServices.Marshal.SizeOf(_CH368_MEM_REG));// 数据缓冲区最大长度

//public const ULONG		mMAX_COMMAND_LENGTH	=	( mWIN32_COMMAND_HEAD + mMAX_BUFFER_LENGTH )	;// 最大数据长度加上命令结构头的长度

public const ULONG		mCH368_MEM_BASE_AUTO	=0xffffffff 	;// 自动设定CH368的存储器基址

public const ULONG		mCH367_INT_LINE_AUTO=	0xffffffff		;		// 自动检测CH367的中断号

// 寄存器的位定义
//0xE8
public const ULONG		mBitI2cSdaOut           =0x01   ;     //设定SDA 引脚的输出值(1),1*:high,0:low
public const ULONG		mBitI2cSclOut           =0x02   ;     //设定SCL 引脚的输出值(1)
public const ULONG		mBitSpiScsOut           =0x04   ;     //设定SCS 引脚的输出值(1)
public const ULONG		mBitBeWakenEnable       =0x32  ;      //使能支持被强制唤醒(0)
public const ULONG		mBitSetSpiSdxDir        =0x64  ;      //设定SDX 引脚的数据方向(0)
//0xEA
public const ULONG		mBitSpiSdxOut           =0x01   ;     //输入SDA 引脚的状态(1)
public const ULONG		mBitIntStatus           =0x08     ;   //输入INT#引脚的状态(1)
public const ULONG		mBitRDStatus            =0x10  ;      //输入RD#引脚的状态(1)
public const ULONG		mBitWRStatus            =0x20   ;     //输入WR#引脚的状态(1)
public const ULONG		mBitAddrStatus          =0x40    ;    //输入ADDR 引脚的状态(1)
public const ULONG		mBitSdxStatus           =0x80     ;   //输入SDX 引脚的状态(1)
//0xEB
public const ULONG		mBitGlobalIntEnable     =0x02   ;     //全局中断使能(0)
public const ULONG		mBitIntPolarity         =0x04     ;   //INT#引脚中断输入的极性(0),0:低电平/上升沿;1:高电平/下降沿
public const ULONG		mBitIntInType           =0x08   ;     //INT#引脚中断输入的类型(0)
//0xF8:
public const ULONG		mBitAddr15Out           =0x01  ;      //设定A15 引脚的输出值(1)
public const ULONG		mBitIntAction           =0x04    ;    //中断激活状态(0)
//public const ULONG		mBitIntStatus           =0x08    ;    //输入INT#引脚的状态(1)     
public const ULONG		mBitRST0Out             =0x80  ;      //设定RSTO 引脚的输出值(1)
//0xFA
public const ULONG		mBitSpeedInact          =0xFA    ;    //含建立时间和保持时间的读写信号总宽度(0111)
public const ULONG		mBitDataAddrOutCreate=   0x10   ;     //数据和地址输出建立时间(0),0:15nS,1:45nS
public const ULONG		mBitDataAddrOutKeep     =0x20  ;      //数据和地址输出保持时间(0),0:15nS,1:45nS
public const ULONG		mBitLocalBusWidth       =0x40    ;    //本地数据总线宽度(0),0:8位,1:32位
//0xFD
public const ULONG		mBitHWCountH4           =0x0F   ;   //硬件循环计数的高4 位(XXXX),与硬件循环计数寄存器CNTR 合在一起共12 位
public const ULONG		mBitSpiTransportStatus  =0x10    ;    //SPI 传输正在进行状态(0),0:空闲,1:正在传输
public const ULONG		mBitSpiClockFreq        =0x20    ;    //选择SPI 串行时钟频率(0),0:31.3MHz,1:15.6MHz
public const ULONG		mBitSelSpiInPin         =0x40   ;     //选择SPI 数据输入引脚(0),0:SDK,1:ADDR
public const ULONG		mBitStartNewSPITrans    =0x80   ;     //使能读SPIDR 后启动新传输(0),0:读后空闲,1:读后启动


// 应用层接口的功能代码
public const ULONG		mFuncNoOperation	=	0x00000000;	// 无操作
public const ULONG		mFuncGetVersion		=	0x00000001;	// 获取驱动程序版本号
public const ULONG		mFuncGetIoBaseAddr	=	0x00000004;	// 读取I/O端口基址
public const ULONG		mFuncSetIoBaseAddr	=	0x00000005	;// 设置I/O端口基址
public const ULONG		mFuncGetMemBaseAddr	=	0x00000006;	// 读取存储器基址
public const ULONG		mFuncSetMemBaseAddr=		0x00000007	;// 设置存储器基址,自动设定存储器基址
public const ULONG		mFuncGetInterLine	=	0x00000008;	// 读取中断号
public const ULONG		mFuncSetInterLine	=	0x00000009;	// 设置中断号,自动检测中断号
public const ULONG		mFuncWaitInterrupt	=	0x0000000a	;// 等待中断,直到CH367产生中断
public const ULONG		mFuncAbortWaitInter=		0x0000000b	;// 放弃等待中断,终止等待
public const ULONG		mFuncSetExclusive	=   0x0000000c;	// 设置独占使用
public const ULONG		mFuncReadIoByte	=		0x00000010;	// 读取输入输出端口,在同一个端口地址以字节为单位连续读取
public const ULONG		mFuncReadIoWord		=	0x00000011	;// 读取输入输出端口,在同一个端口地址以字为单位连续读取
public const ULONG		mFuncReadIoDword	=	0x00000012;	// 读取输入输出端口,在同一个端口地址以双字为单位连续读取
public const ULONG		mFuncReadIoBlock	=	0x00000013;	// 读取输入输出端口,每读取一个字节,端口地址加一
public const ULONG		mFuncReadIo32Block	=	0x00000028;	// 读取输入输出端口,每读取四字节,端口地址加四,最大长度232B(从偏移地址00H读到E7H)
public const ULONG		mFuncWriteIoByte	=	0x00000014;	// 写入输入输出端口,在同一个端口地址以字节为单位连续写入
public const ULONG		mFuncWriteIoWord	=	0x00000015;	// 写入输入输出端口,在同一个端口地址以字为单位连续写入
public const ULONG		mFuncWriteIoDword	=	0x00000016;	// 写入输入输出端口,在同一个端口地址以双字为单位连续写入
public const ULONG		mFuncWriteIoBlock	=	0x00000017	;// 写入输入输出端口,每写入一个字节,端口地址加一
public const ULONG		mFuncWriteIo32Block	=	0x00000029	;// 写入输入输出端口,每写入一个四字节,端口地址加四,最大长度232B(从偏移地址00H写到E7H)
public const ULONG		mFuncReadMemByte	=	0x00000018;	// 读取存储器/寄存器
public const ULONG		mFuncReadMemDword	=	0x0000001a	;// 读取存储器/寄存器
public const ULONG		mFuncWriteMemByte	=	0x0000001c;	// 写入存储器/寄存器
public const ULONG		mFuncWriteMemDword	=	0x0000001e;	// 写入存储器/寄存器
public const ULONG		mFuncReadConfig	=		0x00000020;	// 读取PCI配置空间
public const ULONG		mFuncWriteConfig	=	0x00000021;	// 写入PCI配置空间
public const ULONG		mFuncReadBuffer1	=	0x00000024	;// 读取中断命令缓冲区1
public const ULONG		mFuncWriteBuffer1	=	0x00000025;	// 写入中断命令缓冲区1
public const ULONG		mFuncReadBuffer2	=	0x00000026	;// 读取中断命令缓冲区2
public const ULONG		mFuncWriteBuffer2	=	0x00000027;	// 写入中断命令缓冲区2

public const ULONG		mFuncStreamSPI	    =	0x0000002A;	// SPI数据流传输函数
public const ULONG		mFuncSetStreamMode  =  	0x0000002B;	// 设置SPI为SPI3或SPI4
public const ULONG		mFuncSetInterMode  =  	0x0000002C;	// 设置中断极性及输入类型


public const ULONG		mFuncFlashLock  =  	0x0000002D;	// 对Flash-ROM存储器进行写保护设定 
public const ULONG		mFuncFlashRead  =  	0x0000002E;	// 从Flash-ROM存储器读取数据块
public const ULONG		mFuncFlashErase  =  	0x0000002F;	// 对Flash-ROM存储器的指定区域进行擦除,每4096字节即4K为一个扇区,最小擦除单位是扇区
public const ULONG		mFuncFlashWrite   = 	0x00000030;	// 向Flash-ROM存储器写入数据块
		[DllImport("CH367.dll", EntryPoint = "CH367mOpenDevice", CharSet = CharSet.Ansi)]
		public static extern HANDLE CH367mOpenDevice(  // 打开CH367设备,返回句柄,出错则无效
			ULONG			iIndex,  // 指定CH367设备序号,0对应第一个设备
	BOOL			iEnableMemory,  // 是否需要支持存储器,CH367芯片不支持,CH368芯片支持
	BOOL			iEnableInterrupt,  // 是否需要支持中断
    UCHAR           iInterruptMode ); // 位0:中断输入的极性1:高电平/下降沿;0:低电平/上升沿;位1:中断输入的类型 1:边沿,0:电平
		[DllImport("CH367.dll", EntryPoint = "CH367mReadConfig", CharSet = CharSet.Ansi)]
		public static extern BOOL CH367mReadConfig(  // 从配置空间读取一个字节数据
 	ULONG			iIndex,  // 指定CH367设备序号
 	PVOID			iOffset,  // 指定偏移地址
 	//PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据
	ref byte oByte);  // 指向一个字节单元,用于保存读取的字节数据

		[DllImport("CH367.dll", EntryPoint = "CH367mCloseDevice", CharSet = CharSet.Ansi)]
		public static extern void CH367mCloseDevice(  // 关闭CH367设备
	ULONG			iIndex );  // 指定CH367设备序号


		[DllImport("CH367.dll", EntryPoint = "CH367mAccessBlock", CharSet = CharSet.Ansi)]
		public static extern BOOL CH367mAccessBlock(  // 读取或者写入数据块
	ULONG			iIndex,  // 指定CH367设备序号
	ULONG			iAccessMode,  // 参考下面的说明
	PVOID			iAddr,  // 指定I/O端口或者存储器的地址
	//PVOID			ioBuffer,  // 指向输入或者输出的缓冲区
    byte[] ioBuffer,
            ULONG			iLength );  // 数据块长度,也就是读取或者写入的字节数,长度不超过32KB

		[DllImport("CH367.dll", EntryPoint = "CH367mReadIoByte", CharSet = CharSet.Ansi)]
		public static extern BOOL CH367mReadIoByte(  // 从I/O端口读取一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
			//PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据
	ref byte oByte);  // 指向一个字节单元,用于保存读取的字节数据

		[DllImport("CH367.dll", EntryPoint = "CH367mWriteIoByte", CharSet = CharSet.Ansi)]
		public static extern BOOL CH367mWriteIoByte(  // 向I/O端口写入一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	UCHAR			iByte );  // 待写入的字节数据

		[DllImport("CH367.dll", EntryPoint = "CH367GetDrvVersion", CharSet = CharSet.Ansi)]
		public static extern ULONG CH367GetDrvVersion( );  // 获得驱动程序版本号,返回版本号,出错则返回0

		[DllImport("CH367.dll", EntryPoint = "CH367mGetIntLine", CharSet = CharSet.Ansi)]
		public static extern BOOL CH367mGetIntLine(  // 获取中断号
	ULONG			iIndex,  // 指定CH367设备序号
	//PULONG			oIntLine );  // 保存中断号的单元地址
	ref ULONG oIntLine);  // 保存中断号的单元地址


		[DllImport("CH367.dll", EntryPoint = "CH367mGetIoBaseAddr", CharSet = CharSet.Ansi)]
		public static extern BOOL CH367mGetIoBaseAddr(  // 获取I/O端口的基址
	ULONG iIndex,  // 指定CH367设备序号
	//mPCH367_IO_REG* oIoBaseAddr);  // 保存I/O端口基址的单元地址
	//ref _CH367_IO_REG oIoBaseAddr);  // 保存I/O端口基址的单元地址
           out PVOID ptr);  // 保存I/O端口基址的单元地址

        [DllImport("CH367.dll", EntryPoint = "CH368mGetMemBaseAddr", CharSet = CharSet.Ansi)]
        public static extern BOOL CH368mGetMemBaseAddr(  // 获取存储器的基址
    ULONG iIndex,  // 指定CH367设备序号
            //mPCH368_MEM_REG	*oMemBaseAddr );  // 保存存储器基址的单元地址
            //ref _CH368_MEM_REG	oMemBaseAddr );  // 保存存储器基址的单元地址
            out PVOID ptr);
		public delegate void mPCH367_INT_ROUTINE();

 		[DllImport("CH367.dll", EntryPoint = "CH367mSetIntRoutine", CharSet = CharSet.Ansi)]
 		public static extern BOOL CH367mSetIntRoutine(  // 设定中断服务程序
 	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_INT_ROUTINE	iIntRoutine );  // 指定中断服务程序,为NULL则取消中断服务,否则在中断时调用该程序
	}
}
