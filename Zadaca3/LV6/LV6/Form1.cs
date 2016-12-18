using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LV6
{
    public partial class Form1 : Form
    {
        protected override void OnPaint(PaintEventArgs e)
        {
            Font f1 = new Font("Times New Roman", 12, FontStyle.Bold | FontStyle.Italic);
            Font f2 = new Font("Arial", 20, FontStyle.Underline | FontStyle.Italic);
            Font f3 = new Font("Courier New", 28, FontStyle.Italic);
            Font f4 = new Font("Tahoma", 34, FontStyle.Strikeout);
            e.Graphics.DrawString("Razvoj programskih rješenja.", f1, new SolidBrush(ForeColor), 0, 0);
            e.Graphics.DrawString("Razvoj programskih rješenja.", f2, new SolidBrush(ForeColor), 0, 20);
            e.Graphics.DrawString("Razvoj programskih rješenja.", f3, new SolidBrush(ForeColor), 0, 60);
            e.Graphics.DrawString("Razvoj programskih rješenja.", f4, new SolidBrush(ForeColor), 0, 100);
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
        }
    }
}
