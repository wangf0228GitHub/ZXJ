using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.TCP;
using WFNetLib;
using WFNetLib.PacketProc;
using System.Net;
using WFNetLib.Log;

namespace 水听器数据监测
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
		public static WFNetLib.TCP.ClientContext mcuClientContext;
        TCPAsyncServer tcpAsyncServer = null;
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            if (toolStripButton1.Text == "开始")
            {
				if (!int.TryParse(tbPort.Text, out tcpAsyncServer.TCPServerPort))
				{
					MessageBox.Show("输入的端口号格式有问题!!");
					return;
				}
                toolStripButton1.Text = "停止";
                tcpAsyncServer.Start();
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("服务器启动\r\n");
                NetLog("\r\n");
				timer1.Enabled = true;
                //this.Text = tcpAsyncServer.TCPServerName + ":" + tcpAsyncServer.TCPServerPort;
            }
            else
            {
                toolStripButton1.Text = "开始";
                tcpAsyncServer.Stop();
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("服务器停止\r\n");
                NetLog("\r\n");
				mcuClientContext = null;
				timer1.Enabled = false;
            }
        }
        void NetLog(string str)
        {
            textBox1.AppendText(str);
            WFNetLib.Log.TextLog.AddTextLog(str);
        }
        string fileHY;
        private void Form1_Load(object sender, EventArgs e)
        {
			CP1616_NoAddr_Packet.bVerify = false;
            tcpAsyncServer = new TCPAsyncServer();
			tcpAsyncServer.SaveDataProcessCallback = new SaveDataProcessCallbackDelegate(CP1616_NoAddr_Packet.SaveDataProcessCallbackProc);
            tcpAsyncServer.ErrorServerEvent += new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.AcceptServerEvent += new TCPAcceptEvent(tcpAsyncServer_AcceptServer);
            tcpAsyncServer.DisconnectServerEvent += new TCPDisconnectEvent(tcpAsyncServer_DisconnectServer);
            tcpAsyncServer.ReceiveServerEvent += new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent);
			if (!int.TryParse(tbPort.Text, out tcpAsyncServer.TCPServerPort))
			{
				MessageBox.Show("输入的端口号格式有问题!!");
				return;
			}
			toolStripButton1.Text = "停止";
			mcuClientContext = null;
			tcpAsyncServer.Start();
			NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
			NetLog("服务器启动\r\n");
			NetLog("\r\n");
			timer1.Enabled = true;
            DateTime dt = DateTime.Now;
            fileHY = System.Windows.Forms.Application.StartupPath + "\\TextLog\\HY" + String.Format("{0:D4}{1:D2}{2:D2}{3:D2}{4:D2}{5:D2}", dt.Year, dt.Month, dt.Day, dt.Hour, dt.Minute, dt.Second) + ".txt";
            TextLog.AddTextLog("实验开始时间:" + dt.ToString(), fileHY, false);
        }
        private void tcpAsyncServer_ReceiveServerEvent(object sender, ReceiveServerEventArgs e)
        {
			 IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            //if (ip.Address.Equals(mcuSocketIP.Address))

			 if (mcuClientContext != null && e.Client == mcuClientContext)
			 {
				 this.Invoke((EventHandler)(delegate
				 {
					 CP1616_NoAddr_Packet rx = (CP1616_NoAddr_Packet)e.netPacket;
					 if (rx.Header.Command == 0x01)
					 {
						 textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
						 textBox1.AppendText("收到水听器采集板数据" + e.Client.clientEndPoint.ToString());
						 textBox1.AppendText("\r\n");
						 int max = 102400;
						 if (chart1.Series[0].Points.Count > max)
						 {
							 chart1.Series[0].Points.Clear();
						 }
                         StringBuilder sb = new StringBuilder();
						 for (int i = 0; i < (rx.Data.Length - 2); i += 2)
						 {
							 ushort ad = BytesOP.MakeShort(rx.Data[i], rx.Data[i + 1]);
							 double v = (double)ad;
							 v = v * 0.000185;
							 v = v - 6.144;
							 //chart1.Series[0].Points.Clear();
							 chart1.Series[0].Points.AddY(v);
                             sb.AppendLine(v.ToString());
// 							 int max = 1024000;
// 							 if (chart1.Series[0].Points.Count > max)
// 							 {
// 								 while (chart1.Series[0].Points.Count > (max - 1024))
// 								 {
// 									 chart1.Series[0].Points.RemoveAt(0);
// 								 }
// 							 }
						 }
                         TextLog.AddTextLog(sb.ToString(), fileHY, false);
					 }
				 }));
			 }
			 else
			 {
				 this.Invoke((EventHandler)(delegate
				 {
					 textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
					 textBox1.AppendText("收到未知IP数据" + e.Client.clientEndPoint.ToString() + ":");
					 textBox1.AppendText("\r\n");
					 CP1616_NoAddr_Packet rx = (CP1616_NoAddr_Packet)e.netPacket;
					 if (rx.Header.Command == 0xf0)
					 {
						 if (rx.Data[0] == 0x02)//矢量水听器采集板接入
						 {
							 mcuClientContext = e.Client;
							 //mcuSocketIP.Port = ip.Port;
							 this.Invoke((EventHandler)(delegate
							 {
								 NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
								 NetLog("水听器采集板接入");
								 NetLog("\r\n");

							 }));
						 }
					 }
				 }));
			 }
        }
        private void tcpAsyncServer_ErrorServer(object sender, ErrorServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(e.Error.Message + "\r\n");

            }));
        }
        private void tcpAsyncServer_AcceptServer(object sender, AcceptServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(DateTime.Now.ToLongTimeString() + ":");
                NetLog("Appcet:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                NetLog("\r\n");
            }));
			byte[] tx = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0xf0);
			tcpAsyncServer.Send(e.Client, tx);
        }
        private void tcpAsyncServer_DisconnectServer(object sender, DisconnectEventArgs e)
        {
			IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
			if (mcuClientContext != null && e.Client == mcuClientContext)
			{
				mcuClientContext = null;
				this.Invoke((EventHandler)(delegate
				{
					NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
					NetLog("水听器采集板断开");
					NetLog("\r\n");
				}));
			}
			else
			{
				this.Invoke((EventHandler)(delegate
				{
					NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
				}));				
				if (mcuClientContext != null)
				{
					IPEndPoint mcuSocketIP = (IPEndPoint)mcuClientContext.ClientSocket.RemoteEndPoint;
					if (ip.Address.Equals(mcuSocketIP.Address))
					{
						this.Invoke((EventHandler)(delegate
						{
							NetLog("上一个水听器采集板IP断开");
						}));
					}
				}
				this.Invoke((EventHandler)(delegate
				{
					NetLog("客户端断开连接" + e.Client.ClientSocket.RemoteEndPoint.ToString());
					NetLog("\r\n");
				}));
			}
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 32000)
                textBox1.Clear();
        }

		private void timer1_Tick(object sender, EventArgs e)
		{
			//看看是否有未知的板子接入
			ClientContext[] clientList = tcpAsyncServer.ClientContextList;
			foreach (ClientContext client in clientList)
			{
				if (mcuClientContext != null)
				{
					if (client == mcuClientContext)
					{
						continue;
					}
				}
				byte[] tx = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0xf0);
				tcpAsyncServer.Send(client, tx);
			}
		}

		private void Form1_FormClosing(object sender, FormClosingEventArgs e)
		{
			tcpAsyncServer.Stop();
		}

		private void toolStripButton2_Click(object sender, EventArgs e)
		{
			timer1.Enabled = false;
			//bForm2 = true;
			Form2 f = new Form2(tcpAsyncServer);
			f.ShowDialog();
			timer1.Enabled = true;
			//bForm2 = false;
		}
    }
}
