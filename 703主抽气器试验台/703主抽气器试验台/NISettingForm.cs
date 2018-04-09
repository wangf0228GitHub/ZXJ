using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace _703主抽气器试验台
{
    public partial class NISettingForm : Form
    {
        public NISettingForm()
        {
            InitializeComponent();
        }

        private void NISettingForm_Load(object sender, EventArgs e)
        {
            dataGridView1.AutoGenerateColumns = false;
            DataTable dt = DAL.NIChannelSettingDataDBOption.DataTableSelect();
            dataGridView1.DataSource = dt;
        }

        private void dataGridView1_DoubleClick(object sender, EventArgs e)
        {
            
        }

        private void dataGridView1_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex < 0 || e.RowIndex > 63)
                return;
            Form f = new NIChannelSetForm(e.RowIndex+1);
            if (f.ShowDialog() == DialogResult.OK)
            {
                DataTable dt = DAL.NIChannelSettingDataDBOption.DataTableSelect();
                dataGridView1.DataSource = dt;
            }
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                MessageBox.Show("请先选中某一通道，或双击某一通道即可设定");
            }
            Form f = new NIChannelSetForm(dataGridView1.CurrentRow.Index + 1);
            if (f.ShowDialog() == DialogResult.OK)
            {
                DataTable dt = DAL.NIChannelSettingDataDBOption.DataTableSelect();
                dataGridView1.DataSource = dt;
            }
        }
    }
}
