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
        public static extern void ChangeView(float TurnX, float TurnY, float TurnZ);
        public Win3D()
        {
            InitializeComponent();
            btn开关灯.Text = "Turn On Light";
            btn开关透明.Text = "Turn On Alpha";
        }

        bool OpenLight = false;
        bool OpenAlpha = false;
        public IntPtr GetHwnd()
        {
            return panel1.Handle;
        }

        private void btn开关灯_Click(object sender, EventArgs e)
        {
            OpenLight = !OpenLight;
            if (OpenLight)
                btn开关灯.Text = "Turn Off Light";
            else
                btn开关灯.Text = "Turn On Light";
            LightSwitch(OpenLight);

        }

        private void btn开关透明_Click(object sender, EventArgs e)
        {
            OpenAlpha = !OpenAlpha;
            if (OpenAlpha)
                btn开关透明.Text = "Turn Off Alpha";
            else
                btn开关透明.Text = "Turn On Alpha";
            AlphaSwitch(OpenAlpha);
        }

        private void btn向左旋转_Click(object sender, EventArgs e)
        {
            timer旋转停止.Start();
            ChangeView(1.0f, 0.0f, 0.0f);
        }

        private void btn向右旋转_Click(object sender, EventArgs e)
        {
            timer旋转停止.Start();
            ChangeView(-1.0f, 0.0f, 0.0f);
        }

        private void btn向上旋转_Click(object sender, EventArgs e)
        {
            timer旋转停止.Start();
            ChangeView(0.0f,-1.0f, 0.0f);
        }

        private void btn向下旋转_Click(object sender, EventArgs e)
        {
            timer旋转停止.Start();
            ChangeView(0.0f, 1.0f, 0.0f);
        }

        private void btn拉近_Click(object sender, EventArgs e)
        {
            timer旋转停止.Start();
            ChangeView(0.0f, 0.0f, -1.0f);
        }

        private void btn拉远_Click(object sender, EventArgs e)
        {
            timer旋转停止.Start();
            ChangeView(0.0f, 0.0f, 1.0f);
        }

        private void timer旋转停止_Tick(object sender, EventArgs e)
        {
            timer旋转停止.Stop();
            ChangeView(0.0f, 0.0f, 0.0f);
        }
    }
}
