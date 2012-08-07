using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

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
            if (w == 0 || h == 0)
            {
                this.Visible = false;
                return;
            }
            if ((w * h + 1024) >= data.Length)
            {
                this.Visible = false;
                return;
            }
            //this.Width = w;
            //this.Height = h;
            pictureBox1.Width = w;
            pictureBox1.Height = h;
            label1.Text = "Width：" + w.ToString();
            label2.Text = "Height：" + h.ToString();
            culfmt = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
            System.Drawing.Bitmap gb = new Bitmap(w,h, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);
            paladd=0x20+w*h+0x10;
            paladd+=paladd%16;
            Color[] tmpcols = new Color[256];
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

        }
        void Analysis_GIM4bit()
        {
            this.Visible = false;
        }
        public void Analysis_GIM()
        {
            if (data == null)
                return;
            if (data[4] == 1)
                Analysis_GIM4bit();
            else
                Analysis_GIM8bit();
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
    }
}
