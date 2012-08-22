using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace AC4Analysis
{
    public partial class Text : UserControl
    {
        public byte[] FontData;
        public byte[] TextData;
        Color[] cols = new Color[16];
        public Text()
        {
            InitializeComponent();
        }
        Bitmap[] bmps;
        int FontNum = 0;
        public bool check(byte[] datain)
        {
            FontNum = datain[0x8] + datain[0x9] * 0x100 + datain[0xA] * 0x10000 + datain[0xB] * 1000000;
            if (datain.Length == (FontNum * 0x90 + 0x80))
                return true;
            else
                return false;
        }
        public void Analysis()
        {
            bmps = new Bitmap[FontNum];
            int paladd = FontNum * 0x90 + 0x40;
            for (int i = 0; i < cols.Length; i++)
            {
                byte alpha = FontData[paladd + i * 4 + 3];
                if (alpha == 128)
                    alpha = 255;
                else
                    alpha = (byte)(alpha * 2);
                cols[i] = Color.FromArgb(
                    alpha,
                    127,
                    127,
                    255);
            }
            for (int i = 0; i < FontNum; i++)
            {
                int FontAdd = i * 0x90 + 0x30;
                Bitmap tmp = new Bitmap(16, 16, System.Drawing.Imaging.PixelFormat.Format4bppIndexed);
                System.Drawing.Imaging.ColorPalette tempPalette;
                using (Bitmap tempBmp = new Bitmap(1, 1, System.Drawing.Imaging.PixelFormat.Format4bppIndexed))
                {
                    tempPalette = tempBmp.Palette;
                }
                for (int j = 0; j < cols.Length; j++)
                {
                    tempPalette.Entries[j] = cols[j];
                }
                byte[] newdata = new byte[16 * 16 / 2];
                for (int j = 0; j < newdata.Length; j++)
                {
                    byte A = FontData[j + FontAdd];
                    newdata[j] = (byte)(((A & 0xf0) >> 4) | ((A & 0x0f) << 4));
                }

                tmp.Palette = tempPalette;
                System.Drawing.Imaging.BitmapData bdata = tmp.LockBits(Rectangle.FromLTRB(0, 0, 16, 16), System.Drawing.Imaging.ImageLockMode.WriteOnly, System.Drawing.Imaging.PixelFormat.Format4bppIndexed);
                System.Runtime.InteropServices.Marshal.Copy(newdata, 0, bdata.Scan0, 16 * 16 / 2);
                tmp.UnlockBits(bdata);
                bmps[i] = tmp;
            }
        }
    }
}
