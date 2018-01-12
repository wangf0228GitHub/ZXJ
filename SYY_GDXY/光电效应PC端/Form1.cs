using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Printing;
using Microsoft.Reporting.WinForms;
using System.IO;
using System.Drawing.Imaging;
using WFNetLib.TCP;
using WFNetLib;
using WFNetLib.PacketProc;
using System.Collections;
using System.Threading;

namespace 光电效应PC端
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Hide();
                this.ShowInTaskbar = false;
                this.notifyIcon.Visible = true;
            } 
        }

        private void notifyIcon_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Show();
                this.WindowState = FormWindowState.Normal;
                notifyIcon.Visible = false;
                this.ShowInTaskbar = true;
            } 
        }
        bool bPrint;
        string pathPDF;
        private IList<Stream> m_streams;
        TCPAsyncServer tcpAsyncServer=null;
        private void Form1_Load(object sender, EventArgs e)
        {
            iniFileOP.iniFilePath = System.Windows.Forms.Application.StartupPath + "\\miConfig.ini";
            if (iniFileOP.Read("Work Setting", "bPrint") == "1")
                bPrint = true;
            else
                bPrint = false;
            pathPDF = iniFileOP.Read("Work Setting", "pathPDF");
            CurveDataTable = new Hashtable();
            tcpAsyncServer = new TCPAsyncServer();
            tcpAsyncServer.TCPServerPort = 8000;
            tcpAsyncServer.ErrorServerEvent += new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.AcceptServerEvent += new TCPAcceptEvent(tcpAsyncServer_AcceptServer);
            tcpAsyncServer.DisconnectServerEvent += new TCPDisconnectEvent(tcpAsyncServer_DisconnectServer);
            tcpAsyncServer.ReceiveServerEvent += new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent);
            tcpAsyncServer.SaveDataProcessCallback = new SaveDataProcessCallbackDelegate(easyStringPacket.SaveDataProcessCallbackProc);
            tcpAsyncServer.Start();
            textBox1.AppendText("服务启动" + "\r\n");
            byte[] xx=NetPacket.MakeStringPacket("123");

            this.reportViewer1.RefreshReport();
        }
        Hashtable CurveDataTable;
        private void tcpAsyncServer_ReceiveServerEvent(object sender, ReceiveServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {                
                string strRx = (string)e.netPacket;                
                string[] rxList=strRx.Split(',');
                string key = e.Client.ClientSocket.RemoteEndPoint.ToString();
                //if(rxList.Length==2)
                {
                    int index=int.Parse(rxList[0]);
                    if(index==1)//学号等信息
                    {
                        textBox1.AppendText(strRx + "\r\n");
                        CurveData cd=new CurveData();
                        string[] infoList=rxList[1].Split('|');
                        if(infoList.Length==4)
                        {
                            cd.ZuoWeiHao=infoList[0];
                            cd.BanJi=infoList[1];
                            cd.XueHao=infoList[2];
                            cd.exWorkTepy = byte.Parse(infoList[3]);
                            CurveDataTable[key]=cd;
                            WFGlobal.WaitMS(1000);
                            textBox1.AppendText("学号信息\r\n");
                            tcpAsyncServer.Send(e.Client, easyStringPacket.MakePacket("01,OK"));
                        }
                    }
                    else if (index <= 7 && index >= 2)
                    {
                        CurveData cd = (CurveData)CurveDataTable[key];
                        if (cd != null)
                        {
                            int nCount = int.Parse(rxList[1]);
                            string[] infoList = rxList[2].Split('|');
                            if (infoList.Length == nCount)
                            {
                                cd.VADataCount[index - 2] = nCount;
                                for (int i = 0; i < nCount; i++)
                                {
                                    cd.VAData[index - 2, i] = (float)(float.Parse(infoList[i]) * 0.000763);
                                }
                                cd.bVAExist[index-2] = true;
                                CurveDataTable[key] = cd;
                                WFGlobal.WaitMS(1000);
                                textBox1.AppendText("实验数据\r\n");
                                tcpAsyncServer.Send(e.Client, easyStringPacket.MakePacket(index.ToString("d2")+",OK"));
//                                 if (index == 7)
//                                 {
//                                     ReportPrint(cd);
//                                 }
                            }                            
                        }
                    }
                    else if (index <= 11 && index >= 8)
                    {
                        CurveData cd = (CurveData)CurveDataTable[key];
                        int gqIndex = index - 8;
                        if (cd != null)
                        {
                            int nCount = int.Parse(rxList[1]);
                            string[] infoList = rxList[2].Split('|');
                            if (infoList.Length == nCount)
                            {
                                cd.GQDataCount[gqIndex] = nCount;
                                for (int i = 0; i < nCount; i++)
                                {
                                    cd.GQData[gqIndex, i] = (float)(float.Parse(infoList[i]) * 0.000763);
                                }
                                cd.bGQExist[gqIndex] = true;
                                CurveDataTable[key] = cd;
                                WFGlobal.WaitMS(1000);
                                textBox1.AppendText("实验数据\r\n");
                                tcpAsyncServer.Send(e.Client, easyStringPacket.MakePacket(index.ToString("d2") + ",OK"));
                                //                                 if (index == 7)
                                //                                 {
                                //                                     ReportPrint(cd);
                                //                                 }
                            }
                        }
                    }
                    else if (index ==12)
                    {
                        CurveData cd = (CurveData)CurveDataTable[key];
                        if (cd != null)
                        {
                            string[] infoList = rxList[1].Split('|');
                            if (infoList.Length == 9)
                            {
                                for (int i = 0; i < 9; i++)
                                {
                                    cd.PLKData[i]= float.Parse(infoList[i]);
                                }
                                cd.bPLKExist = true;
                                CurveDataTable[key] = cd;
                                WFGlobal.WaitMS(1000);
                                textBox1.AppendText("实验数据\r\n");
                                tcpAsyncServer.Send(e.Client, easyStringPacket.MakePacket(index.ToString("d2") + ",OK"));
                                //                                 if (index == 7)
                                //                                 {
                                //                                     ReportPrint(cd);
                                //                                 }
                            }
                        }
                    }
                    else if (index == 99)//请求打印帧
                    {
                        CurveData cd = (CurveData)CurveDataTable[key];
                        if (cd != null)
                        {
                            WFGlobal.WaitMS(1000);
                            textBox1.AppendText("开始打印\r\n");
                            tcpAsyncServer.Send(e.Client, easyStringPacket.MakePacket(index.ToString("d2") + ",OK"));
                            ReportPrint(cd);
                        }
                    }
                }                
                //textBox1.AppendText(strRx + "\r\n");
//                 NetPacket np = (NetPacket)e.netPacket;
//                 switch (np.PacketHead.PType)
//                 {
//                     case NetPacket.NetPacketType.STRING:
//                         textBox1.AppendText("收到字符串" + np.Data.ToString() + "\r\n");
//                         tcpAsyncServer.Send(e.Client, NetPacket.MakeStringPacket("服务器收到数据" + np.Data.ToString()));
//                         break;
//                     case NetPacket.NetPacketType.BINARY:
//                         NetFile nf = (NetFile)np.Data;
//                         textBox1.AppendText("收到文件" + nf.FileName + ",正在后台生成.....\r\n");
//                         string file = System.Windows.Forms.Application.StartupPath + "\\收到的文件\\" + nf.FileName;
//                         FileInfo f = new FileInfo(file);
//                         if (!Directory.Exists(f.DirectoryName))
//                             Directory.CreateDirectory(f.DirectoryName);
//                         FileStream fs = null;
//                         fs = new FileStream(file, FileMode.Create);
//                         fs.BeginWrite(nf.Content, 0, nf.Content.Length, NetFileWriteOK, fs);
//                         break;
//                     case NetPacket.NetPacketType.COMPLEX:
//                         NetObject no = (NetObject)np.Data;
//                         textBox1.AppendText("收到序列对象" + no.TypeName + ",正在后台生成.....\r\n");
//                         break;
//                 }
            }));
        }
        private void tcpAsyncServer_ErrorServer(object sender, ErrorServerEventArgs e)
        {
            try
            {
                this.Invoke((EventHandler)(delegate
                {
                    textBox1.AppendText(e.Error.Message + "\r\n");
                }));
            }
            catch// (System.Exception ex)
            {
            	
            }            
        }
        private void tcpAsyncServer_AcceptServer(object sender, AcceptServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(e.Client.ClientSocket.RemoteEndPoint.ToString() + "\r\n");
//                 ComboBoxItem c = new ComboBoxItem(e.Client.ClientSocket.RemoteEndPoint.ToString(), e.Client.key);
//                 int i = toolStripComboBox1.Items.Add(c);
//                 toolStripComboBox1.SelectedIndex = i;
            }));
        }
        private void tcpAsyncServer_DisconnectServer(object sender, DisconnectEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                try
                {
                    textBox1.AppendText(e.Client.ClientSocket.RemoteEndPoint.ToString() + "\r\n");
                }
                catch// (System.Exception ex)
                {
                	
                }
                
//                 foreach (object o in toolStripComboBox1.Items)
//                 {
//                     if (o.ToString() == e.Client.ClientSocket.RemoteEndPoint.ToString())
//                     {
//                         toolStripComboBox1.Items.Remove(o);
//                         break;
//                     }
//                 }
            }));
        }
        
        private void button1_Click(object sender, EventArgs e)
        {
            CurveData cd = new CurveData();
            cd.XueHao = "111";
            cd.exWorkTepy = 0x08;
            cd.bGQExist[0] = true;
            ReportPrint(cd);
           //ProgramPrint();
            //ReportPrint();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            tcpAsyncServer.Stop();
        }
        
    }
}
