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

namespace 水听器数据监测
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        TCPAsyncServer tcpAsyncServer = null;
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            if (toolStripButton1.Text == "开始")
            {
                toolStripButton1.Text = "停止";
                tcpAsyncServer.Start();
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("服务器启动\r\n");
                NetLog("\r\n");
                //this.Text = tcpAsyncServer.TCPServerName + ":" + tcpAsyncServer.TCPServerPort;
            }
            else
            {
                toolStripButton1.Text = "开始";
                tcpAsyncServer.Stop();
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("服务器停止\r\n");
                NetLog("\r\n");               
            }
        }
        void NetLog(string str)
        {
            textBox1.AppendText(str);
            WFNetLib.Log.TextLog.AddTextLog(str);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            tcpAsyncServer = new TCPAsyncServer();
            tcpAsyncServer.SaveDataProcessCallback = new SaveDataProcessCallbackDelegate(SaveDataProcessCallbackProc);
            tcpAsyncServer.ErrorServerEvent += new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.AcceptServerEvent += new TCPAcceptEvent(tcpAsyncServer_AcceptServer);
            tcpAsyncServer.DisconnectServerEvent += new TCPDisconnectEvent(tcpAsyncServer_DisconnectServer);
            tcpAsyncServer.ReceiveServerEvent += new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent);
            tcpAsyncServer.TCPServerPort = 6000;            
        }
        public static object SaveDataProcessCallbackProc(byte[] tempbuffer, ref byte[] buffer, ref int dataOffset, int length)
        {
            if (length % 2 != 0)
                return null;
            byte[] ret=new byte[length];
            Array.Copy(tempbuffer, 0, ret, 0, length);
            return ret;            
        }
        private void tcpAsyncServer_ReceiveServerEvent(object sender, ReceiveServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("收到ad采集板数据" + e.Client.clientEndPoint.ToString() + ":");
                byte[] rx = (byte[])e.netPacket;
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < rx.Length; i+=2)
                {
                    ushort ad = BytesOP.MakeShort(rx[i], rx[i + 1]);
                    double v = (double)ad;
                    v = v / 65536;
                    v = v * 5.12;
                    chart1.Series[0].Points.AddY(v);
                    int max=10240;
                    if (chart1.Series[0].Points.Count > max)
                    {
                        while (chart1.Series[0].Points.Count > (max - 1024))
                        {
                            chart1.Series[0].Points.RemoveAt(0);
                        }
                    }
                    sb.Append(v.ToString("f3") + ";");
                }
                NetLog(sb.ToString());
                NetLog("\r\n");                
            }));
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
                NetLog("PIC采集板接入:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                NetLog("\r\n");
            }));
        }
        private void tcpAsyncServer_DisconnectServer(object sender, DisconnectEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("AD采集板断开");
                NetLog("\r\n");
            }));
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 32000)
                textBox1.Clear();
        }
    }
}
