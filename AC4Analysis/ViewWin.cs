using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace AC4Analysis
{
    public partial class ViewWin : Form
    {
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Perspective(float Fov);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Orthogonal(float w, float h);
        public ViewWin()
        {
            InitializeComponent();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            float Fov, Height, Width;
            if(rbView1.Checked)
            {
                if (float.TryParse(tbFov.Text, out Fov) == false)
                {
                    MessageBox.Show("Must number only");
                }
                else
                {
                    Perspective(Fov);
                }
            }
            if (rbView2.Checked)
            {
                if (float.TryParse(tbHeight.Text, out Height) == false)
                {
                    MessageBox.Show("Must number only");
                    return;
                }
                if (float.TryParse(tbWidth.Text, out Width) == false)
                {
                    MessageBox.Show("Must number only");
                    return;
                }
                Orthogonal(Width, Height);
            }
            Close();
        }

        private void rbView1_CheckedChanged(object sender, EventArgs e)
        {
            if (rbView1.Checked)
            {
                tbFov.Enabled = true;
                tbHeight.Enabled = false;
                tbWidth.Enabled = false;
            }
        }

        private void rbView2_CheckedChanged(object sender, EventArgs e)
        {
            if (rbView2.Checked)
            {
                tbFov.Enabled = false;
                tbHeight.Enabled = true;
                tbWidth.Enabled = true;
            }
        }
    }
}
