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
using System.Threading;
using WFNetLib;
using WFOffice;
using System.Windows.Forms.DataVisualization.Charting;
using System.IO;
using System.Diagnostics;
using Microsoft.Office.Interop.Excel;

namespace 弗兰克赫兹上位机
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
            CP1616PacketHead.Addr_SIZE = 0;
            CP1616PacketHead.DataLen_SIZE = 1;
            CP1616PacketHead.CalcHeaderLen();            
        }
        CP1616Packet Rx1616;
        string PortName;
        private void btConnect_Click(object sender, EventArgs e)
        {
            serialPort1.ReadTimeout = 500;
            bool bOK = false;
            string[] ports = SerialPort.GetPortNames();
            Rx1616 = new CP1616Packet(1, 1);
            PortName = "";
            progressBar1.Value = 0;
            progressBar1.Maximum = ports.Length*3;
            foreach (string com in ports)
            {
                serialPort1.PortName = com;
                for (int i = 0; i < 3; i++)
                {
                    progressBar1.PerformStep();
                    try
                    {
                        serialPort1.Open();
                        byte[] tx = CP1616Packet.MakeCP1616Packet(1, 1, null);
                        try
                        {
                            serialPort1.Write(tx, 0, tx.Length);
                        }
                        catch { continue; }
                        while (true)
                        {
                            try
                            {
                                if (Rx1616.DataPacketed((byte)serialPort1.ReadByte()))
                                {
                                    if(Rx1616.Data[0]==0x01)//成功
                                    {
                                        PortName = com;
                                        progressBar1.Value = progressBar1.Maximum;
                                        bOK = true;
                                        bConnect.BackColor = Color.Green;
                                        lConnect.Text = "已连接";
                                        MessageBox.Show("成功连接到主机！！！");
                                        btDisconnect.Enabled = true;
                                        btScan.Enabled = true;
                                        btConnect.Enabled = false;
                                        break;
                                    }
                                    else
                                    {
                                        serialPort1.Close();
                                        if (Rx1616.Data[0] == 0x10)
                                            MessageBox.Show("主机设备自动模式无法与计算机进行连接！");
                                        else
                                            MessageBox.Show("主机设备当前无法与计算机进行连接！"+Rx1616.Data[0].ToString("x02"));
                                        return;
                                    }
                                }
                            }
                            catch
                            { break; }
                        }
                        if (PortName != "")
                            break;
                        serialPort1.Close();
                        Thread.Sleep(100);
                    }
                    catch
                    {
                        break;
                    }
                }
                if (PortName != "")
                {
                    break;
                }
            }
            if (PortName == "")
            {
                progressBar1.Value = progressBar1.Maximum;
                MessageBox.Show("未找到设备");
            }
        }

        private void btDisconnect_Click(object sender, EventArgs e)
        {
            serialPort1.ReadTimeout = 500;
            Rx1616 = new CP1616Packet(2, 1);
            byte[] tx = CP1616Packet.MakeCP1616Packet(2, 1, 1);
            try
            {
                serialPort1.Write(tx, 0, tx.Length);
            }
            catch
            {
                PortName = "";
                progressBar1.Value = progressBar1.Maximum;
                serialPort1.Close();
                bConnect.BackColor = Color.Red;
                lConnect.Text = "已断开";
                MessageBox.Show("成功断开连接！！！");
            }
            while (true)
            {
                try
                {
                    if (Rx1616.DataPacketed((byte)serialPort1.ReadByte()))
                    {
                        PortName = "";
                        progressBar1.Value = progressBar1.Maximum;
                        bConnect.BackColor = Color.Red;
                        lConnect.Text = "已断开";
                        MessageBox.Show("成功与主机断开连接！！！");
                        break;
                    }
                }
                catch
                { break; }
            }
            serialPort1.Close();
            btDisconnect.Enabled = false;
            btScan.Enabled = false;
            btConnect.Enabled = true;
        }
        public int stepV=5;
        public int stepS = 1000;
        public int bYaGuan = 1;
        public double UF = 8.0;
        public double UG1K = 10.0;
        public double UG2A = 2.3;
//         public string strName;
//         public string strClass;
//         public string strNumber;
        private void btScan_Click(object sender, EventArgs e)
        {
            chart1.Series[0].Points.Clear();
            btDisconnect.Enabled = false;
            btScan.Enabled = false;
            btConnect.Enabled = false;
            button1.Enabled = false;
            btReport.Enabled = false;
            btCalc.Enabled = false;
            progressBar1.Value = 0;
            switch (stepV)
            {
                case 2://0.16,2
                    progressBar1.Maximum=512;
                    break;
                case 5://0.4,5
                    progressBar1.Maximum = 205;
                    break;
                case 10://0.8,10
                    progressBar1.Maximum = 103;
                    break;
            }
            tScan.Interval=stepS;
            daV = 0;
            tScan.Enabled = true;
        }
        int daV;
        void PickFinish()
        {
            btDisconnect.Enabled = true;
            btScan.Enabled = true;
            btConnect.Enabled = false;
            button1.Enabled = true;
            btReport.Enabled = true;
            btCalc.Enabled = true;
        }
        void PickOne()
        {
            serialPort1.ReadTimeout = 2000;
            int retry=3;
            Rx1616 = new CP1616Packet(3, 1);
            byte[] bv=new byte[2];
            bv[0]=BytesOP.GetHighByte((ushort)daV);
            bv[1]=BytesOP.GetLowByte((ushort)daV);
            byte[] tx = CP1616Packet.MakeCP1616Packet(3, 1, bv);
            while(retry!=0)
            {
                try
                {
                    serialPort1.Write(tx, 0, tx.Length);
                }
                catch
                {
                    PortName = "";
                    serialPort1.Close();
                    PickFinish();
                    MessageBox.Show("发送错误，与主机断开连接");
                    btDisconnect.Enabled = false;
                    btConnect.Enabled = true;
                    return;
                }
                while (true)
                {
                    try
                    {
                        if (Rx1616.DataPacketed((byte)serialPort1.ReadByte()))
                        {
                            if (Rx1616.Data[0]==0x01)
                            {
                                chart1.Series[0].Points.AddXY(daV * 0.08, BytesOP.MakeShort(Rx1616.Data[1], Rx1616.Data[2]));
                                lX.Text = (daV * 0.08).ToString("f01");
                                lY.Text = BytesOP.MakeShort(Rx1616.Data[1], Rx1616.Data[2]).ToString();
                                progressBar1.PerformStep();
                                if (daV >= 1023)
                                {
                                    tScan.Enabled = false;
                                    MessageBox.Show("采集完成");
                                    PickFinish();
                                }
                                else
                                {
                                    tScan.Enabled = true;
                                    daV += stepV;
                                    if (daV >= 1023)
                                        daV = 1023;
                                }
                            }
                            else
                            {
                                PortName = "";
                                serialPort1.Close();
                                PickFinish();
                                btDisconnect.Enabled = false;
                                btConnect.Enabled = true;
                                bConnect.BackColor = Color.Red;
                                lConnect.Text = "已断开";
                                MessageBox.Show("发送错误，与主机断开连接");                                
                            }
                            return;
                        }
                    }
                    catch
                    { break; }
                }
                retry--;
            }
            if (retry == 0)//重试失败
            {
                PortName = "";
                serialPort1.Close();
                PickFinish();
                btDisconnect.Enabled = false;
                btConnect.Enabled = true;
                bConnect.BackColor = Color.Red;
                lConnect.Text = "已断开";
                MessageBox.Show("发送错误，与主机断开连接");
            }
        }

        private void tScan_Tick(object sender, EventArgs e)
        {
            tScan.Enabled = false;
            PickOne();
        }
        public void MakeReport(string filename)
        {
            WordReport report = new WordReport();
            //double d;
            if (bYaGuan != 0)
            {
                report.CreateNewDocument(System.Windows.Forms.Application.StartupPath + "\\弗兰克_氩.dot");
                report.InsertValue("V1", tbU1.Text);
                report.InsertValue("V2", tbU2.Text);
                report.InsertValue("V3", tbU3.Text);
                report.InsertValue("V4", tbU4.Text);
                report.InsertValue("V5", tbU5.Text);
                report.InsertValue("V6", tbU6.Text);
            }
            else
            {
                report.CreateNewDocument(System.Windows.Forms.Application.StartupPath + "\\弗兰克_氖.dot");
                report.InsertValue("V1", tbU1.Text);
                report.InsertValue("V2", tbU2.Text);
                report.InsertValue("V3", tbU3.Text);
            }
            report.InsertValue("实验时间", DateTime.Now.ToString("yyyy.MM.dd   HH:mm"));
            report.InsertValue("姓名",lName.Text);
            report.InsertValue("班级", lClass.Text);
            report.InsertValue("学号", lNumber.Text);
            report.InsertValue("灯丝电压", UF.ToString("f02"));
            report.InsertValue("控制栅电压", UG1K.ToString("f02"));
            report.InsertValue("拒斥电压", UG2A.ToString("f02"));
            report.InsertValue("VAverage", tbU0.Text);
            string pic=System.Windows.Forms.Application.StartupPath + "\\temp\\1.tiff";
            FileInfo f = new FileInfo(pic);
            // 如果文件所在的文件夹不存在则创建文件夹
            if (!Directory.Exists(f.DirectoryName))
                Directory.CreateDirectory(f.DirectoryName);
            chart1.SaveImage(pic, System.Drawing.Imaging.ImageFormat.Tiff);
            report.InsertPicture("曲线", pic, 350, 300);            
            report.SaveDocument(filename);
        }

        private void btReport_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() != DialogResult.OK)
            {
                return;
            }
            chart1.ChartAreas[0].CursorX.LineWidth = 0;
            chart1.ChartAreas[0].CursorY.LineWidth = 0;
            MakeReport(saveFileDialog1.FileName);
            MessageBox.Show("实验报告保存成功\r\n" + saveFileDialog1.FileName);
            chart1.ChartAreas[0].CursorX.LineWidth = 1;
            chart1.ChartAreas[0].CursorY.LineWidth = 1;
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            FormLogin f = new FormLogin();
            f.ShowDialog();
            lName.Text = f.textBox1.Text;
            lNumber.Text = f.textBox2.Text;
            lClass.Text = f.textBox3.Text;
            ExFormProc();

//             for (int i = 0; i < 1024; i += 5)
//             {
//                 double da = i * 0.08;
//                 double Ip = i / 2;
//                 chart1.Series[0].Points.AddXY(da, Ip);
//             }           
        }
        void ExFormProc()
        {
            if (bYaGuan != 0)
            {
                lGuan.Text = "氩管";
                pbU2.Visible = true;
                pbU3.Visible = true;
                pbU4.Visible = true;
                pbU5.Visible = true;
                pbU6.Visible = true;
                tbU2.Visible = true;
                tbU3.Visible = true;
                tbU4.Visible = true;
                tbU5.Visible = true;
                tbU6.Visible = true;
                lv2.Visible = true;
                lv4.Visible = true;
                lv6.Visible = true;
                pbU2.Image = Properties.Resources.计算3;
                pbU3.Image = Properties.Resources.计算4;
                pbU4.Image = Properties.Resources.计算5;
                pbU5.Image = Properties.Resources.计算6;
                pbU6.Image = Properties.Resources.计算7;
                tbU1.Text = "0.0";
                tbU2.Text = "0.0";
                tbU3.Text = "0.0";
                tbU4.Text = "0.0";
                tbU5.Text = "0.0";
                tbU6.Text = "0.0";
                tbU0.Text = "0.00";
            }
            else
            {
                pbU2.Visible = false;
                pbU3.Visible = true;
                pbU4.Visible = false;
                pbU5.Visible = true;
                pbU6.Visible = false;
                tbU2.Visible = false;
                tbU3.Visible = true;
                tbU4.Visible = false;
                tbU5.Visible = true;
                tbU6.Visible = false;
                lv2.Visible = false;
                lv4.Visible = false;
                lv6.Visible = false;
                //pbU2.Image = Properties.Resources.计算3;
                pbU3.Image = Properties.Resources.计算3;
                //pbU4.Image = Properties.Resources.计算5;
                pbU5.Image = Properties.Resources.计算4;
                //pbU6.Image = Properties.Resources.计算7;
                tbU1.Text = "0.0";
                tbU2.Text = "0.0";
                tbU3.Text = "0.0";
                tbU4.Text = "0.0";
                tbU5.Text = "0.0";
                tbU6.Text = "0.0";
                tbU0.Text = "0.00";
                lGuan.Text = "氖管";
            }
            lUF.Text = UF.ToString("f02") + "V";
            lUG1K.Text = UG1K.ToString("f02") + "V";
            lUG2A.Text = UG2A.ToString("f02") + "V";
            switch (stepV)
            {
                case 2://0.16,2
                    lStepV.Text = "0.16 V";
                    break;
                case 5://0.4,5
                    lStepV.Text = "0.40 V";
                    break;
                case 10://0.8,10
                    lStepV.Text = "0.80 V";
                    break;
            }
            switch (stepS)
            {
                case 2000://0.16,2
                    lStepS.Text = "2 s";
                    break;
                case 1000://0.4,5
                    lStepS.Text = "1 s";
                    break;
                case 500://0.8,10
                    lStepS.Text = "0.5 s";
                    break;
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            FormSetting f = new FormSetting(this);           
            f.ShowDialog();
            ExFormProc();
        }

        private void btCalc_Click(object sender, EventArgs e)
        {
            double u1=0, u2=0, u3=0, u4=0, u5=0, u6=0;
            double ud1,ud2,ud3,ud4,ud5,u0;
            if (bYaGuan != 0)
            {
                if (tbU1.Text == "" || !double.TryParse(tbU1.Text, out u1))
                {
                    MessageBox.Show("第一个峰电压输入有误");
                    return;
                }
                if (tbU2.Text == "" || !double.TryParse(tbU2.Text, out u2))
                {
                    MessageBox.Show("第二个峰电压输入有误");
                    return;
                }
                if (tbU3.Text == "" || !double.TryParse(tbU3.Text, out u3))
                {
                    MessageBox.Show("第三个峰电压输入有误");
                    return;
                }
                if (tbU4.Text == "" || !double.TryParse(tbU4.Text, out u4))
                {
                    MessageBox.Show("第四个峰电压输入有误");
                    return;
                }
                if (tbU5.Text == "" || !double.TryParse(tbU5.Text, out u5))
                {
                    MessageBox.Show("第五个峰电压输入有误");
                    return;
                }
                if (tbU6.Text == "" || !double.TryParse(tbU6.Text, out u6))
                {
                    MessageBox.Show("第六个峰电压输入有误");
                    return;
                }
                ud1 = u2 - u1;
                ud2 = u3 - u2;
                ud3 = u4 - u3;
                ud4 = u5 - u4;
                ud5 = u6 - u5;
                u0 = ud1;
                u0 += ud2;
                u0 += ud3;
                u0 += ud4;
                u0 += ud5;
                u0 = u0 / 5;
                tbU0.Text = u0.ToString("f02");
            }
            else
            {
                if (tbU1.Text == "" || !double.TryParse(tbU1.Text, out u1))
                {
                    MessageBox.Show("第一个峰电压输入有误");
                    return;
                }               
                if (tbU3.Text == "" || !double.TryParse(tbU3.Text, out u2))
                {
                    MessageBox.Show("第三个峰电压输入有误");
                    return;
                }                
                if (tbU5.Text == "" || !double.TryParse(tbU5.Text, out u3))
                {
                    MessageBox.Show("第五个峰电压输入有误");
                    return;
                }                
                ud1 = u2 - u1;
                ud2 = u3 - u2;                
                u0 = ud1;
                u0 += ud2;                
                u0 = u0 / 2;
                tbU0.Text = u0.ToString("f02");
            }
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(MessageBox.Show("是否关闭软件？","关闭软件",MessageBoxButtons.YesNo,MessageBoxIcon.Question)!=DialogResult.Yes)
                e.Cancel=true;
        }

        private void chart1_CursorPositionChanged(object sender, CursorEventArgs e)
        {
            
        }

        private void chart1_CursorPositionChanging(object sender, CursorEventArgs e)
        {
            int N=chart1.Series[0].Points.Count;
            if (N == 0)
                return;
            if (e.Axis.AxisName == AxisName.X)
            {
                int xindex = GetPointIndex(e.NewPosition);                
                e.NewPosition = chart1.Series[0].Points[xindex].XValue;
                lX.Text = e.NewPosition.ToString("f01");
            }
            if (e.Axis.AxisName == AxisName.Y)
            {
                double x = e.ChartArea.CursorX.Position;
                for (int i = 0; i < N; i++)
                {
                    if (x == chart1.Series[0].Points[i].XValue)
                    {
                        e.NewPosition = chart1.Series[0].Points[i].YValues[0];
                        lY.Text = e.NewPosition.ToString();
                        return;
                    }
                }
               
                
            }
        }

      

        private void chart1_KeyPress(object sender, KeyPressEventArgs e)
        {
            
        }

        private void FormMain_KeyPress(object sender, KeyPressEventArgs e)
        {
            
        }
        int GetPointIndex(double x)
        {
            int N = chart1.Series[0].Points.Count;
            double[] d = new double[N];
            for (int i = 0; i < N; i++)
            {
                d[i] = x - chart1.Series[0].Points[i].XValue;
            }
            double dmin = double.MaxValue;
            int xindex = 0;
            for (int i = 0; i < N; i++)
            {
                if (Math.Abs(d[i]) < dmin)
                {
                    dmin = d[i];
                    xindex = i;
                }
            }
            return xindex;
        }
        private void FormMain_KeyDown(object sender, KeyEventArgs e)
        {
            double x = 0;
            if (!double.TryParse(lX.Text, out x))
                return;
            int xindex = GetPointIndex(x);
            if(e.KeyData==Keys.Left)
            {
                if (xindex != 0)
                {
                    xindex--;
                    chart1.ChartAreas[0].CursorX.Position = chart1.Series[0].Points[xindex].XValue;
                    chart1.ChartAreas[0].CursorY.Position = chart1.Series[0].Points[xindex].YValues[0];
                    lX.Text = chart1.ChartAreas[0].CursorX.Position.ToString("f01");
                    lY.Text = chart1.ChartAreas[0].CursorY.Position.ToString();
                }
            }
            else if (e.KeyData == Keys.Right)
            {
                if (xindex <(chart1.Series[0].Points.Count-1))
                {
                    xindex++;
                    chart1.ChartAreas[0].CursorX.Position = chart1.Series[0].Points[xindex].XValue;
                    chart1.ChartAreas[0].CursorY.Position = chart1.Series[0].Points[xindex].YValues[0];
                    lX.Text = chart1.ChartAreas[0].CursorX.Position.ToString("f01");
                    lY.Text = chart1.ChartAreas[0].CursorY.Position.ToString();
                }
            }
        }
        protected override bool ProcessDialogKey(Keys keyData)
        {
            if (keyData == Keys.Up || keyData == Keys.Down ||

                keyData == Keys.Left || keyData == Keys.Right)

                return false;

            else

                return base.ProcessDialogKey(keyData);

        }

        private void button4_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(System.Windows.Forms.Application.StartupPath + "\\弗兰克赫兹实验仪软件操作说明.pdf");
        }
        private void button2_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(System.Windows.Forms.Application.StartupPath + "\\弗兰克赫兹实验讲义.pdf");
        }
        ExcelExport ee;
        private void btExcel_Click(object sender, EventArgs e)
        {
            if (chart1.Series[0].Points.Count == 0)
            {
                MessageBox.Show("没有实验数据需要导出!");
                return;
            }
            if (saveFileDialog2.ShowDialog() != DialogResult.OK)
            {
                return;
            }
            ee = new ExcelExport(chart1.Series[0].Points.Count);
            ee.bShowExcel = false;
            ee.ExcelWorkbookCallbackProc = new ExcelExport.ExcelWorkbookCallback(ExcelWorkbookCallbackProc);
            ee.ExcelExportProc();
            MessageBox.Show("实验数据导出成功\r\n" + saveFileDialog2.FileName);
        }
        private bool ExcelWorkbookCallbackProc(Workbook wBook,int sheetIndex, int index)
        {
            Worksheet wSheet;
            string str;
            wSheet = (Worksheet)wBook.Worksheets[1];
            Range dr;
            if (index == -1)
            {               
                wSheet = (Worksheet)wBook.Worksheets[1];
                wSheet.Name = "光电效应实验数据";
                dr = wSheet.get_Range("A2", "A5");
                dr.Merge(0);
                dr.Value = "实验人员";
                dr.HorizontalAlignment = XlVAlign.xlVAlignCenter;
                dr.VerticalAlignment = XlVAlign.xlVAlignCenter;
                wSheet.Cells[2, 2] = "实验时间"; wSheet.Cells[2, 3] = DateTime.Now.ToString("yyyy.MM.dd   HH:mm");
                wSheet.Cells[3, 2] = "姓名"; wSheet.Cells[3, 3] = lName.Text;
                wSheet.Cells[4, 2] = "学号"; wSheet.Cells[4, 3] = lNumber.Text;
                wSheet.Cells[5, 2] = "班级"; wSheet.Cells[5, 3] = lClass.Text;

                dr = wSheet.get_Range("A7", "A10");
                dr.Merge(0);
                dr.Value = "实验条件";
                dr.HorizontalAlignment = XlVAlign.xlVAlignCenter;
                dr.VerticalAlignment = XlVAlign.xlVAlignCenter;
                wSheet.Cells[7, 2] = "电子管类型";
                if (bYaGuan != 0)
                    wSheet.Cells[7, 3] = "氩管";
                else
                    wSheet.Cells[7, 3] = "氖管";
                wSheet.Cells[8, 2] = "灯丝电压"; wSheet.Cells[8, 3] = UF.ToString("f02")+"V";
                wSheet.Cells[9, 2] = "控制柵电压"; wSheet.Cells[9, 3] = UG1K.ToString("f02")+"V";
                wSheet.Cells[10, 2] = "拒斥电压"; wSheet.Cells[10, 3] = UG2A.ToString("f02")+"V";


                dr = wSheet.get_Range("A12", "C12");
                dr.Merge(0);
                dr.Value = "实验数据";
                dr.HorizontalAlignment = XlVAlign.xlVAlignCenter;
                dr.VerticalAlignment = XlVAlign.xlVAlignCenter;

                wSheet.Cells[13, 1] = "序号";
                wSheet.Cells[13, 2] = "加速电压(V)";
                wSheet.Cells[13, 3] = "电流(10^-8A)";
//                 dr = wSheet.get_Range("A7", "C10");
//                 dr.Columns.AutoFit();
//                 dr.HorizontalAlignment = XlHAlign.xlHAlignCenter;
//                 dr.Borders.LineStyle = XlLineStyle.xlContinuous;

            }
            else if (index == int.MaxValue)
            {
                dr=wSheet.get_Range("A1");
                dr.ColumnWidth = 12;
                dr = wSheet.get_Range("B1");
                dr.ColumnWidth = 18;
                dr = wSheet.get_Range("C1");
                dr.ColumnWidth = 18;

                dr = wSheet.get_Range("A2", "C5");
                dr.HorizontalAlignment = XlHAlign.xlHAlignCenter;
                dr.Borders.LineStyle = XlLineStyle.xlContinuous;

                dr = wSheet.get_Range("A7", "C10");
                dr.HorizontalAlignment = XlHAlign.xlHAlignCenter;
                dr.Borders.LineStyle = XlLineStyle.xlContinuous;

                str = "C" + (12 + 1 + chart1.Series[0].Points.Count).ToString();
                dr = wSheet.get_Range("A12", str);
                dr.HorizontalAlignment = XlHAlign.xlHAlignCenter;
                dr.Borders.LineStyle = XlLineStyle.xlContinuous;

                str = "B" + (13 + chart1.Series[0].Points.Count).ToString();
                dr = wSheet.get_Range("B14", str);
                dr.NumberFormat = "0.0";

                str = "C" + (13 + chart1.Series[0].Points.Count).ToString();
                dr = wSheet.get_Range("C14", str);
                dr.NumberFormat = "0";

                dr = wSheet.get_Range("A1", str);
                dr.Font.Name = "宋体";
                dr.Font.Size = "11";

                wBook.Saved = true;
                wBook.SaveCopyAs(saveFileDialog2.FileName);
//                 dr = wSheet.get_Range("A1", "A5");
//                 //dr.Columns.Width=12;
//                 dr.HorizontalAlignment = XlHAlign.xlHAlignCenter;
//                 dr.Borders.LineStyle = XlLineStyle.xlContinuous;
            }
            else
            {
                wSheet.Cells[14+index, 1] = (index+1).ToString();
                wSheet.Cells[14 + index, 2] = chart1.Series[0].Points[index].XValue.ToString();
                wSheet.Cells[14 + index, 3] = chart1.Series[0].Points[index].YValues[0].ToString();
            }
            return true;
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }
    }
}
