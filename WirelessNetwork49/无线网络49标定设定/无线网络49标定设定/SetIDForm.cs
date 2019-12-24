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
    public partial class SetIDForm : Form
    {
        SerialPort Uart;
        public SetIDForm(SerialPort _Uart)
        {
            InitializeComponent();
            Uart = _Uart;
        }
        byte waitCommand;
        private void button1_Click(object sender, EventArgs e)
        {
            byte[] data=new byte[2];
            data[1]= (byte)numericUpDown1.Value;
            data[0]=(byte)numericUpDown2.Value;
            if(numericUpDown2.Value==0)
                data[0]=0xfe;//广播地址
            WaitSometingForm.WaitSometing_Init();
            waitCommand = 4;
            CP1616Packet.CP1616ComSend(ref Uart, waitCommand, 0, data);
            if (!WaitSometingForm.WaitSometing(100, 150, "等待控制器设定节点ID，预计时长15s"))
            {
                waitCommand = 0;
                MessageBox.Show("设定失败！！！！！");
            }
            waitCommand = 0;
        }
        public void UartRxProc(CP1616Packet rxPacket)
        {
            Debug.WriteLine(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rxPacket.Data, " "));
            if (rxPacket.Header.Command != waitCommand)
                return;
            WaitSometingForm.bGenerateSometing = true;
            if (rxPacket.Data[0] == 1)//设定成功
            {
                this.Invoke((EventHandler)(delegate
                {
                    MessageBox.Show(this, "设定成功：" + rxPacket.Data[1].ToString() + "->" + rxPacket.Data[2].ToString());
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

        private void button2_Click(object sender, EventArgs e)
        {

        }
    }
}
