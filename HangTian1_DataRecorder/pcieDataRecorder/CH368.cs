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
		UCHAR[] mCH367IoPort;                     //00H-E7H,共232字节为标准的I/O端口
		UCHAR mCH367GPOR;	                        //E8H 通用输出寄存器
		UCHAR mCH367GPVR;	                        //E9H 通用变量寄存器
		UCHAR mCH367GPIR;	                        //EAH 通用输入寄存器
		UCHAR mCH367IntCtr;	                        //EBH 中断控制寄存器
		[MarshalAs(UnmanagedType.ByValArray , SizeConst = 4)]
		UCHAR[] mCH367IoBuf;
// 		union{
// 			UCHAR mCH367IoBuf8;                     //ECH 8位被动并行接口数据缓冲区
// 			ULONG mCH367IoBuf32;                    //ECH 32位被动并行接口数据缓冲区
// 		};
		[MarshalAs(UnmanagedType.ByValArray , SizeConst = 2)]
		UCHAR[] mCH368MemAddr;

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
		UCHAR mCH367IORESV2;                        //F2H
		UCHAR mCH368MemData;                        //F3H 存储器接口: 存储器数据存取寄存器
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		UCHAR[] mCH367DataSta;
// 		union{
// 			UCHAR mCH367Data8Sta;                   //F4H D7-D0端口状态寄存器
// 			ULONG mCH367SData32Sta;                 //F4H D31-D0端口状态寄存器
// 		};
		UCHAR mCH367Status;                         //F8H 杂项控制和状态寄存器
		UCHAR mCH367IO_RESV3;                       //F9H
		UCHAR mCH367Speed;                          //FAH 读写速度控制寄存器
		UCHAR mCH367PDataCtrl;                      //FBH 被动并行接口控制寄存器
		UCHAR mCH367IoTime;                         //FCH 硬件循环计数寄存器
		UCHAR mCH367SPICtrl;                        //FDH SPI控制寄存器
		UCHAR mCH367SPIData;                        //FEH SPI数据寄存器
		UCHAR mCH367IO_RESV4;                       //FFH
	}
	[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
	public struct _CH368_MEM_REG 
	{				// CH367芯片的存储器空间
		[MarshalAs(UnmanagedType.ByValArray , SizeConst = 0x8000)]
		UCHAR[]	mCH368MemPort;		// 0000H-7FFFH,共32768字节为标准的存储器单元		
	}

	public class CH368
	{
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
	PVOID			ioBuffer,  // 指向输入或者输出的缓冲区
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
	ref _CH367_IO_REG oIoBaseAddr);  // 保存I/O端口基址的单元地址


		[DllImport("CH367.dll", EntryPoint = "CH368mGetMemBaseAddr", CharSet = CharSet.Ansi)]
		public static extern BOOL CH368mGetMemBaseAddr(  // 获取存储器的基址
	ULONG			iIndex,  // 指定CH367设备序号
	//mPCH368_MEM_REG	*oMemBaseAddr );  // 保存存储器基址的单元地址
	ref _CH368_MEM_REG	oMemBaseAddr );  // 保存存储器基址的单元地址

		public delegate void mPCH367_INT_ROUTINE();

 		[DllImport("CH367.dll", EntryPoint = "CH367mSetIntRoutine", CharSet = CharSet.Ansi)]
 		public static extern BOOL CH367mSetIntRoutine(  // 设定中断服务程序
 	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_INT_ROUTINE	iIntRoutine );  // 指定中断服务程序,为NULL则取消中断服务,否则在中断时调用该程序
	}
}
