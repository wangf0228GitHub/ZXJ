using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.MyControls;
using WFOffice2007;
using DAL;

namespace _703主抽气器试验台
{
    public partial class exportForm : Form
    {
        public exportForm()
        {
            InitializeComponent();
        }
        ToolStripDateTimePicker startTime;
        ToolStripDateTimePicker endTime;
        DataTable exDT;
        private void exportForm_Load(object sender, EventArgs e)
        {            
            startTime = new ToolStripDateTimePicker();
            startTime.Width = 130;
            endTime = new ToolStripDateTimePicker();
            endTime.Width = 130;
            toolStrip1.Items.Insert(6, startTime);
            toolStrip1.Items.Insert(8, endTime);
            startTime.Control.Format = DateTimePickerFormat.Custom;
            startTime.Control.CustomFormat = "yyyy-MM-dd";
            endTime.Control.Format = DateTimePickerFormat.Custom;
            endTime.Control.CustomFormat = "yyyy-MM-dd";
            dataGridView1.AutoGenerateColumns = false;
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            exDT = DAL.ExInfoDataDBOption.DataTableSelect();
            dataGridView1.DataSource = exDT;
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            string strSQL = "select * from ExInfo where Title like '%" + toolStripTextBox1.Text + "%'";
            exDT = WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            dataGridView1.DataSource = exDT;
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            string strSQL = "select * from ExInfo where ETime BETWEEN '" + startTime.Value.ToString("yyyyMMdd") + "' AND '" + endTime.Value.AddDays(1).ToString("yyyyMMdd") + "'";
            exDT = WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            dataGridView1.DataSource = exDT;
        }
        ExcelExport ExcelEx;
        DataTable exData;
        DataTable aidt;
        DAL.ExInfoData exInfo;
        string[] aiNameList;
        private void dataGridView1_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex < 0)
                return;
            exInfo = DAL.ExInfoDataFactory.Construct(exDT.Rows[e.RowIndex]);
            List<DAL.NIChannelSettingData> aiList = new List<DAL.NIChannelSettingData>();
            aiNameList = exInfo.NI9188Mod.Split('|');
            string strSQL = "select * from  NIChannelSetting where ( ";
            foreach (string ai in aiNameList)
            {
                strSQL += "ID=" + ai + " OR ";
            }
            strSQL = strSQL.Substring(0, strSQL.Length - 4);
            strSQL += ")";
            aidt = WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            for (int i = 0; i < aidt.Rows.Count; i++)
            {
                DAL.NIChannelSettingData ai = DAL.NIChannelSettingDataFactory.Construct(aidt.Rows[i]);
                aiList.Add(ai);
            }
            strSQL = "select * from  ExData where ExID=" + exInfo.ID.ToString();
            exData = WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            ExcelEx = new ExcelExport(exData.Rows.Count);
            ExcelEx.ExcelWorkbookCallbackProc = new ExcelExport.ExcelWorkbookCallback(ExcelWorkbookCallbackProc);
            ExcelEx.ExcelExportProc();
        }
        private bool ExcelWorkbookCallbackProc(Microsoft.Office.Interop.Excel.Workbook wBook, int index)
        {
            Microsoft.Office.Interop.Excel.Worksheet wSheet;            
            Microsoft.Office.Interop.Excel.Range dr;
            if (index == -1)
            {
                wBook.Worksheets.Add();
                wBook.Worksheets.Add();
                for (int i = 0; i < wBook.Worksheets.Count - 2; i++)
                {
                    wSheet = (Microsoft.Office.Interop.Excel.Worksheet)wBook.Worksheets[i + 1];
                    wSheet.Delete();
                }
                wSheet = (Microsoft.Office.Interop.Excel.Worksheet)wBook.Worksheets[1];
                wSheet.Name = "试验信息";
                wSheet.Cells[1, 1] = "试验名称";
                wSheet.Cells[2, 1] = "采样率";
                wSheet.Cells[3, 1] = "存储间隔";
                wSheet.Cells[4, 1] = "试验时间";
                wSheet.Cells[5, 1] = "检测传感器:";
                dr = wSheet.get_Range("A1", "A5");
                dr.Interior.Color = System.Drawing.ColorTranslator.ToOle(System.Drawing.Color.DarkOrange);
                dr.Interior.Pattern = Microsoft.Office.Interop.Excel.XlPattern.xlPatternSolid;
                wSheet.Cells[1, 2] = exInfo.Title;
                wSheet.Cells[2, 2] = exInfo.SampleRete.ToString()+" Hz";
                wSheet.Cells[3, 2] = exInfo.SaveNS.ToString()+" s";
                wSheet.Cells[4, 2] = exInfo.ETime.ToString();
                dr = wSheet.get_Range("B1", "B4");
                //wSheet.Cells[5, 2] = "检测传感器";
                wSheet.Cells[6, 1] = "传感器名称";
                wSheet.Cells[6, 2] = "工位号";
                wSheet.Cells[6, 3] = "安装位置";
                wSheet.Cells[6, 4] = "报警下限";
                wSheet.Cells[6, 5] = "报警上限";
                wSheet.Cells[6, 6] = "物理量单位";
                dr = wSheet.get_Range("A6", "F6");
                dr.Interior.Color = System.Drawing.ColorTranslator.ToOle(System.Drawing.Color.Aqua);
                dr.Interior.Pattern = Microsoft.Office.Interop.Excel.XlPattern.xlPatternSolid;
                dr.ColumnWidth = 15;
                int xx=7;
                foreach (DataRow aidr in aidt.Rows)
                {
                    wSheet.Cells[xx, 1] = aidr["名称"];
                    wSheet.Cells[xx, 2] = aidr["工位号"];
                    wSheet.Cells[xx, 3] = aidr["安装位置"];
                    wSheet.Cells[xx, 4] = aidr["最小值"];
                    wSheet.Cells[xx, 5] = aidr["最大值"];
                    wSheet.Cells[xx, 6] = aidr["物理量单位"];
                    xx++;
                }
                dr = wSheet.get_Range("A1", "F"+(7+aidt.Rows.Count).ToString());
                dr.Columns.AutoFit();
                dr.HorizontalAlignment = Microsoft.Office.Interop.Excel.XlHAlign.xlHAlignCenter;
                dr.Borders.LineStyle = Microsoft.Office.Interop.Excel.XlLineStyle.xlContinuous;


                wSheet = (Microsoft.Office.Interop.Excel.Worksheet)wBook.Worksheets[2];
                wSheet.Name = "试验数据";
                wSheet.Cells[3, 1] = "序号";
                wSheet.Cells[3, 2] = "时间";
                xx = 3;
                foreach (DataRow aidr in aidt.Rows)
                {
                    wSheet.Cells[1, xx] = aidr["名称"] + "(" + aidr["物理量单位"] + ")";
                    wSheet.Cells[2, xx] = aidr["工位号"];
                    wSheet.Cells[3, xx] = aidr["安装位置"];
                    xx++;
                }
                dr = wSheet.get_Range("A1", "BN3");
                dr.Columns.AutoFit();
                dr.HorizontalAlignment = Microsoft.Office.Interop.Excel.XlHAlign.xlHAlignCenter;
                //dr.Borders.LineStyle = Microsoft.Office.Interop.Excel.XlLineStyle.xlContinuous;
                dr.Interior.Color = System.Drawing.ColorTranslator.ToOle(System.Drawing.Color.Aqua);
                dr.Interior.Pattern = Microsoft.Office.Interop.Excel.XlPattern.xlPatternSolid;
            }
            else if (index == int.MaxValue)
            {
                wSheet = (Microsoft.Office.Interop.Excel.Worksheet)wBook.Worksheets[2];
                dr = wSheet.get_Range("A1", "BN3" + (exData.Rows.Count + 1).ToString());
                dr.Columns.AutoFit();
                dr.HorizontalAlignment = Microsoft.Office.Interop.Excel.XlHAlign.xlHAlignCenter;
                //dr.Borders.LineStyle = Microsoft.Office.Interop.Excel.XlLineStyle.xlContinuous;
            }
            else
            {
                wSheet = (Microsoft.Office.Interop.Excel.Worksheet)wBook.Worksheets[2];
                ExDataData ex = ExDataDataFactory.Construct(exData, index);
                wSheet.Cells[4 + index, 1] = (index + 1).ToString();
                wSheet.Cells[4 + index, 2] = ex.DataTime.ToString();
                double[] vs=new double[64];
                for(int i=0;i<64;i++)
                {
                    vs[i]=double.Parse(exData.Rows[index][2+i].ToString());
                }
                int aiNum;
                for(int i=0;i<aiNameList.Length;i++)
                {
                    aiNum = int.Parse(aiNameList[i]);
                    wSheet.Cells[4 + index, 3+i] = vs[aiNum-1];
                }
            }
            return true;
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                MessageBox.Show("请选中某个试验!!!");
                return;
            }
            exInfo = DAL.ExInfoDataFactory.Construct(exDT.Rows[dataGridView1.SelectedRows[0].Index]);
            List<DAL.NIChannelSettingData> aiList = new List<DAL.NIChannelSettingData>();
            aiNameList = exInfo.NI9188Mod.Split('|');
            string strSQL = "select * from  NIChannelSetting where ( ";
            foreach (string ai in aiNameList)
            {
                strSQL += "ID=" + ai + " OR ";
            }
            strSQL = strSQL.Substring(0, strSQL.Length - 4);
            strSQL += ")";
            aidt = WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            for (int i = 0; i < aidt.Rows.Count; i++)
            {
                DAL.NIChannelSettingData ai = DAL.NIChannelSettingDataFactory.Construct(aidt.Rows[i]);
                aiList.Add(ai);
            }
            strSQL = "select * from  ExData where ExID=" + exInfo.ID.ToString();
            exData = WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            ExcelEx = new ExcelExport(exData.Rows.Count);
            ExcelEx.ExcelWorkbookCallbackProc = new ExcelExport.ExcelWorkbookCallback(ExcelWorkbookCallbackProc);
            ExcelEx.ExcelExportProc();
        }

        private void toolStripButton5_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                MessageBox.Show("请选中某个试验!!!");
                return;
            }            
            if (MessageBox.Show("删除试验后，数据无法恢复，确认继续删除？", "删除数据后将无法恢复", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                return;
            ExInfoData exInfo1 = DAL.ExInfoDataFactory.Construct(exDT.Rows[dataGridView1.SelectedRows[0].Index]);
            DAL.ExInfoDataDBOption.Delete(exInfo1);
            string strSQL = "delete from  ExData where ExID="+exInfo1.ID;            
            WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            exDT.Rows.RemoveAt(dataGridView1.SelectedRows[0].Index);
            MessageBox.Show("删除成功");
        }
    }
}
