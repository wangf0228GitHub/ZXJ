﻿namespace 地声数据监测
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
            System.Windows.Forms.ListViewGroup listViewGroup9 = new System.Windows.Forms.ListViewGroup("温度传感器", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup10 = new System.Windows.Forms.ListViewGroup("MS8607", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup11 = new System.Windows.Forms.ListViewGroup("电子罗盘", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup12 = new System.Windows.Forms.ListViewGroup("授时", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup13 = new System.Windows.Forms.ListViewGroup("光源", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup14 = new System.Windows.Forms.ListViewGroup("电源", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup15 = new System.Windows.Forms.ListViewGroup("IO状态", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup16 = new System.Windows.Forms.ListViewGroup("通信错误统计", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewItem listViewItem30 = new System.Windows.Forms.ListViewItem(new string[] {
            "温度",
            "xx.xx",
            "℃"}, -1);
            System.Windows.Forms.ListViewItem listViewItem31 = new System.Windows.Forms.ListViewItem(new string[] {
            "偏航角",
            "xxx.xx",
            "度"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem32 = new System.Windows.Forms.ListViewItem(new string[] {
            "俯仰角",
            "xxx.xx",
            "度"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem33 = new System.Windows.Forms.ListViewItem(new string[] {
            "翻滚角",
            "xxx.xx",
            "度"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem34 = new System.Windows.Forms.ListViewItem(new string[] {
            "时间",
            ""}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem35 = new System.Windows.Forms.ListViewItem(new string[] {
            "日期",
            ""}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192))))), null);
            System.Windows.Forms.ListViewItem listViewItem36 = new System.Windows.Forms.ListViewItem(new string[] {
            "温度",
            "xx.xx",
            "℃"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255))))), null);
            System.Windows.Forms.ListViewItem listViewItem37 = new System.Windows.Forms.ListViewItem(new string[] {
            "压力",
            "xxxx.xx",
            "mbar"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255))))), null);
            System.Windows.Forms.ListViewItem listViewItem38 = new System.Windows.Forms.ListViewItem(new string[] {
            "相对湿度",
            "xx.xx",
            "%RH"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255))))), null);
            System.Windows.Forms.ListViewItem listViewItem39 = new System.Windows.Forms.ListViewItem(new string[] {
            "温度传感器",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem40 = new System.Windows.Forms.ListViewItem(new string[] {
            "电子罗盘",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem41 = new System.Windows.Forms.ListViewItem(new string[] {
            "光源",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem42 = new System.Windows.Forms.ListViewItem(new string[] {
            "授时模块",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem43 = new System.Windows.Forms.ListViewItem(new string[] {
            "MS8607",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem44 = new System.Windows.Forms.ListViewItem(new string[] {
            "光电流",
            "xxxx",
            "mA"}, -1);
            System.Windows.Forms.ListViewItem listViewItem45 = new System.Windows.Forms.ListViewItem(new string[] {
            "状态值",
            "xxxx"}, -1);
            System.Windows.Forms.ListViewItem listViewItem46 = new System.Windows.Forms.ListViewItem(new string[] {
            "激光器稳定",
            "是"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.Lime, null);
            System.Windows.Forms.ListViewItem listViewItem47 = new System.Windows.Forms.ListViewItem(new string[] {
            "主板温度报警(<-5 or >75)",
            "否"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.Lime, null);
            System.Windows.Forms.ListViewItem listViewItem48 = new System.Windows.Forms.ListViewItem(new string[] {
            "激光器温度报警(>80)",
            "否"}, -1, System.Drawing.Color.Empty, System.Drawing.Color.Lime, null);
            System.Windows.Forms.ListViewItem listViewItem49 = new System.Windows.Forms.ListViewItem(new string[] {
            "漏水1",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem50 = new System.Windows.Forms.ListViewItem(new string[] {
            "漏水2",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem51 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO1",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem52 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO2",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem53 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO3",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem54 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO4",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem55 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO5",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem56 = new System.Windows.Forms.ListViewItem(new string[] {
            "备用IO6",
            "1"}, -1);
            System.Windows.Forms.ListViewItem listViewItem57 = new System.Windows.Forms.ListViewItem(new string[] {
            "辅助传感器电源",
            "打开"}, -1);
            System.Windows.Forms.ListViewItem listViewItem58 = new System.Windows.Forms.ListViewItem(new string[] {
            "解调电路电源",
            "打开"}, -1);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.tbPort = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
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
            this.toolStrip1.Size = new System.Drawing.Size(1049, 27);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(43, 24);
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
            this.toolStripButton2.Size = new System.Drawing.Size(73, 24);
            this.toolStripButton2.Text = "系统设定";
            this.toolStripButton2.Click += new System.EventHandler(this.toolStripButton2_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(39, 24);
            this.toolStripLabel1.Text = "端口";
            // 
            // tbPort
            // 
            this.tbPort.Name = "tbPort";
            this.tbPort.Size = new System.Drawing.Size(132, 27);
            this.tbPort.Text = "6000";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 27);
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton3.Enabled = false;
            this.toolStripButton3.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton3.Image")));
            this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Size = new System.Drawing.Size(103, 24);
            this.toolStripButton3.Text = "读取光源状态";
            this.toolStripButton3.Click += new System.EventHandler(this.toolStripButton3_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 27);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.listView1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.textBox1);
            this.splitContainer1.Size = new System.Drawing.Size(1049, 850);
            this.splitContainer1.SplitterDistance = 415;
            this.splitContainer1.SplitterWidth = 5;
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
            listViewGroup9.Header = "温度传感器";
            listViewGroup9.Name = "listViewGroup1";
            listViewGroup10.Header = "MS8607";
            listViewGroup10.Name = "listViewGroup2";
            listViewGroup11.Header = "电子罗盘";
            listViewGroup11.Name = "listViewGroup3";
            listViewGroup12.Header = "授时";
            listViewGroup12.Name = "listViewGroup4";
            listViewGroup13.Header = "光源";
            listViewGroup13.Name = "listViewGroup6";
            listViewGroup14.Header = "电源";
            listViewGroup14.Name = "listViewGroup8";
            listViewGroup15.Header = "IO状态";
            listViewGroup15.Name = "listViewGroup7";
            listViewGroup16.Header = "通信错误统计";
            listViewGroup16.Name = "listViewGroup5";
            this.listView1.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup9,
            listViewGroup10,
            listViewGroup11,
            listViewGroup12,
            listViewGroup13,
            listViewGroup14,
            listViewGroup15,
            listViewGroup16});
            listViewItem30.Group = listViewGroup9;
            listViewItem30.StateImageIndex = 0;
            listViewItem31.Group = listViewGroup11;
            listViewItem31.StateImageIndex = 0;
            listViewItem32.Group = listViewGroup11;
            listViewItem32.StateImageIndex = 0;
            listViewItem33.Group = listViewGroup11;
            listViewItem33.StateImageIndex = 0;
            listViewItem34.Group = listViewGroup12;
            listViewItem34.StateImageIndex = 0;
            listViewItem35.Group = listViewGroup12;
            listViewItem35.StateImageIndex = 0;
            listViewItem36.Group = listViewGroup10;
            listViewItem36.StateImageIndex = 0;
            listViewItem37.Group = listViewGroup10;
            listViewItem37.StateImageIndex = 0;
            listViewItem38.Group = listViewGroup10;
            listViewItem38.StateImageIndex = 0;
            listViewItem39.Group = listViewGroup16;
            listViewItem39.StateImageIndex = 0;
            listViewItem40.Group = listViewGroup16;
            listViewItem40.StateImageIndex = 0;
            listViewItem41.Group = listViewGroup16;
            listViewItem41.StateImageIndex = 0;
            listViewItem42.Group = listViewGroup16;
            listViewItem42.StateImageIndex = 0;
            listViewItem43.Group = listViewGroup16;
            listViewItem43.StateImageIndex = 0;
            listViewItem44.Group = listViewGroup13;
            listViewItem44.StateImageIndex = 0;
            listViewItem45.Group = listViewGroup13;
            listViewItem45.StateImageIndex = 0;
            listViewItem46.Group = listViewGroup13;
            listViewItem46.StateImageIndex = 0;
            listViewItem47.Group = listViewGroup13;
            listViewItem48.Group = listViewGroup13;
            listViewItem49.Group = listViewGroup15;
            listViewItem50.Group = listViewGroup15;
            listViewItem51.Group = listViewGroup15;
            listViewItem52.Group = listViewGroup15;
            listViewItem53.Group = listViewGroup15;
            listViewItem54.Group = listViewGroup15;
            listViewItem55.Group = listViewGroup15;
            listViewItem56.Group = listViewGroup15;
            listViewItem57.Group = listViewGroup14;
            listViewItem58.Group = listViewGroup14;
            this.listView1.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem30,
            listViewItem31,
            listViewItem32,
            listViewItem33,
            listViewItem34,
            listViewItem35,
            listViewItem36,
            listViewItem37,
            listViewItem38,
            listViewItem39,
            listViewItem40,
            listViewItem41,
            listViewItem42,
            listViewItem43,
            listViewItem44,
            listViewItem45,
            listViewItem46,
            listViewItem47,
            listViewItem48,
            listViewItem49,
            listViewItem50,
            listViewItem51,
            listViewItem52,
            listViewItem53,
            listViewItem54,
            listViewItem55,
            listViewItem56,
            listViewItem57,
            listViewItem58});
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.listView1.MultiSelect = false;
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(415, 850);
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
            this.textBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox1.Size = new System.Drawing.Size(629, 850);
            this.textBox1.TabIndex = 0;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // timer2
            // 
            this.timer2.Interval = 50000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1049, 877);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.toolStrip1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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

