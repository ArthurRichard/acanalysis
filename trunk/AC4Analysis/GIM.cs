using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using System.Runtime.InteropServices;
using System.IO;
namespace AC4Analysis
{
    public partial class GIM : UserControl
    {
        public byte[] data;
        public GIM()
        {
            InitializeComponent();
        }
        public string cdpfilename;
        int w;
        int h;
        public uint add;
        int paladd;
        System.Drawing.Imaging.PixelFormat culfmt;
        void Analysis_GIM8bit()
        {
            w = data[0x1c] + data[0x1d] * 256;
            h = data[0x1e] + data[0x1f] * 256;
            pictureBox1.Width = w;
            pictureBox1.Height = h;
            pictureBox2.Width = w;
            pictureBox2.Height = h;
            label1.Text = "Width：" + w.ToString();
            label2.Text = "Height：" + h.ToString();
            culfmt = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
            System.Drawing.Bitmap gb = new Bitmap(w,h, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);
            paladd=0x20+w*h+0x10;
            if ((paladd % 16) > 0)
                paladd += (16 - paladd % 16);
            Color[] tmpcols = new Color[256];
            Color[] tmpcolsA = new Color[256];
            for (int i = 0; i < tmpcols.Length; i++)
            {
                byte alpha = data[paladd + i * 4 + 3];
                if (alpha == 128)
                    alpha = 255;
                else
                    alpha = (byte)(alpha * 2);
                tmpcols[i] = Color.FromArgb(
                    alpha,
                    data[paladd + i * 4 + 0],
                    data[paladd + i * 4 + 1],
                    data[paladd + i * 4 + 2]);
                //tmpcols[i] = Color.FromArgb(
                //    data[paladd + i * 4 + 0],
                //    data[paladd + i * 4 + 1],
                //    data[paladd + i * 4 + 2]);
                tmpcolsA[i] = Color.FromArgb(255, alpha, alpha, alpha);
            }
            System.Drawing.Imaging.ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, System.Drawing.Imaging.PixelFormat.Format8bppIndexed))
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

            System.Drawing.Imaging.BitmapData bdata = gb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);
            System.Runtime.InteropServices.Marshal.Copy(data, 0x20, bdata.Scan0, w * h);
            gb.UnlockBits(bdata);

            pictureBox1.Image = gb;
            pictureBox1.BackColor = Color.FromArgb(255, 0, 0, 0);
            this.Visible = true;
            btn导入图像.Enabled = true;
            btn保存非调色板图像.Enabled = true;
            btn在3D窗口里使用.Enabled = true;

            System.Drawing.Imaging.ColorPalette tempPaletteA;
            using (Bitmap tempBmp = new Bitmap(1, 1, culfmt))
            {
                tempPaletteA = tempBmp.Palette;
            }
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    tempPaletteA.Entries[i * 32 + j + 8 * 0] = tmpcolsA[i * 32 + j + 8 * 0];
                for (int j = 0; j < 8; j++)
                    tempPaletteA.Entries[i * 32 + j + 8 * 2] = tmpcolsA[i * 32 + j + 8 * 1];
                for (int j = 0; j < 8; j++)
                    tempPaletteA.Entries[i * 32 + j + 8 * 1] = tmpcolsA[i * 32 + j + 8 * 2];
                for (int j = 0; j < 8; j++)
                    tempPaletteA.Entries[i * 32 + j + 8 * 3] = tmpcolsA[i * 32 + j + 8 * 3];
            }
            System.Drawing.Bitmap gbA = new Bitmap(w, h, culfmt);
            gbA.Palette = tempPaletteA;
            System.Drawing.Imaging.BitmapData bdataA = gbA.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);
            System.Runtime.InteropServices.Marshal.Copy(data, 0x20, bdataA.Scan0, w * h);
            gbA.UnlockBits(bdataA);
            pictureBox2.Image = gbA;
            pictureBox2.BackColor = Color.FromArgb(255, 0, 0, 0);
            Point point = new Point();
            point.X = pictureBox1.Location.X + w + 5;
            point.Y = pictureBox1.Location.Y;
            pictureBox2.Location = point;
            Width = Math.Max(605, pictureBox1.Location.X + w * 2 + 10);
            pictureBox2.Visible = true;
        }
        void Analysis_GIM4bit()
        {
            w = data[0x1c] + data[0x1d] * 256;
            h = data[0x1e] + data[0x1f] * 256;
            pictureBox1.Width = w;
            pictureBox1.Height = h;
            label1.Text = "Width：" + w.ToString();
            label2.Text = "Height：" + h.ToString();

            culfmt = System.Drawing.Imaging.PixelFormat.Format4bppIndexed;
            System.Drawing.Bitmap gb = new Bitmap(w, h, culfmt);
            paladd = 0x20 + w * h / 2 + 0x10;
            if ((paladd % 16) > 0)
                paladd += (16 - paladd % 16);
            Color[] tmpcols = new Color[16];
            Color[] tmpcolsA = new Color[16];
            for (int i = 0; i < tmpcols.Length; i++)
            {
                byte alpha = data[paladd + i * 4 + 3];
                if (alpha == 128)
                    alpha = 255;
                else
                    alpha = (byte)(alpha * 2);
                tmpcols[i] = Color.FromArgb(
                    alpha,
                    data[paladd + i * 4 + 0],
                    data[paladd + i * 4 + 1],
                    data[paladd + i * 4 + 2]);
                tmpcolsA[i] = Color.FromArgb(255, alpha, alpha, alpha);
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
                byte A = data[i + 0x20];
                newdata[i] = (byte)(((A & 0xf0) >> 4) | ((A & 0x0f) << 4));
            }
            gb.Palette = tempPalette;
            System.Drawing.Imaging.BitmapData bdata = gb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);
            System.Runtime.InteropServices.Marshal.Copy(newdata, 0, bdata.Scan0, w * h / 2);
            gb.UnlockBits(bdata);
            pictureBox1.Image = gb;
            pictureBox1.BackColor = Color.FromArgb(255, 0, 0, 0);
            this.Visible = true;

            System.Drawing.Imaging.ColorPalette tempPaletteA;
            using (Bitmap tempBmp = new Bitmap(1, 1, culfmt))
            {
                tempPaletteA = tempBmp.Palette;
            }
            for (int i = 0; i < tmpcols.Length; i++)
            {
                tempPaletteA.Entries[i] = tmpcolsA[i];
            }
            System.Drawing.Bitmap gbA = new Bitmap(w, h, culfmt);
            gbA.Palette = tempPalette;
            System.Drawing.Imaging.BitmapData bdataA = gbA.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);
            System.Runtime.InteropServices.Marshal.Copy(newdata, 0, bdataA.Scan0, w * h / 2);
            gbA.UnlockBits(bdataA);
            PictureBox pbA = new PictureBox();
            pbA.Image = gbA;
            pbA.Width = w;
            pbA.Height = h;
            Point point = new Point();
            point.X = pictureBox1.Location.X + w + 5;
            point.Y = pictureBox1.Location.Y;
            pbA.Location = point;
            Controls.Add(pbA);
            Width = Math.Max(605, pictureBox1.Location.X + w * 2 + 10);
        }
        void Analysis_GIM24bit()
        {
            w = data[0x1c] + data[0x1d] * 256;
            h = data[0x1e] + data[0x1f] * 256;
            pictureBox1.Width = w;
            pictureBox1.Height = h;
            label1.Text = "Width：" + w.ToString();
            label2.Text = "Height：" + h.ToString();
            int newW=w + 4 - w % 4;
            byte[] DataBgra = new byte[newW * h * 3];
            for (int y = 0; y < h; y++)
            {
                for (int x = 0; x < w; x++)
                {
                    DataBgra[y * newW * 3 + x * 3 + 0] = data[y * w * 3 + x * 3 + 1];
                    DataBgra[y * newW * 3 + x * 3 + 1] = data[y * w * 3 + x * 3 + 0];
                    DataBgra[y * newW * 3 + x * 3 + 2] = data[y * w * 3 + x * 3 + 2];
                }
                for (int x = w; x < newW; x++)
                {
                    DataBgra[y * newW * 3 + x * 3 + 0] = 0;
                    DataBgra[y * newW * 3 + x * 3 + 1] = 0;
                    DataBgra[y * newW * 3 + x * 3 + 2] = 0;
                }
            }
            culfmt = System.Drawing.Imaging.PixelFormat.Format24bppRgb;
            System.Drawing.Bitmap gb = new Bitmap(newW, h, culfmt);
            System.Drawing.Imaging.BitmapData bdata = gb.LockBits(Rectangle.FromLTRB(0, 0, newW, h), System.Drawing.Imaging.ImageLockMode.WriteOnly, culfmt);
            System.Runtime.InteropServices.Marshal.Copy(DataBgra, 0, bdata.Scan0, newW * h * 3);
            gb.UnlockBits(bdata);
            pictureBox1.Image = gb;
            pictureBox1.BackColor = Color.FromArgb(255, 0, 0, 0);
            this.Visible = true;
        }
        public void Analysis_GIM()
        {
            btn保存非调色板图像.Enabled = false;
            btn导入图像.Enabled = false;
            btn在3D窗口里使用.Enabled = false;
            this.Visible = false;
            if (data == null)
                return;
            if (data[0x10] == 0x30)
                return;
            if (data[0x13] == 0x13 || data[0x13]==0x1B)
            {
                Analysis_GIM8bit();
                return;
            }
            if (data[0x13] == 0x14)
            {
                if (data[0x8] != 0 || data[0x9] != 0 || data[0xA] != 0 || data[0xB] != 0)
                {
                    return;
                }
                Analysis_GIM4bit();
                return;
            }
            if (data[0x12] == 4 || data[0x13] == 1)
            {
                Analysis_GIM24bit();
                return;
            }
        }

        private void btn保存图像_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image == null)
                return;
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "bmp files (*.bmp)|*.bmp|gif files|*.gif|png files|*.png|jpg files|*.jpg|tif files|*.tif";
            if (!sfd.ShowDialog().Equals(DialogResult.OK))
                return;
            string ext=System.IO.Path.GetExtension(sfd.FileName);
            switch (ext)
            {
                case ".bmp":
                    {
                        pictureBox1.Image.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Bmp);
                        break;
                    }
                case ".gif":
                    {
                        pictureBox1.Image.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Gif);
                        break;
                    }
                case ".jpg":
                    {
                        pictureBox1.Image.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Jpeg);
                        break;
                    }
                case ".png":
                    {
                        pictureBox1.Image.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Png);
                        break;
                    }
                case ".tif":
                    {
                        pictureBox1.Image.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Tiff);
                        break;
                    }
                default:
                    {
                        pictureBox1.Image.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Bmp);
                        break;
                    }
            }
        }
        void save8Bit(Bitmap imb)
        {
            Color[] tmpcols = new Color[256];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    tmpcols[i * 32 + j + 8 * 0] = imb.Palette.Entries[i * 32 + j + 8 * 0];
                for (int j = 0; j < 8; j++)
                    tmpcols[i * 32 + j + 8 * 1] = imb.Palette.Entries[i * 32 + j + 8 * 2];
                for (int j = 0; j < 8; j++)
                    tmpcols[i * 32 + j + 8 * 2] = imb.Palette.Entries[i * 32 + j + 8 * 1];
                for (int j = 0; j < 8; j++)
                    tmpcols[i * 32 + j + 8 * 3] = imb.Palette.Entries[i * 32 + j + 8 * 3];
            }
                        
            for (int i = 0; i < tmpcols.Length; i++)
            {
                data[paladd + i * 4 + 0]=tmpcols[i].R;
                data[paladd + i * 4 + 1]=tmpcols[i].G;
                data[paladd + i * 4 + 2]=tmpcols[i].B;
            }
            System.Drawing.Imaging.BitmapData bdata = imb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);

            System.Runtime.InteropServices.Marshal.Copy(bdata.Scan0, data, 0x20, w * h);
            imb.UnlockBits(bdata);
            Analysis_GIM8bit();

            FileStream fsc = new FileStream(cdpfilename, FileMode.Open);
            fsc.Seek(add, SeekOrigin.Begin);
            fsc.Write(data, 0, data.Length);
            fsc.Close();
            MessageBox.Show("Save to DATA.TBL OK");
        }
        private void btn导入图像_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image == null)
                return;
            OpenFileDialog ofd = new OpenFileDialog();
            if (!ofd.ShowDialog().Equals(DialogResult.OK))
                return;
            Bitmap imb;
            try
            {
                imb = new Bitmap(ofd.FileName);
                if (imb.PixelFormat != culfmt)
                {
                    throw new Exception("格式不符，输入图像必须是" + culfmt.ToString() + "\nFormat Error");
                }
                if (imb.Width != w || imb.Height != h)
                {
                    throw new Exception("大小不符"+ "\nSize Error");
                }
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
                return;
            }
            if (culfmt == System.Drawing.Imaging.PixelFormat.Format8bppIndexed)
                save8Bit(imb);
        }

        private void btn保存非调色板图像_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image == null)
                return;
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "tif files (*.tif)|*.tif|png files|*.png";
            if (!sfd.ShowDialog().Equals(DialogResult.OK))
                return;
            string ext=System.IO.Path.GetExtension(sfd.FileName);
            System.Drawing.Bitmap gb = (System.Drawing.Bitmap)pictureBox1.Image;
            if (gb.PixelFormat == System.Drawing.Imaging.PixelFormat.Format8bppIndexed)
            {
                System.Drawing.Bitmap newb = new Bitmap(w,h, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                for(int y=0;y<h;y++)
                    for (int x = 0; x < w; x++)
                    { 
                        newb.SetPixel(x,y,gb.GetPixel(x,y));
                    }
                switch (ext)
                {
                    case ".png":
                        {
                            newb.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Png);
                            break;
                        }
                    case ".tif":
                        {
                            newb.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Tiff);
                            break;
                        }
                    default:
                        {
                            newb.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Tiff);
                            break;
                        }
                }
            }
        }

        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InputTex(byte[] TexDataIn, int SizeX, int SizeY, int DataSize);
        private void btn在3D窗口里使用_Click(object sender, EventArgs e)
        {
            System.Drawing.Bitmap gb = (System.Drawing.Bitmap)pictureBox1.Image;
            System.Drawing.Bitmap newb = new Bitmap(w, h, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            for (int y = 0; y < h; y++)
                for (int x = 0; x < w; x++)
                {
                    newb.SetPixel(x, y, gb.GetPixel(x, y));
                }
            byte[] TexDataIn = new byte[w * h * 4];
            System.Drawing.Imaging.BitmapData bdata = newb.LockBits(Rectangle.FromLTRB(0, 0, w, h), System.Drawing.Imaging.ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            System.Runtime.InteropServices.Marshal.Copy(bdata.Scan0, TexDataIn, 0, w * h*4);
            newb.UnlockBits(bdata);
            InputTex(TexDataIn, w, h, w * h * 4);
        }
    }
}
