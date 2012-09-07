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
        public Win3D()
        {
            InitializeComponent();
            SetMoveStep(float.Parse(textBox1.Text));
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

        }

        private void rdbView模式选择1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void rdbView模式选择2_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
