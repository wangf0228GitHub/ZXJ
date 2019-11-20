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

        private void button1_Click(object sender, EventArgs e)
        {
            CP1616Packet setID = CP1616Packet.CP1616ComProc(ref Uart, 4, 0, BytesOP.MakeShort((byte)numericUpDown1.Value,0));
            if (setID != null)
            {
                if (setID.Data[0] == 1)//设定成功
                {
                    MessageBox.Show("设定成功：" + setID.Data[1].ToString() + "->" + setID.Data[2].ToString());
                }
                else if (setID.Data[0] == 2)
                {
                    MessageBox.Show("设定失败，没有无线节点响应");
                }
                else if (setID.Data[0] == 3)//设定成功
                {
                    MessageBox.Show("网络已经启动，请先利用“启动网络”功能接入网络，而后停止网络后再设定节点ID");
                }
            }
        }
    }
}
