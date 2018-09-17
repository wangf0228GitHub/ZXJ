namespace 地声数据监测
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            System.Windows.Forms.ListViewGroup listViewGroup41 = new System.Windows.Forms.ListViewGroup("温度传感器", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup42 = new System.Windows.Forms.ListViewGroup("MS8607", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup43 = new System.Windows.Forms.ListViewGroup("电子罗盘", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup44 = new System.Windows.Forms.ListViewGroup("授时", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup45 = new System.Windows.Forms.ListViewGroup("光源", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup46 = new System.Windows.Forms.ListViewGroup("电源", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup47 = new System.Windows.Forms.ListViewGroup("IO状态", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup48 = new System.Windows.Forms.ListViewGroup("通信错误统计", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewItem listViewItem146 = new System.Windows.Forms.ListViewItem(new string[] {
            "温度",
            "xx.xx",
            "℃"}, -1);
            System.Windows.Forms.ListViewItem listViewItem147 = new System.Windows.Forms.ListViewItem(new string[] {
            "偏航角",
            "xxx.xx",
            "度"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem148 = new System.Windows.Forms.ListViewItem(new string[] {
            "俯仰角",
            "xxx.xx",
            "度"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem149 = new System.Windows.Forms.ListViewItem(new string[] {
            "翻滚角",
            "xxx.xx",
            "度"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem150 = new System.Windows.Forms.ListViewItem(new string[] {
            "时间",
            ""}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem151 = new System.Windows.Forms.ListViewItem(new string[] {
            "日期",
            ""}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem152 = new System.Windows.Forms.ListViewItem(new string[] {
            "温度",
            "xx.xx",
            "℃"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255))))), null);
            System.Windows.Forms.ListViewItem listViewItem153 = new System.Windows.Forms.ListViewItem(new string[] {
            "压力",
            "xxxx.xx",
            "mbar"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255))))), null);
            System.Windows.Forms.ListViewItem listViewItem154 = new System.Windows.Forms.ListViewItem(new string[] {
            "相对湿度",
            "xx.xx",
            "%RH"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255))))), null);
            System.Windows.Forms.ListViewItem listViewItem155 = new System.Windows.Forms.ListViewItem(new string[] {
            "温度传感器",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem156 = new System.Windows.Forms.ListViewItem(new string[] {
            "电子罗盘",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem157 = new System.Windows.Forms.ListViewItem(new string[] {
            "光源",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem158 = new System.Windows.Forms.ListViewItem(new string[] {
            "授时模块",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem159 = new System.Windows.Forms.ListViewItem(new string[] {
            "MS8607",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem160 = new System.Windows.Forms.ListViewItem(new string[] {
            "光电流",
            "xxxx",
            "mA"}, -1);
            System.Windows.Forms.ListViewItem listViewItem161 = new System.Windows.Forms.ListViewItem(new string[] {
            "状态值",
            "xxxx"}, -1);
            System.Windows.Forms.ListViewItem listViewItem162 = new System.Windows.Forms.ListViewItem(new string[] {
            "激光器稳定",
            "是"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.Lime, null);
            System.Windows.Forms.ListViewItem listViewItem163 = new System.Windows.Forms.ListViewItem(new string[] {
            "主板温度报警(<-5 or >75)",
            "否"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.Lime, null);
            System.Windows.Forms.ListViewItem listViewItem164 = new System.Windows.Forms.ListViewItem(new string[] {
            "激光器温度报警(>80)",
            "否"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.Lime, null);
            System.Windows.Forms.ListViewItem listViewItem165 = new System.Windows.Forms.ListViewItem(new string[] {
            "漏水1",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem166 = new System.Windows.Forms.ListViewItem(new string[] {
            "漏水2",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem167 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO1",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem168 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO2",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem169 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO3",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem170 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO4",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem171 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO5",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem172 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO6",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem173 = new System.Windows.Forms.ListViewItem(new string[] {
            "辅助传感器电源",
            "打开"}, -1);
            System.Windows.Forms.ListViewItem listViewItem174 = new System.Windows.Forms.ListViewItem(new string[] {
            "解调电路电源",
            "打开"}, -1);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.tbPort = new System.Windows.Forms.ToolStripTextBox();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.toolStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1,
            this.toolStripButton2,
            this.toolStripSeparator1,
            this.toolStripLabel1,
            this.tbPort,
            this.toolStripSeparator2,
            this.toolStripButton3});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(787, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(36, 22);
            this.toolStripButton1.Text = "停止";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton2.Enabled = false;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(60, 22);
            this.toolStripButton2.Text = "系统设定";
            this.toolStripButton2.Click += new System.EventHandler(this.toolStripButton2_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(32, 22);
            this.toolStripLabel1.Text = "端口";
            // 
            // tbPort
            // 
            this.tbPort.Name = "tbPort";
            this.tbPort.Size = new System.Drawing.Size(100, 25);
            this.tbPort.Text = "6000";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 25);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.listView1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.textBox1);
            this.splitContainer1.Size = new System.Drawing.Size(787, 755);
            this.splitContainer1.SplitterDistance = 415;
            this.splitContainer1.TabIndex = 1;
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3});
            this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            listViewGroup41.Header = "温度传感器";
            listViewGroup41.Name = "listViewGroup1";
            listViewGroup42.Header = "MS8607";
            listViewGroup42.Name = "listViewGroup2";
            listViewGroup43.Header = "电子罗盘";
            listViewGroup43.Name = "listViewGroup3";
            listViewGroup44.Header = "授时";
            listViewGroup44.Name = "listViewGroup4";
            listViewGroup45.Header = "光源";
            listViewGroup45.Name = "listViewGroup6";
            listViewGroup46.Header = "电源";
            listViewGroup46.Name = "listViewGroup8";
            listViewGroup47.Header = "IO状态";
            listViewGroup47.Name = "listViewGroup7";
            listViewGroup48.Header = "通信错误统计";
            listViewGroup48.Name = "listViewGroup5";
            this.listView1.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup41,
            listViewGroup42,
            listViewGroup43,
            listViewGroup44,
            listViewGroup45,
            listViewGroup46,
            listViewGroup47,
            listViewGroup48});
            listViewItem146.Group = listViewGroup41;
            listViewItem146.StateImageIndex = 0;
            listViewItem147.Group = listViewGroup43;
            listViewItem147.StateImageIndex = 0;
            listViewItem148.Group = listViewGroup43;
            listViewItem148.StateImageIndex = 0;
            listViewItem149.Group = listViewGroup43;
            listViewItem149.StateImageIndex = 0;
            listViewItem150.Group = listViewGroup44;
            listViewItem150.StateImageIndex = 0;
            listViewItem151.Group = listViewGroup44;
            listViewItem151.StateImageIndex = 0;
            listViewItem152.Group = listViewGroup42;
            listViewItem152.StateImageIndex = 0;
            listViewItem153.Group = listViewGroup42;
            listViewItem153.StateImageIndex = 0;
            listViewItem154.Group = listViewGroup42;
            listViewItem154.StateImageIndex = 0;
            listViewItem155.Group = listViewGroup48;
            listViewItem155.StateImageIndex = 0;
            listViewItem156.Group = listViewGroup48;
            listViewItem156.StateImageIndex = 0;
            listViewItem157.Group = listViewGroup48;
            listViewItem157.StateImageIndex = 0;
            listViewItem158.Group = listViewGroup48;
            listViewItem158.StateImageIndex = 0;
            listViewItem159.Group = listViewGroup48;
            listViewItem159.StateImageIndex = 0;
            listViewItem160.Group = listViewGroup45;
            listViewItem160.StateImageIndex = 0;
            listViewItem161.Group = listViewGroup45;
            listViewItem161.StateImageIndex = 0;
            listViewItem162.Group = listViewGroup45;
            listViewItem162.StateImageIndex = 0;
            listViewItem163.Group = listViewGroup45;
            listViewItem164.Group = listViewGroup45;
            listViewItem165.Group = listViewGroup47;
            listViewItem166.Group = listViewGroup47;
            listViewItem167.Group = listViewGroup47;
            listViewItem168.Group = listViewGroup47;
            listViewItem169.Group = listViewGroup47;
            listViewItem170.Group = listViewGroup47;
            listViewItem171.Group = listViewGroup47;
            listViewItem172.Group = listViewGroup47;
            listViewItem173.Group = listViewGroup46;
            listViewItem174.Group = listViewGroup46;
            this.listView1.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem146,
            listViewItem147,
            listViewItem148,
            listViewItem149,
            listViewItem150,
            listViewItem151,
            listViewItem152,
            listViewItem153,
            listViewItem154,
            listViewItem155,
            listViewItem156,
            listViewItem157,
            listViewItem158,
            listViewItem159,
            listViewItem160,
            listViewItem161,
            listViewItem162,
            listViewItem163,
            listViewItem164,
            listViewItem165,
            listViewItem166,
            listViewItem167,
            listViewItem168,
            listViewItem169,
            listViewItem170,
            listViewItem171,
            listViewItem172,
            listViewItem173,
            listViewItem174});
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.MultiSelect = false;
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(415, 755);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.Resize += new System.EventHandler(this.listView1_Resize);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "物理量";
            this.columnHeader1.Width = 173;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "数值";
            this.columnHeader2.Width = 175;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "单位";
            // 
            // textBox1
            // 
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox1.Location = new System.Drawing.Point(0, 0);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox1.Size = new System.Drawing.Size(368, 755);
            this.textBox1.TabIndex = 0;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton3.Enabled = false;
            this.toolStripButton3.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton3.Image")));
            this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Size = new System.Drawing.Size(84, 22);
            this.toolStripButton3.Text = "读取光源状态";
            this.toolStripButton3.Click += new System.EventHandler(this.toolStripButton3_Click);
            // 
            // timer2
            // 
            this.timer2.Interval = 1000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(787, 780);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.toolStrip1);
            this.Name = "Form1";
            this.Text = "地声数据监测";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripLabel toolStripLabel1;
		private System.Windows.Forms.ToolStripTextBox tbPort;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton toolStripButton3;
        private System.Windows.Forms.Timer timer2;
    }
}

