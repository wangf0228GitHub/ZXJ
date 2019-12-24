using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using WFNetLib.PacketProc;
using WFNetLib;
using System.Diagnostics;

namespace 无线网络49上位机
{
    public partial class SetCalibrationForm : Form
    {
        SerialPort Uart;
        public SetCalibrationForm(SerialPort _Uart)
        {
            InitializeComponent();
            Uart = _Uart;
        }
        byte waitCommand;
        public void UartRxProc(CP1616Packet rxPacket)
        {
            Debug.WriteLine(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rxPacket.Data, " "));
            if (rxPacket.Header.Command != waitCommand)
                return;
            WaitSometingForm.bGenerateSometing = true;
            if (rxPacket.Header.Command==6)
            {
                if (rxPacket.Data[0] == 1)//设定成功
                {
                    this.Invoke((EventHandler)(delegate
                    {
                        StringBuilder sb = new StringBuilder();
                        sb.Append("设定成功：\r\n");
                        sb.Append("          节点ID:" + rxPacket.Data[1].ToString() + "\r\n");
                        float k, b, A;
                        k = BitConverter.ToSingle(rxPacket.Data, 2);
                        b = BitConverter.ToSingle(rxPacket.Data, 6);
                        A = BitConverter.ToSingle(rxPacket.Data, 10);
                        sb.Append("          原系数为:\r\n");
                        sb.Append("          k=" + k.ToString() + "\r\n");
                        sb.Append("          b=" + b.ToString() + "\r\n");
                        sb.Append("          A=" + A.ToString() + "\r\n");
                        sb.Append("          新系数为:\r\n");
                        k = BitConverter.ToSingle(rxPacket.Data, 14);
                        b = BitConverter.ToSingle(rxPacket.Data, 18);
                        A = BitConverter.ToSingle(rxPacket.Data, 22);
                        sb.Append("          k=" + k.ToString() + "\r\n");
                        sb.Append("          b=" + b.ToString() + "\r\n");
                        sb.Append("          A=" + A.ToString() + "\r\n");
                        MessageBox.Show(this, sb.ToString());
                    }));
                }
                else if (rxPacket.Data[0] == 2)
                {
                    this.Invoke((EventHandler)(delegate
                    {
                        MessageBox.Show(this, "设定失败，没有无线节点响应");
                    }));
                }
                else if (rxPacket.Data[0] == 3)//设定成功
                {
                    this.Invoke((EventHandler)(delegate
                    {
                        MessageBox.Show(this, "网络已经启动，请先利用“网络采集AD值”停止网络后再进行此操作");
                    }));
                }
            }
            else if (rxPacket.Header.Command == 7)
            {
                if (rxPacket.Data[0] == 1)//设定成功
                {
                    this.Invoke((EventHandler)(delegate
                    {                        
                        float k, b, A;
                        k = BitConverter.ToSingle(rxPacket.Data, 2);
                        b = BitConverter.ToSingle(rxPacket.Data, 6);
                        A = BitConverter.ToSingle(rxPacket.Data, 10);

                        textBox1.Text = k.ToString();
                        textBox2.Text = b.ToString();
                        textBox3.Text = A.ToString();
                        MessageBox.Show(this, "读取成功!!!");
                    }));
                }
                else if (rxPacket.Data[0] == 2)
                {
                    this.Invoke((EventHandler)(delegate
                    {
                        MessageBox.Show(this, "读取失败，没有无线节点响应");
                    }));
                }
                else if (rxPacket.Data[0] == 3)//设定成功
                {
                    this.Invoke((EventHandler)(delegate
                    {
                        MessageBox.Show(this, "网络已经启动，请先利用“网络采集AD值”停止网络后再进行此操作");
                    }));
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1+12];
            float k, b, A;
            if (float.TryParse(textBox1.Text, out k) == false)
            {
                MessageBox.Show("节点斜率k输入有误");
                return;
            }
            if (float.TryParse(textBox2.Text, out b) == false)
            {
                MessageBox.Show("节点截距b输入有误");
                return;
            }
            if (float.TryParse(textBox3.Text, out A) == false)
            {
                MessageBox.Show("节点增益A输入有误");
                return;
            }
            data[0] = (byte)numericUpDown2.Value;
            byte[] kbyte = BitConverter.GetBytes(k);
            byte[] bbyte = BitConverter.GetBytes(b);
            byte[] Abyte = BitConverter.GetBytes(A);
            for (int i = 0; i < 4; i++)
            {
                data[1 + i] = kbyte[i];
                data[5 + i] = bbyte[i];
                data[9 + i] = Abyte[i];
            }
            WaitSometingForm.WaitSometing_Init();
            waitCommand = 6;
            CP1616Packet.CP1616ComSend(ref Uart, waitCommand, 0, data);
            if (!WaitSometingForm.WaitSometing(100, 150, "等待控制器设定节点标定系数，预计时长15s"))
            {
                waitCommand = 0;
                MessageBox.Show("设定失败！！！！！");
            }
            waitCommand = 0;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1];            
            data[0] = (byte)numericUpDown2.Value;
            WaitSometingForm.WaitSometing_Init();
            waitCommand = 7;
            CP1616Packet.CP1616ComSend(ref Uart, waitCommand, 0, data);
            if (!WaitSometingForm.WaitSometing(100, 150, "等待控制器读取节点标定系数，预计时长15s"))
            {
                waitCommand = 0;
                MessageBox.Show("读取失败！！！！！");
            }
            waitCommand = 0;
        }
    }
}
