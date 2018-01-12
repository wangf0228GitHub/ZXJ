using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Reporting.WinForms;
using System.Data;
using System.IO;
using System.Drawing.Printing;
using System.Drawing.Imaging;
using WFNetLib;

namespace 光电效应PC端
{
    public partial class Form1 : Form
    {        
        void ReportPrint_PLK_GQ_VA(CurveData cd)
        {
            LocalReport report = new LocalReport();
            report.ReportPath = "reportGDXY6.rdlc";
            DataTable dt = reportDataSet1.Student.Clone();
            GetInfoTable(cd, dt);
            report.DataSources.Add(new ReportDataSource("DataSet1", dt));
            DataTable dt1 = reportDataSet1.Curve.Clone();
            GetVATable(cd, dt1);
            report.DataSources.Add(new ReportDataSource("DataSet2", dt1));
            
            DataTable dt2 = reportDataSet1.Curve1.Clone();
            GetGQTable(cd, dt2);
            report.DataSources.Add(new ReportDataSource("DataSet3", dt2));
            if(cd.bPLKExist)
            {
                DataTable dt3 = reportDataSet1.Curve2.Clone();
                GetPLKTable(cd, dt3);
                report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
            }
            else
            {
                DataTable dt3 = reportDataSet1.Curve2.Clone();
                DataRow dr = dt3.NewRow();                
                dr["Line"] = "";
                dt3.Rows.Add(dr);
                report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
            }
            ReportPrintProc(report);
            //report.Refresh();
            
        }
        void ReportPrint_PLK_GQ(CurveData cd)
        {
            LocalReport report = new LocalReport();
            report.ReportPath = "reportGDXY5.rdlc";
            DataTable dt = reportDataSet1.Student.Clone();
            GetInfoTable(cd, dt);
            report.DataSources.Add(new ReportDataSource("DataSet1", dt));
//             DataTable dt1 = reportDataSet1.Curve.Clone();
//             GetVATable(cd, dt1);
//             report.DataSources.Add(new ReportDataSource("DataSet2", dt1));

            DataTable dt2 = reportDataSet1.Curve1.Clone();
            GetGQTable(cd, dt2);
            report.DataSources.Add(new ReportDataSource("DataSet3", dt2));
            if (cd.bPLKExist)
            {
                DataTable dt3 = reportDataSet1.Curve2.Clone();
                GetPLKTable(cd, dt3);
                report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
            }
            ReportPrintProc(report);
            //report.Refresh();

        }
        void ReportPrint_VA_GQ(CurveData cd)
        {
            LocalReport report = new LocalReport();
            report.ReportPath = "reportGDXY4.rdlc";
            DataTable dt = reportDataSet1.Student.Clone();
            GetInfoTable(cd, dt);
            report.DataSources.Add(new ReportDataSource("DataSet1", dt));
            DataTable dt1 = reportDataSet1.Curve.Clone();
            GetVATable(cd, dt1);
            report.DataSources.Add(new ReportDataSource("DataSet2", dt1));

            DataTable dt2 = reportDataSet1.Curve1.Clone();
            GetGQTable(cd, dt2);
            report.DataSources.Add(new ReportDataSource("DataSet3", dt2));
//             if (cd.bPLKExist)
//             {
//                 DataTable dt3 = reportDataSet1.Curve2.Clone();
//                 GetPLKTable(cd, dt3);
//                 report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
//             }
            ReportPrintProc(report);
            //report.Refresh();

        }
        void ReportPrint_VA_PLK(CurveData cd)
        {
            LocalReport report = new LocalReport();
            report.ReportPath = "reportGDXY3.rdlc";
            DataTable dt = reportDataSet1.Student.Clone();
            GetInfoTable(cd, dt);
            report.DataSources.Add(new ReportDataSource("DataSet1", dt));
            DataTable dt1 = reportDataSet1.Curve.Clone();
            GetVATable(cd, dt1);
            report.DataSources.Add(new ReportDataSource("DataSet2", dt1));

//             DataTable dt2 = reportDataSet1.Curve1.Clone();
//             GetGQTable(cd, dt2);
//             report.DataSources.Add(new ReportDataSource("DataSet3", dt2));
            if (cd.bPLKExist)
            {
                DataTable dt3 = reportDataSet1.Curve2.Clone();
                GetPLKTable(cd, dt3);
                report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
            }
            ReportPrintProc(report);
            //report.Refresh();

        }
        void ReportPrint_GQ(CurveData cd)
        {
            LocalReport report = new LocalReport();
            report.ReportPath = "reportGDXY2.rdlc";
            DataTable dt = reportDataSet1.Student.Clone();
            GetInfoTable(cd, dt);
            report.DataSources.Add(new ReportDataSource("DataSet1", dt));

//             DataTable dt1 = reportDataSet1.Curve.Clone();
//             GetVATable(cd, dt1);
//             report.DataSources.Add(new ReportDataSource("DataSet2", dt1));

            DataTable dt2 = reportDataSet1.Curve1.Clone();
            GetGQTable(cd, dt2);
            report.DataSources.Add(new ReportDataSource("DataSet3", dt2));

//             if (cd.bPLKExist)
//             {
//                 DataTable dt3 = reportDataSet1.Curve2.Clone();
//                 GetPLKTable(cd, dt3);
//                 report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
//             }
            ReportPrintProc(report);
            //report.Refresh();

        }
        void ReportPrint_PLK(CurveData cd)
        {
            LocalReport report = new LocalReport();
            report.ReportPath = "reportGDXY1.rdlc";
            DataTable dt = reportDataSet1.Student.Clone();
            GetInfoTable(cd, dt);
            report.DataSources.Add(new ReportDataSource("DataSet1", dt));

            //             DataTable dt1 = reportDataSet1.Curve.Clone();
            //             GetVATable(cd, dt1);
            //             report.DataSources.Add(new ReportDataSource("DataSet2", dt1));

//             DataTable dt2 = reportDataSet1.Curve1.Clone();
//             GetGQTable(cd, dt2);
//             report.DataSources.Add(new ReportDataSource("DataSet3", dt2));

            if (cd.bPLKExist)
            {
                DataTable dt3 = reportDataSet1.Curve2.Clone();
                GetPLKTable(cd, dt3);
                report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
            }
            ReportPrintProc(report);
            //report.Refresh();

        }
        void ReportPrint_VA(CurveData cd)
        {
            LocalReport report = new LocalReport();
            report.ReportPath = "reportGDXY.rdlc";
            DataTable dt = reportDataSet1.Student.Clone();
            GetInfoTable(cd, dt);
            report.DataSources.Add(new ReportDataSource("DataSet1", dt));

            DataTable dt1 = reportDataSet1.Curve.Clone();
            GetVATable(cd, dt1);
            report.DataSources.Add(new ReportDataSource("DataSet2", dt1));

            //             DataTable dt2 = reportDataSet1.Curve1.Clone();
            //             GetGQTable(cd, dt2);
            //             report.DataSources.Add(new ReportDataSource("DataSet3", dt2));

//             if (cd.bPLKExist)
//             {
//                 DataTable dt3 = reportDataSet1.Curve2.Clone();
//                 GetPLKTable(cd, dt3);
//                 report.DataSources.Add(new ReportDataSource("DataSet4", dt3));
//             }
            ReportPrintProc(report);
            //report.Refresh();

        }
        void ReportPrint(CurveData cd)
        {
            byte pp = (byte)(cd.exWorkTepy&0x1a);
            switch (pp)
            {
                case 0x1a://全部打印
                    ReportPrint_PLK_GQ_VA(cd);
                    break;
                case 0x10://plk
                    ReportPrint_PLK(cd);
                    break;
                case 0x08://GQ
                    ReportPrint_GQ(cd);
                    break;
                case 0x02://VA
                    ReportPrint_VA(cd);
                    break;
                case 0x0a://GQ VA
                    ReportPrint_VA_GQ(cd);
                    break;
                case 0x12://PLK VA
                    ReportPrint_VA_PLK(cd);
                    break;
                case 0x18://PLK GQ
                    ReportPrint_PLK_GQ(cd);
                    break;
            }
        
        }
        //用来提供Stream对象的函数，用于LocalReport对象的Render方法的第三个参数。
        private Stream CreateStream(string name, string fileNameExtension,
            Encoding encoding, string mimeType, bool willSeek)
        {
            //如果需要将报表输出的数据保存为文件，请使用FileStream对象。
            Stream stream = new FileStream(name + "." + fileNameExtension,
          FileMode.Create);
            m_streams.Add(stream);
            return stream;
        }
        //用来记录当前打印到第几页了
        private int m_currentPageIndex;

        private void Print()
        {
            m_currentPageIndex = 0;

            if (m_streams == null || m_streams.Count == 0)
                return;
            //声明PrintDocument对象用于数据的打印
            PrintDocument printDoc = new PrintDocument();
            //指定需要使用的打印机的名称，使用空字符串""来指定默认打印机
            //printDoc.PrinterSettings.PrinterName = "";
            //判断指定的打印机是否可用
            if (!printDoc.PrinterSettings.IsValid)
            {
                MessageBox.Show("Can't find printer");
                return;
            }
            //声明PrintDocument对象的PrintPage事件，具体的打印操作需要在这个事件中处理。
            printDoc.PrintPage += new PrintPageEventHandler(PrintPage);
            //执行打印操作，Print方法将触发PrintPage事件。
            printDoc.Print();
        }
        private void PrintPage(object sender, PrintPageEventArgs ev)
        {
            //Metafile对象用来保存EMF或WMF格式的图形，
            //我们在前面将报表的内容输出为EMF图形格式的数据流。
            if (m_currentPageIndex > 0)
                return;
            Metafile pageImage =
         new Metafile(m_streams[m_currentPageIndex]);
            //Image pageImage = Image.FromFile(@"E:\temp\WindowsFormsApplication1\WindowsFormsApplication1\bin\Debug\Report1.TIF");
            ev.Graphics.DrawImage(pageImage, ev.PageBounds);
            m_currentPageIndex++;
            ev.HasMorePages = false;// = (m_currentPageIndex < m_streams.Count);
        }
        string XueHao;
        void GetInfoTable(CurveData cd, DataTable dt)
        {
            DataRow dr = dt.NewRow();
            dr["Class"] = cd.BanJi;
            dr["SteNum"] = cd.XueHao;
            XueHao = cd.XueHao;
            dr["ExNum"] = cd.ZuoWeiHao;
            dr["DT"] = DateTime.Now.ToString();
            dt.Rows.Add(dr);
        }
        void GetVATable(CurveData cd, DataTable dt)
        {
            DataRow dr = dt.NewRow();
            for (int i = 0; i < 101; i++)
            {
                dr = dt.NewRow();
                if (BytesOP.GetBit(cd.exWorkTepy, 0))//自动，则0.5V
                {
                    if(i%2==1)
                        continue;
                    dr["GQ"] = ((float)i) / 2;
                }
                else
                    dr["GQ"] = i;
                //dr["BC"] = "L1=" + (10 + 5.23).ToString();
                if (cd.bVAExist[0] && i < cd.VADataCount[0])
                    dr["紫光400nm"] = cd.VAData[0, i];
                if (cd.bVAExist[1] && i < cd.VADataCount[1])
                    dr["蓝光460nm"] = cd.VAData[1, i];
                if (cd.bVAExist[2] && i < cd.VADataCount[2])
                    dr["绿光520nm"] = cd.VAData[2, i];
                if (cd.bVAExist[3] && i < cd.VADataCount[3])
                    dr["黄光590nm"] = cd.VAData[3, i];
                if (cd.bVAExist[4] && i < cd.VADataCount[4])
                    dr["橙光603nm"] = cd.VAData[4, i];
                if (cd.bVAExist[5] && i < cd.VADataCount[5])
                    dr["红光625nm"] = cd.VAData[5, i];

                if (cd.bVAExist[0] && ((i + 1) == cd.VADataCount[0]))
                    dr["L1"] = cd.VAData[0, i];
                if (cd.bVAExist[1] && ((i + 1) == cd.VADataCount[1]))
                    dr["L2"] = cd.VAData[1, i];
                if (cd.bVAExist[2] && ((i + 1) == cd.VADataCount[2]))
                    dr["L3"] = cd.VAData[2, i];
                if (cd.bVAExist[3] && ((i + 1) == cd.VADataCount[3]))
                    dr["L4"] = cd.VAData[3, i];
                if (cd.bVAExist[4] && ((i + 1) == cd.VADataCount[4]))
                    dr["L5"] = cd.VAData[4, i];
                if (cd.bVAExist[5] && ((i + 1) == cd.VADataCount[5]))
                    dr["L6"] = cd.VAData[5, i];
                dt.Rows.Add(dr);
            }
        }
        void GetGQTable(CurveData cd, DataTable dt)
        {
            DataRow dr = dt.NewRow();
            for (int i = 0; i < 101; i++)
            {
                dr = dt.NewRow();
                if (BytesOP.GetBit(cd.exWorkTepy, 2))//自动，则0.5V
                {
                    if (i % 2 == 1)
                        continue;
                    dr["GQ"] = ((float)i) / 2;
                }
                else
                    dr["GQ"] = i;
                //dr["BC"] = "L1=" + (10 + 5.23).ToString();
                if (cd.bGQExist[0] && i < cd.GQDataCount[0])
                    dr["工作电流1mA"] = cd.GQData[0, i];
                if (cd.bGQExist[1] && i < cd.GQDataCount[1])
                    dr["工作电流2mA"] = cd.GQData[1, i];
                if (cd.bGQExist[2] && i < cd.GQDataCount[2])
                    dr["工作电流4mA"] = cd.GQData[2, i];
                if (cd.bGQExist[3] && i < cd.GQDataCount[3])
                    dr["工作电流5mA"] = cd.GQData[3, i];


                if (cd.bGQExist[0] && ((i + 1) == cd.GQDataCount[0]))
                    dr["L1"] = cd.GQData[0, i];
                if (cd.bGQExist[1] && ((i + 1) == cd.GQDataCount[1]))
                    dr["L2"] = cd.GQData[1, i];
                if (cd.bGQExist[2] && ((i + 1) == cd.GQDataCount[2]))
                    dr["L3"] = cd.GQData[2, i];
                if (cd.bGQExist[3] && ((i + 1) == cd.GQDataCount[3]))
                    dr["L4"] = cd.GQData[3, i];
                dt.Rows.Add(dr);
            }
        }
        void GetPLKTable(CurveData cd, DataTable dt)
        {
            DataRow dr = dt.NewRow();
            float[] f = new float[6] { 7.5f, 6.5f, 5.8f, 5.2f, 5.0f, 4.8f };
            for (int i = 5; i > -1; i--)
            {
                dr = dt.NewRow();
                dr["f"] = f[i];
                dr["Us"] = cd.PLKData[i];
                dr["UsLine"] = cd.PLKData[6] * f[i] + cd.PLKData[7];
                if (cd.PLKData[7] > 0)
                    dr["Line"] = string.Format("曲线方程Us={0}v+{1},计算出的普朗克常数为h={2} E-34 J·S", cd.PLKData[6], cd.PLKData[7], cd.PLKData[8]);
                else
                    dr["Line"] = string.Format("曲线方程Us={0}v{1},计算出的普朗克常数为h={2} E-34 J·S", cd.PLKData[6], cd.PLKData[7], cd.PLKData[8]);
                dt.Rows.Add(dr);
            }
        }
        void ReportPrintProc(LocalReport report)
        {
            if(bPrint)
            {
                string deviceInfo =
                                        @"<DeviceInfo>
                                     <OutputFormat>EMF</OutputFormat>
                                     <PageWidth>8.5in</PageWidth>
                                     <PageHeight>11in</PageHeight>
                                     <MarginTop>0.25in</MarginTop>
                                     <MarginLeft>0.25in</MarginLeft>
                                     <MarginRight>0.25in</MarginRight>
                                     <MarginBottom>0.25in</MarginBottom>
                                 </DeviceInfo>";
                Warning[] warnings;
                m_streams = new List<Stream>();
                report.Render("Image", deviceInfo, CreateStream,
                   out warnings);
                foreach (Stream stream in m_streams)
                    stream.Position = 0;
                Print();
                foreach (Stream stream in m_streams)
                {
                    stream.Flush();
                    stream.Close();
                    stream.Dispose();
                }
            }
            else
            {
                Warning[] warnings;
                string[] streamids;
                string mimeType;
                string encoding;
                string extension;
                string deviceInfo =
                                       @"<DeviceInfo>
                                      <OutputFormat>PDF</OutputFormat>
                                      <PageWidth>8.5in</PageWidth>
                                      <PageHeight>11in</PageHeight>
                                      <MarginTop>0in</MarginTop>
                                      <MarginLeft>0in</MarginLeft>
                                      <MarginRight>0in</MarginRight>
                                      <MarginBottom>0in</MarginBottom>
                                  </DeviceInfo>";
                byte[] bytes = report.Render(
                   "PDF", deviceInfo, out mimeType, out encoding, out extension,
                   out streamids, out warnings);
                string stmp = pathPDF;
                FileInfo f = new FileInfo(stmp + "\\1.bin");
                // 如果文件所在的文件夹不存在则创建文件夹
                if (!Directory.Exists(f.DirectoryName))
                    Directory.CreateDirectory(f.DirectoryName);

                FileStream fs = new FileStream(stmp + "/" + DateTime.Now.ToString("yyyyMMdd_hhmmss_") + XueHao + ".pdf", FileMode.Create);
                fs.Write(bytes, 0, bytes.Length);
                fs.Close();
            }
        }
    }
}
