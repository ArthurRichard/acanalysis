using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using System.Runtime.InteropServices;
namespace AC4Analysis
{
    public partial class Win3D : UserControl
    {
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LightSwitch(bool Use);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AlphaSwitch(bool Use);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMoveStep(float MoveStepIn);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ResetView();
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ChangeViewMode(int mode);
        LightWin lightwin;
        ViewWin viewwin;
        public Win3D()
        {
            InitializeComponent();
            rdbView模式选择1.Checked = true;
            tp观察模式操作说明.SetToolTip(rdbView模式选择1, "Mouse wheel to Forward and back\nDrag mouse right key to change view");
            tp自由模式操作说明.SetToolTip(rdbView模式选择2, "Mouse wheel to Forward and back\nDrag mouse right key to change view\nDrag mouse middle key to move");
            SetMoveStep(float.Parse(textBox1.Text));
            lightwin = new LightWin();
            viewwin = new ViewWin();
        }
        public IntPtr GetHwnd()
        {
            return panel1.Handle;
        }

        private void cb光源开关_CheckedChanged(object sender, EventArgs e)
        {
            LightSwitch(cb光源开关.Checked);
        }

        private void cb透明开关_CheckedChanged(object sender, EventArgs e)
        {

            AlphaSwitch(cb透明开关.Checked);
        }

        private void textBox1_KeyUp(object sender, KeyEventArgs e)
        {
            float MoveStep = 10.0f;
            if (float.TryParse(textBox1.Text, out MoveStep) == false)
            {
                MessageBox.Show("Must number only");
            }
            else
            {
                SetMoveStep(MoveStep);
            }

        }

        private void btn重置视角_Click(object sender, EventArgs e)
        {
            ResetView();
        }

        private void rdbView模式选择1_CheckedChanged(object sender, EventArgs e)
        {
            if (rdbView模式选择1.Checked)
                ChangeViewMode(0);
        }

        private void rdbView模式选择2_CheckedChanged(object sender, EventArgs e)
        {
            if (rdbView模式选择2.Checked)
                ChangeViewMode(1);
        }

        private void btn设置光源_Click(object sender, EventArgs e)
        {
            lightwin.ShowDialog();
        }

        private void btnSetView_Click(object sender, EventArgs e)
        {
            viewwin.ShowDialog();
        }
    }
}
