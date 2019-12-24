using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using WFNetLib;
using WFNetLib.PacketProc;
using System.Diagnostics;
using System.Threading;

namespace 无线网络49上位机
{
    public partial class Form1 : Form
    {
        SerialPort Uart;
        public Form1(SerialPort _Uart)
        {
            InitializeComponent();
            Uart = _Uart;
        }
        _SensorSignIn sensorSingIn;
        _SensorBAT sensorBAT;
        byte startResult;
        private void btNetStart_Click(object sender, EventArgs e)
        {
            if (btNetStart.Text == "启动网络")
            {
                sensorSingIn.clearSignIn();
                listView1.Items.Clear();
                for (int i = 0; i < 3; i++)
                {
                    startResult = 0;
                    waitCommand = 5;
                    //timer1.Enabled = true;
                    CP1616Packet.CP1616ComSend(ref Uart, waitCommand, 0, (ushort)0);
                    int x = 0;
                    while (true)
                    {
                        Thread.Sleep(1);
                        if (startResult != 0)
                            break;
                        x++;
                        if (x > 500)
                        {
                            startResult = 0xff;
                            break;
                        }
                    }
                    if (startResult == 0xff)//超时了
                    {

                    }
                    else
                    {
                        break;
                        
                    }
                }
                if (startResult == 0xff)
                {
                    MessageBox.Show("网络控制器未做应答!!!");
                    return;
                }
                else if (startResult == 2)
                {
                    waitCommand = 0x10;
                    MessageBox.Show("网络已经启动，等待接入");
                }
                else if (startResult == 3)
                {
                    waitCommand = 0x10;
                    MessageBox.Show("测量网络已经启动，将自动转为标定网络，等待接入");
                }
                else
                {
                    WaitSometingForm.WaitSometing_Init();
                    waitCommand = 0x10;//点名完成
                    if (!WaitSometingForm.WaitSometing(10, 3000, "等待无线节点组网，预计时长25s"))
                    {
                        waitCommand = 0;
                        MessageBox.Show("组网失败");
                        return;
                    }
                    if (listView1.Items.Count != 0)
                    {
                        WaitSometingForm.WaitSometing_Init();
                        waitCommand = 0x22;//等待标定数据
                        if (!WaitSometingForm.WaitSometing(10, 500, "等待网络数据，预计时长3s"))
                        {
                            waitCommand = 0;
                            MessageBox.Show("组网失败");
                            bStopNet = false;
                            return;
                        }
                        bStopNet = false;
                        btNetStart.Text = "停止网络";
                        MessageBox.Show("网络启动成功");                        
                    }
                    else
                    {
                        waitCommand = 0;
                        MessageBox.Show("当前网络没有发现任何无线节点，网络自动停止");
                        return;
                    }
                }
                bStopNet = false;                
            }
            else
            {
                bStopNet = true;
                WaitSometingForm.WaitSometing_Init();
                waitCommand = 0x02;//等待网络停止
                if (!WaitSometingForm.WaitSometing(10, 500, "等待网络停止，预计时长5s"))
                {
                    waitCommand = 0;
                    MessageBox.Show("网络停止失败");
                    return;
                }
                MessageBox.Show("网络已停止");
                btNetStart.Text = "启动网络";
            }
        }
        byte waitCommand;
        public void UartRxProc(CP1616Packet rxPacket)
        {
            if (bClosing)
                return;
            //Debug.WriteLine(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rxPacket.Data, " "));
            byte[] data = new byte[2];
            data[0] = rxPacket.Header.Command;
            if (bStopNet)
            {
                data[1] = 0x02;//
                CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);//接收应答,并要求关闭网络
            }
            else if (rxPacket.Header.Command == 5)//标定网络启动确认
            {
                startResult = rxPacket.Data[0];
            }
            else if (rxPacket.Header.Command == 0x10)
            {
                data[1] = 0x00;
                CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);//接收应答
                SignInProc(rxPacket);                
            }
            else if (rxPacket.Header.Command == 0x22)//标定软件只处理标定数据
            {
                startResult = 2;
                if (listView1.Items.Count == 0)
                {
                    data[1] = 0x01;//请求传感器名单
                    CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);//接收应答,并请求传感器名单
                }
                else
                {
                    data[1] = 0x00;
                    CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);//接收应答
                    ADCDataProc(rxPacket);
                }
                this.Invoke((EventHandler)(delegate
                {
                    if (btNetStart.Text == "启动网络")
                    {
                        btNetStart.Text = "停止网络";
                    }
                }));                
            }
            else if (rxPacket.Header.Command == 0x20)//测量网络，请求转换为标定网络
            {
                this.Invoke((EventHandler)(delegate
                {
                    textBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:ffff") + ":测量网络转换为标定网络\r\n");
                }));  
                
                startResult = 3;
                data[1] = 0x03;
                CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);
            }
            if (waitCommand == rxPacket.Header.Command)
            {
                WaitSometingForm.bGenerateSometing = true;
            }
            
        }
        bool bStopNet = false;
        bool bClosing = false;
        private void Form1_Load(object sender, EventArgs e)
        {
            //timer1.Enabled = true;
            sensorSingIn = new _SensorSignIn();
            sensorBAT = new _SensorBAT();            
//             double yValue = 50.0;
//             Random random = new Random();
//             for (int pointIndex = 0; pointIndex < 20000; pointIndex++)
//             {
//                 yValue = yValue + (random.NextDouble() * 10.0 - 5.0);
//                 chart1.Series[0].Points.AddY(yValue);
//             }

//             RxPacket = new CP1616Packet();
//             this.Uart.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.Uart_DataReceived);
        }   

        private void listView1_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            // 取消掉正在调整的事件 
            e.Cancel = true;
            // 把新宽度恢复到之前的宽度 
            e.NewWidth = this.listView1.Columns[e.ColumnIndex].Width; 
        }

        private void listView1_Resize(object sender, EventArgs e)
        {
            listView1.Columns[3].Width = listView1.ClientSize.Width - listView1.Columns[0].Width - listView1.Columns[1].Width - listView1.Columns[2].Width;
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 10000)
                textBox1.Clear();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            startResult = 0xff;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            bClosing = true;
            //Uart.Close();
        }     
    }
}
