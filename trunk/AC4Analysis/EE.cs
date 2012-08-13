using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace AC4Analysis
{
    public partial class EE : UserControl
    {
        int CulEEadd = 0;
        public byte[] data;
        public EE()
        {
            InitializeComponent();
        }
        public void Analysis_EE()
        {
            Controls.Clear();
            Controls.Add(label1);
            if (!checkEEhead())
            {
                label1.Text = "error";
                return;
            }
            else
                label1.Text = "EE";
            
        }
        bool checkEEhead()
        {
            if (data[3] != 0x10)
                return false;
            if (data[0xf] != 0x51)
                return false;
            if ((data[0] != data[0xC]) || (data[1] != data[0xD]) || (data[2] != data[0xE]))
                return false;
            return true;
        }
    }
}
