using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace AC4Analysis
{
    public partial class Note : Form
    {
        public Note()
        {
            InitializeComponent();
        }
        public string DataAdd = "";
        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public string DataNote = "";
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
                return;
            DataNote = textBox1.Text;
            Notes.Set(DataAdd, DataNote);
            Notes.Save();
            this.Close();
        }
    }
}
