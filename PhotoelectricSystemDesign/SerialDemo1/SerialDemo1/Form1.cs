using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SerialDemo1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox1.Items.AddRange(ports);
            cp1616 = new CP1616Packet();
        }
        CP1616Packet cp1616;
        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                if (comboBox1.SelectedIndex == -1)
                {
                    MessageBox.Show("请选择设备所对应串口!");
                    return;
                }
                serialPort1.PortName = comboBox1.Text;
                try
                {
                    serialPort1.Open();
                }
                catch
                {
                    MessageBox.Show("所选串口打开失败!");
                    return;
                }
            }
            cp1616.Reset();
            byte[] tx = cp1616.MakeCP1616Packet(0x01);
            textBox1.AppendText("发送:"+byteToHexStr(tx, 0, tx.Length, " ")+"\r\n");
            serialPort1.Write(tx, 0, tx.Length);
            while (true)
            {
                try
                {
                    byte rx = (byte)serialPort1.ReadByte();
                    if (cp1616.DataPacketed(rx))
                    {
                        textBox1.AppendText("接收:" + byteToHexStr(cp1616.HeaderData, 0, cp1616.HeaderData.Length, " "));
                        textBox1.AppendText(byteToHexStr(cp1616.CommandData, 0, cp1616.CommandData.Length, " ") + "\r\n");
                        MessageBox.Show("连接成功");
                        return;
                    }
                }
                catch
                {
                    MessageBox.Show("连接超时");
                    return;
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            serialPort1.Close();
        }
        public string byteToHexStr(byte[] bytes, int offset, int count, string spilt)
        {
            StringBuilder strB = new StringBuilder();
            if (bytes != null)
            {
                for (int i = 0; i < count; i++)
                {
                    strB.Append(bytes[offset + i].ToString("X2"));
                    strB.Append(spilt);
                }
            }
            return strB.ToString();
        }
    }
}
