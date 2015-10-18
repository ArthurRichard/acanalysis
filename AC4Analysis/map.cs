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
    public partial class map : UserControl
    {
        public map()
        {
            InitializeComponent();
        }

        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShowMap();
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMapPackData(byte[] Data, int size, int MapTexAdd);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetMapReadProgress();

        public byte[] CulData;
        int TexDataAdd;

        public bool Check(TreeNode node)
        {
            if (node.Parent != null)
                return false;
            if (node.Nodes.Count != 36)
                return false;
            TreeNode TexsNode = node.Nodes[7];
            GetTexs(TexsNode);
            timer1.Start();
            SetMapPackData(CulData, CulData.Length, TexDataAdd);

            ShowMap();
            return true;
        }

        void GetTexs(TreeNode node)
        {
            _L1 tmp = (_L1)node.Tag;
            int texadd = (int)tmp.add;
            TreeNode texlist = node.Nodes[0];
            tmp = (_L1)texlist.Tag;
            texadd += (int)tmp.add;
            tmp = (_L1)texlist.Nodes[0].Tag;
            texadd += (int)tmp.add;
            TexDataAdd = texadd;
        }

        public void Set3Dwin(Control control)
        {
            Height = control.Height + 35;
            Width = control.Width + 5;
            panel1.Height = control.Height + 2;
            panel1.Width = control.Width + 2;
            panel1.Controls.Add(control);
        }
        public void Unset3Dwin()
        {
            panel1.Controls.Clear();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            progressBar1.Value = Math.Min(100, GetMapReadProgress());
            if (progressBar1.Value >= 100)
                timer1.Stop();
        }
    }
}
