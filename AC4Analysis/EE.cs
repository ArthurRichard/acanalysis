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
            CulEEadd = 0x10;
            bool EEend = false;
            int posY = 40;
            while (!EEend)
            {
                if (data[CulEEadd + 1] == 0x80)
                {
                    EEend = true;
                    break;
                }
                EESub sub = new EESub();
                //if ((data[CulEEadd + 0x17] != 0x13) && (data[CulEEadd + 0x17] != 0x14))
                //    return;
                //if (data[CulEEadd + 0x17] == 0x13)
                //    sub.T = EESub._Type._8bit;
                //else
                //    sub.T = EESub._Type._4bit;
                sub.w = data[CulEEadd + 0x30] + data[CulEEadd + 0x31] * 0x100;
                sub.h = data[CulEEadd + 0x34] + data[CulEEadd + 0x35] * 0x100;
                int size = data[CulEEadd + 0x50] + data[CulEEadd + 0x51]*0x100 + data[CulEEadd + 0x52]*0x10000 + data[CulEEadd + 0x53]*0x1000000;
                size = size * 0x10;
                sub.CulImage = new byte[size];
                Array.Copy(data, CulEEadd + 0x60, sub.CulImage, 0, size);
                CulEEadd += 0x60;
                CulEEadd += size;
                if ((CulEEadd+0x60) >= data.Length)
                {
                    label1.Text = "error";
                    return;
                }
                size = data[CulEEadd + 0x50] + data[CulEEadd + 0x51] * 0x100 + data[CulEEadd + 0x52] * 0x10000 + data[CulEEadd + 0x53] * 0x1000000;
                if (size > 0x10)
                    sub.T = EESub._Type._8bit;
                else
                    sub.T = EESub._Type._4bit;
                size = size * 0x10;
                sub.CulPal = new byte[size];
                Array.Copy(data, CulEEadd + 0x60, sub.CulPal, 0, size);
                CulEEadd += 0x60;
                CulEEadd += size;
                sub.init();
                sub.Location = new Point(0, posY);
                Controls.Add(sub);
                posY += sub.h + 5;
            }
            this.Height = posY;
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
