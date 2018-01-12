namespace 光电效应PC端
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
            this.notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.printDocument = new System.Drawing.Printing.PrintDocument();
            this.button1 = new System.Windows.Forms.Button();
            this.StudentBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.reportDataSet1 = new 光电效应PC端.reportDataSet();
            this.CurveBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.Curve1BindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.Curve2BindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.reportViewer1 = new Microsoft.Reporting.WinForms.ReportViewer();
            ((System.ComponentModel.ISupportInitialize)(this.StudentBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.reportDataSet1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurveBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Curve1BindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Curve2BindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // notifyIcon
            // 
            this.notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon.Icon")));
            this.notifyIcon.Text = "notifyIcon1";
            this.notifyIcon.Visible = true;
            this.notifyIcon.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon_MouseDoubleClick);
            // 
            // printDocument
            // 
            this.printDocument.PrintPage += new System.Drawing.Printing.PrintPageEventHandler(this.printDocument_PrintPage);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(307, 255);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // StudentBindingSource
            // 
            this.StudentBindingSource.DataMember = "Student";
            this.StudentBindingSource.DataSource = this.reportDataSet1;
            // 
            // reportDataSet1
            // 
            this.reportDataSet1.DataSetName = "reportDataSet";
            this.reportDataSet1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // CurveBindingSource
            // 
            this.CurveBindingSource.DataMember = "Curve";
            this.CurveBindingSource.DataSource = this.reportDataSet1;
            // 
            // textBox1
            // 
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox1.Location = new System.Drawing.Point(0, 0);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox1.Size = new System.Drawing.Size(394, 290);
            this.textBox1.TabIndex = 1;
            // 
            // Curve1BindingSource
            // 
            this.Curve1BindingSource.DataMember = "Curve1";
            this.Curve1BindingSource.DataSource = this.reportDataSet1;
            // 
            // Curve2BindingSource
            // 
            this.Curve2BindingSource.DataMember = "Curve2";
            this.Curve2BindingSource.DataSource = this.reportDataSet1;
            // 
            // reportViewer1
            // 
            this.reportViewer1.Location = new System.Drawing.Point(12, 32);
            this.reportViewer1.Name = "reportViewer1";
            this.reportViewer1.Size = new System.Drawing.Size(206, 98);
            this.reportViewer1.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(394, 290);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.reportViewer1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.StudentBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.reportDataSet1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurveBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Curve1BindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Curve2BindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon;
        private System.Drawing.Printing.PrintDocument printDocument;
        private System.Windows.Forms.Button button1;
        private reportDataSet reportDataSet1;
        private System.Windows.Forms.BindingSource StudentBindingSource;
        private System.Windows.Forms.BindingSource CurveBindingSource;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.BindingSource Curve1BindingSource;
        private System.Windows.Forms.BindingSource Curve2BindingSource;
        private Microsoft.Reporting.WinForms.ReportViewer reportViewer1;
    }
}

