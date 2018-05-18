using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;
using System.Drawing;
using System.Diagnostics;
using WFNetLib.StringFunc;

namespace 解调仪调试
{
	public delegate void TCPReceiveEvent(byte[] rxFrame);
	public partial class Form1 : Form
	{
		public event TCPReceiveEvent ReceiveServerEvent;
		byte[] tcpTempBuffer;
		byte[] tcpReceiveBuffer;
		int tcpReceiveCount;
		int tcpCommandNeedData;
		TcpClient tcpClient;
		void tcpRxFrameProc(byte[] rxFrame)
		{
			Debug.WriteLine(StringsFunction.byteToHexStr(rxFrame, " "));
		}
		private void AsyncReadCallBack(IAsyncResult iar)
		{
			if ((tcpClient == null) || (!tcpClient.Connected)) 
				return;
			try
			{
				int NumOfBytesRead;
				NetworkStream stream = tcpClient.GetStream();
				NumOfBytesRead = stream.EndRead(iar);
				if (NumOfBytesRead > 0)
				{
					this.Invoke((EventHandler)(delegate
					{
						int rx = int.Parse(tbRxCount.Text);
						rx += NumOfBytesRead;
						tbRxCount.Text = rx.ToString();
					}));
					for (int i = 0; i < NumOfBytesRead; i++)
					{
						tcpReceiveBuffer[tcpReceiveCount++]=tcpTempBuffer[i];
						if (tcpReceiveCount > 5)
						{
							if(tcpReceiveCount == tcpCommandNeedData)
							{
								//完成一帧，推送处理消息
								if (ReceiveServerEvent != null)
								{
									byte[] rxFrame = new byte[tcpCommandNeedData];
									Array.Copy(tcpReceiveBuffer, rxFrame, tcpCommandNeedData);
									ReceiveServerEvent(rxFrame);
									tcpReceiveCount = 0;
								}
							}
						}
						else if (tcpReceiveCount == 5)//命令决定长度
						{
							switch (tcpReceiveBuffer[4])
							{
								case 4:
									tcpCommandNeedData = 0x08+0x05;
									break;
								default:
									tcpReceiveCount = 0;
									break;
							}
						}
						else// if (tcpReceiveCount == 3)//
						{
							if(tcpReceiveBuffer[tcpReceiveCount-1]!=0x55)
								tcpReceiveCount = 0;
						}
					}
					stream.BeginRead(tcpTempBuffer, 0, tcpTempBuffer.Length, new AsyncCallback(AsyncReadCallBack), stream);
				}
				else
				{
					stream.Close();
					tcpClient.Close();
					stream = null;
					tcpClient = null;
					this.Invoke((EventHandler)(delegate
					{
						btConnect.Text = "连接";
						btConnect.BackColor = Color.Lime;
						btSendCommand.Enabled = false;
						btStartSave.Enabled = false;
						timerSave.Enabled = false;
						MessageBox.Show("网络连接已经断开");
					}));
				}
			}
			catch (System.Exception ex)
			{
				if ((tcpClient == null) || (!tcpClient.Connected))
					return;
				tcpClient.Close();
				tcpClient = null;
				this.Invoke((EventHandler)(delegate
				{
					btConnect.Text = "连接";
					btConnect.BackColor = Color.Lime;
					btSendCommand.Enabled = false;
					btStartSave.Enabled = false;
					timerSave.Enabled = false;
					MessageBox.Show("网络连接已经断开:"+ex.Message);
				}));
			}
			
		}
		private void btConnect_Click(object sender, EventArgs e)
		{
			if (btConnect.Text == "连接")
			{
				IPAddress ip = WFNetLib.StringFunc.StringsFunction.CheckIPInput(tbIP.Text);
				if (ip == null)
				{
					MessageBox.Show("ip地址输入不合法");
					return;
				}
				int port;
				if (!int.TryParse(tbPort.Text, out port))
				{
					MessageBox.Show("端口输入不合法");
					return;
				}
 				IPEndPoint targetPoint = new IPEndPoint(ip, port);
				tcpClient = new TcpClient();
				try
				{
					tcpClient.Connect(targetPoint);
				}
				catch (System.Exception ex)
				{
					MessageBox.Show(ex.Message);
					return;
				}
				NetworkStream stream = tcpClient.GetStream();
				if (stream.CanRead)
				{
					stream.BeginRead(tcpTempBuffer, 0, tcpTempBuffer.Length, new AsyncCallback(AsyncReadCallBack), stream);
				}
				else
				{
					MessageBox.Show("网络流无法读取");
					return;
				}
				btConnect.Text = "断开";
				btConnect.BackColor = Color.Salmon;
				btSendCommand.Enabled = true;
				btStartSave.Enabled = true;				
			}
			else
			{
				tcpClient.Close();
				tcpClient = null;
				btConnect.Text = "连接";
				btConnect.BackColor = Color.Lime;
				btSendCommand.Enabled = false;
				btStartSave.Enabled = false;
				timerSave.Enabled = false;
			}
		}
	}
}
