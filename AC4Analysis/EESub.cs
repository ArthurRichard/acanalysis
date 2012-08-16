using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace AC4Analysis
{
    public partial class EESub : UserControl
    {
        public enum _Type
        {
            _4bit,
            _8bit
        }
        public byte[] CulImage;
        public byte[] CulPal;
        public _Type T=new _Type();
        public int w;
        public int h;
        public EESub()
        {
            InitializeComponent();
        }
        public void init()
        {
            this.Width = w*2+15;
            this.Height = h+5;
            pictureBoxRGB.Width = w;
            pictureBoxRGB.Height = h;
            Point p = new Point();
            p.Y = 0;
            p.X = w + 10;
            pictureBoxAlpha.Location = p;
            pictureBoxAlpha.Width = w;
            pictureBoxAlpha.Height = h;
            if (T == _Type._4bit)
                EE4bit();
            else
                EE8bit();
        }
        void EE8bitRGB()
        {
            System.Drawing.Imaging.PixelFormat culfmt = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
            System.Drawing.Bitmap gb = new Bitmap(w, h, culfmt);
            Color[] tmpcols = new Color[256];
            for (int i = 0; i < tmpcols.Length; i++)
            {
                if ((CulPal.Length % 3) != 0)
                {
                    byte alpha = CulPal[i * 4 + 3];
                    if (alpha == 128)
                        alpha = 255;
                    else
                        alpha = (byte)(alpha * 2);
                    tmpcols[i] = Color.FromArgb(
                        alpha,
                        CulPal[i * 4 + 0],
                        CulPal[i * 4 + 1],
                        CulPal[i * 4 + 2]);
                }
                else
                {
                    tmpcols[i] = Color.FromArgb(
                          255,
                          CulPal[i * 3 + 0],
                          CulPal[i * 3 + 1],
                          CulPal[i * 3 + 2]);
                }
            }
            System.Drawing.Imaging.ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, culfmt))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 0] = tmpcols[i * 32 + j + 8 * 0];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 2] = tmpcols[i * 32 + j + 8 * 1];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 1] = tmpcols[i * 32 + j + 8 * 2];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 3] = tmpcols[i * 32 + j + 8 * 3];
            }

            gb.Palette = tempPalette;
            System.Drawing.Imaging.BitmapData bdata = gb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);

            System.Runtime.InteropServices.Marshal.Copy(CulImage, 0, bdata.Scan0, w * h);
            gb.UnlockBits(bdata);
            pictureBoxRGB.Image = gb;
            pictureBoxRGB.BackColor = Color.FromArgb(255, 0, 0, 0);
        }
        void EE8bitAlpha()
        {
            System.Drawing.Imaging.PixelFormat culfmt = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
            System.Drawing.Bitmap gb = new Bitmap(w, h, culfmt);
            Color[] tmpcols = new Color[256];
            for (int i = 0; i < tmpcols.Length; i++)
            {
                byte alpha = CulPal[i * 4 + 3];
                if (alpha == 128)
                    alpha = 255;
                else
                    alpha = (byte)(alpha * 2);
                tmpcols[i] = Color.FromArgb(
                    255,
                    alpha,
                    alpha,
                    alpha);

            }
            System.Drawing.Imaging.ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, culfmt))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 0] = tmpcols[i * 32 + j + 8 * 0];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 2] = tmpcols[i * 32 + j + 8 * 1];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 1] = tmpcols[i * 32 + j + 8 * 2];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 3] = tmpcols[i * 32 + j + 8 * 3];
            }

            gb.Palette = tempPalette;
            System.Drawing.Imaging.BitmapData bdata = gb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);

            System.Runtime.InteropServices.Marshal.Copy(CulImage, 0, bdata.Scan0, w * h);
            gb.UnlockBits(bdata);
            pictureBoxAlpha.Image = gb;
            pictureBoxAlpha.BackColor = Color.FromArgb(255, 0, 0, 0);
        }
        void EE8bit()
        {
            EE8bitRGB();
            if ((CulPal.Length % 3) != 0)
                EE8bitAlpha();
        }
        void EE4bitRGB()
        {
            System.Drawing.Imaging.PixelFormat culfmt = System.Drawing.Imaging.PixelFormat.Format4bppIndexed;
            System.Drawing.Bitmap gb = new Bitmap(w, h, culfmt);
            Color[] tmpcols = new Color[16];
            for (int i = 0; i < tmpcols.Length; i++)
            {
                if ((CulPal.Length % 3) != 0)
                {
                    byte alpha = CulPal[i * 4 + 3];
                    if (alpha == 128)
                        alpha = 255;
                    else
                        alpha = (byte)(alpha * 2);
                    tmpcols[i] = Color.FromArgb(
                        alpha,
                        CulPal[i * 4 + 0],
                        CulPal[i * 4 + 1],
                        CulPal[i * 4 + 2]);
                }
                else
                {
                    tmpcols[i] = Color.FromArgb(
                          255,
                          CulPal[i * 3 + 0],
                          CulPal[i * 3 + 1],
                          CulPal[i * 3 + 2]);
                }
            }
            System.Drawing.Imaging.ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, culfmt))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < tmpcols.Length; i++)
            {
                tempPalette.Entries[i] = tmpcols[i];
            }
            byte[] newdata = new byte[w * h / 2];
            for (int i = 0; i < newdata.Length; i++)
            {
                byte A = CulImage[i];
                newdata[i] = (byte)(((A & 0xf0) >> 4) | ((A & 0x0f) << 4));
            }
            gb.Palette = tempPalette;
            System.Drawing.Imaging.BitmapData bdata = gb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);
            System.Runtime.InteropServices.Marshal.Copy(newdata, 0, bdata.Scan0, w * h / 2);
            gb.UnlockBits(bdata);
            pictureBoxRGB.Image = gb;
            pictureBoxRGB.BackColor = Color.FromArgb(255, 0, 0, 0);
        }
        void EE4bitAlpha()
        {
            System.Drawing.Imaging.PixelFormat culfmt = System.Drawing.Imaging.PixelFormat.Format4bppIndexed;
            System.Drawing.Bitmap gb = new Bitmap(w, h, culfmt);
            Color[] tmpcols = new Color[16];
            for (int i = 0; i < tmpcols.Length; i++)
            {
                byte alpha = CulPal[i * 4 + 3];
                if (alpha == 128)
                    alpha = 255;
                else
                    alpha = (byte)(alpha * 2);
                tmpcols[i] = Color.FromArgb(
                    255,
                    alpha,
                    alpha,
                    alpha);

            }
            System.Drawing.Imaging.ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, culfmt))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < tmpcols.Length; i++)
            {
                tempPalette.Entries[i] = tmpcols[i];
            }
            byte[] newdata = new byte[w * h / 2];
            for (int i = 0; i < newdata.Length; i++)
            {
                byte A = CulImage[i];
                newdata[i] = (byte)(((A & 0xf0) >> 4) | ((A & 0x0f) << 4));
            }
            gb.Palette = tempPalette;
            System.Drawing.Imaging.BitmapData bdata = gb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);
            System.Runtime.InteropServices.Marshal.Copy(newdata, 0, bdata.Scan0, w * h / 2);
            gb.UnlockBits(bdata);
            pictureBoxAlpha.Image = gb;
            pictureBoxAlpha.BackColor = Color.FromArgb(255, 0, 0, 0);
        }
        void EE4bit()
        {
            EE4bitRGB();
            if ((CulPal.Length % 3) != 0)
                EE4bitAlpha();
        }
    }
}
