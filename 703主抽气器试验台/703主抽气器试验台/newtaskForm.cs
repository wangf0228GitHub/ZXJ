using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib;

namespace _703主抽气器试验台
{
    public partial class newtaskForm : Form
    {
        public newtaskForm()
        {
            InitializeComponent();
        }
        DataTable NIdt;
        private void newtaskForm_Load(object sender, EventArgs e)
        {
            dataGridView1.AutoGenerateColumns = false;
            NIdt = DAL.NIChannelSettingDataDBOption.UseDataTableSelect();
            NIdt.Columns.Add("bCheck");
            for (int i = 0; i < NIdt.Rows.Count;i++ )
            {
                NIdt.Rows[i]["bCheck"] = false;
            }
            dataGridView1.DataSource = NIdt;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DAL.ExInfoData ei = new DAL.ExInfoData();
            ei.Title = textBox1.Text;
            ei.SampleRete = (int)numericUpDown1.Value;
            ei.SaveNS = (int)numericUpDown2.Value;         
            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                DataGridViewCheckBoxCell checkCell = (DataGridViewCheckBoxCell)dataGridView1.Rows[i].Cells[0];
                if (Convert.ToBoolean(checkCell.Value) == true)
                {
                    DAL.NIChannelSettingData ai = DAL.NIChannelSettingDataFactory.Construct(NIdt,i);
                    ei.NI9188Mod += (ai.ID).ToString() + "|";
                }
            }
            if (ei.NI9188Mod == "")
            {
                MessageBox.Show("未选择任何传感器");
                return;
            }
            if (ei.NI9188Mod[ei.NI9188Mod.Length - 1] == '|')
                ei.NI9188Mod = ei.NI9188Mod.Substring(0, ei.NI9188Mod.Length - 1);
            
            DAL.ExInfoDataDBOption.Insert(ei);
            this.Hide();
            taskForm f = new taskForm();
            f.ShowDialog();
            this.Show();
        }

        private void toolStripSeparator1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (toolStripSeparator1.SelectedIndex)
            {
                case 0://全选
                    for (int i = 0; i < dataGridView1.Rows.Count;i++ )
                    {
                        DataGridViewCheckBoxCell checkCell = (DataGridViewCheckBoxCell)dataGridView1.Rows[i].Cells[0];
                        checkCell.Value = true;
                    }
                    break;
                case 1://全不选
                    for (int i = 0; i < dataGridView1.Rows.Count;i++ )
                    {
                        DataGridViewCheckBoxCell checkCell = (DataGridViewCheckBoxCell)dataGridView1.Rows[i].Cells[0];
                        checkCell.Value = false;
                    }
                    break;
                case 2://上一次
                    DataTable dt = WFNetLib.ADO.SQLServerOP.DataTableSQL("select TOP 1 * from ExInfo order by id desc");
                    if (dt.Rows.Count == 0)
                    {
                        MessageBox.Show("当前是第一次试验，系统中没有上次试验的信息");
                        return;
                    }
                    DAL.ExInfoData eipre = DAL.ExInfoDataFactory.Construct(dt.Rows[0]);
                    string[] aiList = eipre.NI9188Mod.Split('|');
                    int aiIndex;
                    for (int i = 0; i < dataGridView1.Rows.Count; i++)
                    {
                        DataGridViewCheckBoxCell checkCell = (DataGridViewCheckBoxCell)dataGridView1.Rows[i].Cells[0];
                        checkCell.Value = false;
                    }
                    foreach (string ai in aiList)
                    {
                        if (int.TryParse(ai, out aiIndex))
                        {
                            DataGridViewCheckBoxCell checkCell = (DataGridViewCheckBoxCell)dataGridView1.Rows[aiIndex-1].Cells[0];
                            checkCell.Value = true;
                        }
                    }                    
                    break;
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 0 && e.RowIndex != -1)
            {
                //获取控件的值
                DataGridViewCheckBoxCell checkCell = (DataGridViewCheckBoxCell)this.dataGridView1.Rows[e.RowIndex].Cells[0];
                Boolean flag = Convert.ToBoolean(checkCell.Value);
                if (flag == true)
                {
                    checkCell.Value = false;
                }
                else
                {
                    checkCell.Value = true;
                }
            } 
        }
    }
}
