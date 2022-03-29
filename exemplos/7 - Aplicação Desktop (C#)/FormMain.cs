using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Desktop
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            this.lblTexto.Text = txtValue.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.lblTexto.Text = "";
            this.txtValue.Text = "";
        }
    }
}
