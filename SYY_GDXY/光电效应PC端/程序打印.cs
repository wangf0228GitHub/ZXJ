using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace 光电效应PC端
{
    public partial class Form1 : Form
    {
        void ProgramPrint()
        {
            //             PrintController printController = new StandardPrintController();
            //             printDocument.PrintController = printController;
            printDocument.Print();
        }
        private void printDocument_PrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            e.Graphics.DrawString("光电效应实验报告", new Font(new FontFamily("宋体"), 16), System.Drawing.Brushes.Black,350, 50);
            e.Graphics.DrawRectangle(new Pen(Color.Black, 1), 65, 100,700,100);
            e.Graphics.DrawLine(new Pen(Color.Black, 1), 65, 150, 765, 150);
            e.Graphics.DrawLine(new Pen(Color.Black, 1), 298, 100, 298, 200);
            e.Graphics.DrawLine(new Pen(Color.Black, 1), 531, 100, 531, 200);

            e.Graphics.DrawString("座位号", new Font(new FontFamily("宋体"), 14), System.Drawing.Brushes.Black, 160, 117);
        }
    }
}
