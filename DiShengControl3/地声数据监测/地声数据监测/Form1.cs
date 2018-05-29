using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.TCP;
using WFNetLib.PacketProc;
using System.Net;
using WFNetLib;

namespace 地声数据监测
{
    public partial class Form1 : Form
    {        
        public Form1()
        {
            InitializeComponent();
        }
        //public static bool bPic=false;
        public static WFNetLib.TCP.ClientContext mcuClientContext;
        //public static IPEndPoint mcuSocketIP;
        TCPAsyncServer tcpAsyncServer = null;
        private void Form1_Load(object sender, EventArgs e)
        {
            tcpAsyncServer = new TCPAsyncServer();
            tcpAsyncServer.SaveDataProcessCallback = new SaveDataProcessCallbackDelegate(CP1616_NoAddr_Packet.SaveDataProcessCallbackProc);
            tcpAsyncServer.ErrorServerEvent += new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.AcceptServerEvent += new TCPAcceptEvent(tcpAsyncServer_AcceptServer);
            tcpAsyncServer.DisconnectServerEvent += new TCPDisconnectEvent(tcpAsyncServer_DisconnectServer);
            tcpAsyncServer.ReceiveServerEvent += new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent);
			

			mcuClientContext = null;
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
            listView1_Resize(null, null);
			timer1.Enabled = true;
        }

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
                //bPic = false;
                timer1.Enabled = false;
				mcuClientContext = null;
            }
        }
        void NetLog(string str)
        {
            textBox1.AppendText(str);
            WFNetLib.Log.TextLog.AddTextLog(str);
        }
        public static double rioCur;
        public static bool bPower1, bPower2;
        public static byte[] bIO=new byte[6];
        private void tcpAsyncServer_ReceiveServerEvent(object sender, ReceiveServerEventArgs e)
        {
            IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            //if (ip.Address.Equals(mcuSocketIP.Address))
            
			if (mcuClientContext!=null && e.Client == mcuClientContext)
            {
                this.Invoke((EventHandler)(delegate
                {
                    CP1616_NoAddr_Packet rx = (CP1616_NoAddr_Packet)e.netPacket;  
                    if(rx.Header.Command==0x01)
                    {
                        double f;
                        byte[] fb = new byte[4];
                        int fbIndex;
                        string str;
                        bool bSave = false;
                        //温度
                        f = BytesOP.MakeShort(rx.Data[0], rx.Data[1]);
                        f = f / 100;
                        listView1.Items[0].SubItems[1].Text = f.ToString("F2");
                        //电子罗盘
                        fbIndex = 2;
                        for (int i = 0; i < 4; i++)
                        {
                            fb[i] = rx.Data[fbIndex + 3 - i];
                        }
                        f = BitConverter.ToSingle(fb, 0);
                        listView1.Items[1].SubItems[1].Text = f.ToString("F2");

                        fbIndex = 6;
                        for (int i = 0; i < 4; i++)
                        {
                            fb[i] = rx.Data[fbIndex + 3 - i];
                        }
                        f = BitConverter.ToSingle(fb, 0);
                        listView1.Items[2].SubItems[1].Text = f.ToString("F2");

                        fbIndex = 10;
                        for (int i = 0; i < 4; i++)
                        {
                            fb[i] = rx.Data[fbIndex + 3 - i];
                        }
                        f = BitConverter.ToSingle(fb, 0);
                        listView1.Items[3].SubItems[1].Text = f.ToString("F2");

                        //授时
                        str = Encoding.UTF8.GetString(rx.Data, 14, 10);
                        listView1.Items[4].SubItems[1].Text = str;

                        str = Encoding.UTF8.GetString(rx.Data, 24, 6);
                        listView1.Items[5].SubItems[1].Text = str;

                        //MS8607
                        f = BitConverter.ToSingle(rx.Data, 30);
                        listView1.Items[6].SubItems[1].Text = f.ToString("F2");

                        f = BitConverter.ToSingle(rx.Data, 34);
                        listView1.Items[7].SubItems[1].Text = f.ToString("F2");

                        f = BitConverter.ToSingle(rx.Data, 38);
                        listView1.Items[8].SubItems[1].Text = f.ToString("F2");
                        //光源
                        f = BytesOP.MakeShort(rx.Data[44], rx.Data[45]);
                        f = f / 10;
                        rioCur = f;
                        listView1.Items[14].SubItems[1].Text = f.ToString("F1");
                        ushort rioStatus = BytesOP.MakeShort(rx.Data[42], rx.Data[43]);
                        listView1.Items[15].SubItems[1].Text = rioStatus.ToString("X04");
                        if (BytesOP.GetBit(rioStatus, 0))
                        {
                            listView1.Items[16].SubItems[1].Text = "是";
                            listView1.Items[16].BackColor = Color.Lime;
                        }
                        else
                        {
                            listView1.Items[16].SubItems[1].Text = "否";
                            listView1.Items[16].BackColor = Color.Red;
                        }
                        if (BytesOP.GetBit(rioStatus, 6))
                        {
                            listView1.Items[17].SubItems[1].Text = "是";
                            listView1.Items[17].BackColor = Color.Red;
                        }
                        else
                        {
                            listView1.Items[17].SubItems[1].Text = "否";
                            listView1.Items[17].BackColor = Color.Lime;
                        }
                        if (BytesOP.GetBit(rioStatus, 7))
                        {
                            listView1.Items[18].SubItems[1].Text = "是";
                            listView1.Items[18].BackColor = Color.Red;
                        }
                        else
                        {
                            listView1.Items[18].SubItems[1].Text = "否";
                            listView1.Items[18].BackColor = Color.Lime;
                        }
                        //通信错误帧统计
                        listView1.Items[9].SubItems[1].Text = rx.Data[46].ToString();
                        if (rx.Data[46] > 5)
                        {
                            bSave = true;
                            listView1.Items[9].BackColor = Color.Red;
                        }
                        else
                        {
                            listView1.Items[9].BackColor = SystemColors.Window;
                        }

                        listView1.Items[10].SubItems[1].Text = rx.Data[47].ToString();
                        if (rx.Data[47] > 5)
                        {
                            bSave = true;
                            listView1.Items[10].BackColor = Color.Red;
                        }
                        else
                        {
                            listView1.Items[10].BackColor = SystemColors.Window;
                        }

                        listView1.Items[11].SubItems[1].Text = rx.Data[48].ToString();
                        if (rx.Data[48] > 5)
                        {
                            bSave = true;
                            listView1.Items[11].BackColor = Color.Red;
                        }
                        else
                        {
                            listView1.Items[11].BackColor = SystemColors.Window;
                        }

                        listView1.Items[12].SubItems[1].Text = rx.Data[49].ToString();
                        if (rx.Data[49] > 5)
                        {
                            bSave = true;
                            listView1.Items[12].BackColor = Color.Red;
                        }
                        else
                        {
                            listView1.Items[12].BackColor = SystemColors.Window;
                        }

                        listView1.Items[13].SubItems[1].Text = rx.Data[50].ToString();
                        if (rx.Data[50] > 5)
                        {
                            bSave = true;
                            listView1.Items[13].BackColor = Color.Red;
                        }
                        else
                        {
                            listView1.Items[13].BackColor = SystemColors.Window;
                        }

                        listView1.Items[19].SubItems[1].Text = rx.Data[51].ToString();//漏水1
                        listView1.Items[20].SubItems[1].Text = rx.Data[52].ToString();//漏水2
                        listView1.Items[21].SubItems[1].Text = rx.Data[53].ToString();//备用IO1
                        listView1.Items[22].SubItems[1].Text = rx.Data[54].ToString();//备用IO1
                        listView1.Items[23].SubItems[1].Text = rx.Data[55].ToString();//备用IO1
                        listView1.Items[24].SubItems[1].Text = rx.Data[56].ToString();//备用IO1
                        listView1.Items[25].SubItems[1].Text = rx.Data[57].ToString();//备用IO1
                        listView1.Items[26].SubItems[1].Text = rx.Data[58].ToString();//备用IO1

                        for (int i = 0; i < 6; i++)
                        {
                            bIO[i] = rx.Data[53 + i];
                        }

                        if (rx.Data[59] == 0)
                        {
                            listView1.Items[27].SubItems[1].Text = "打开";
                            bPower1 = true;
                        }
                        else
                        {
                            listView1.Items[27].SubItems[1].Text = "关闭";
                            bPower1 = false;
                        }

                        if (rx.Data[60] == 0)
                        {
                            listView1.Items[28].SubItems[1].Text = "打开";
                            bPower2 = true;
                        }
                        else
                        {
                            listView1.Items[28].SubItems[1].Text = "关闭";
                            bPower2 = false;
                        }

                        if (bSave)
                        {
                            NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                            NetLog("收到单片机采集板数据" + e.Client.clientEndPoint.ToString() + ":");
                            NetLog(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, " "));
                            NetLog("\r\n");
                        }
                        else
                        {
                            textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                            textBox1.AppendText("收到单片机采集板数据" + e.Client.clientEndPoint.ToString() + ":");
                            textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, " "));
                            textBox1.AppendText("\r\n");
                        }
                    }
                    else
                    {
                        textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                        textBox1.AppendText("收到单片机采集板数据" + e.Client.clientEndPoint.ToString() + ":");
                        textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, " "));
                        textBox1.AppendText("\r\n");
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
						if (rx.Data[0] == 0x01)//传感器采集板接入
						{
							mcuClientContext = e.Client;
							//mcuSocketIP.Port = ip.Port;
							this.Invoke((EventHandler)(delegate
							{
								NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
								NetLog("单片机采集板接入");
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
                NetLog("Accept:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                NetLog("\r\n");
            }));
			byte[] tx = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0xf0);			
			tcpAsyncServer.Send(e.Client, tx);
        }
        private void tcpAsyncServer_DisconnectServer(object sender, DisconnectEventArgs e)
        {
            IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            //if (ip.Address.Equals(mcuSocketIP.Address))
            if(mcuClientContext!=null && e.Client==mcuClientContext)
            {
				mcuClientContext = null;
                this.Invoke((EventHandler)(delegate
                {                    
                    NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                    NetLog("传感器采集板断开");
                    NetLog("\r\n");
                }));
            }            
            else
            {
				NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
				if (mcuClientContext != null)
				{
					IPEndPoint mcuSocketIP = (IPEndPoint)mcuClientContext.ClientSocket.RemoteEndPoint;
					if (ip.Address.Equals(mcuSocketIP.Address))
					{
						this.Invoke((EventHandler)(delegate
						{
							NetLog("上一个单片机采集板IP断开");							
						}));
					}
				}
				this.Invoke((EventHandler)(delegate
				{
					NetLog("客户端断开连接" + e.Client.ClientSocket.RemoteEndPoint.ToString());
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
			if (mcuClientContext != null)
			{
				byte[] tx = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0x01);
				this.Invoke((EventHandler)(delegate
				{
					textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
					textBox1.AppendText("发送到" + mcuClientContext.clientEndPoint.ToString() + ":");
					textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(tx, " "));
					textBox1.AppendText("\r\n");
				}));
				tcpAsyncServer.Send(mcuClientContext, tx);
			}
			//看看是否有未知的板子接入
			ClientContext[] clientList = tcpAsyncServer.ClientContextList;
			foreach (ClientContext client in clientList)
			{
				if(mcuClientContext!=null)
				{
					if (client == mcuClientContext)
					{
						continue;
					}
				}
				byte[] tx = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0xf0);				
				tcpAsyncServer.Send(client, tx);
			}
			//if (bPic)
			//{
			
			//}
			
        }

        private void listView1_Resize(object sender, EventArgs e)
        {
            listView1.Columns[2].Width = listView1.ClientSize.Width - listView1.Columns[0].Width - listView1.Columns[1].Width;
        }
        //bool bForm2=false;
        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            //bForm2 = true;
            Form2 f = new Form2(tcpAsyncServer);
            f.ShowDialog();
            timer1.Enabled = true;
            //bForm2 = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            tcpAsyncServer.Stop();
        }
    }
}
