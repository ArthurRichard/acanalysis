using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace AC4Analysis
{
    public partial class map : UserControl
    {
        public map()
        {
            InitializeComponent();
        }
        public byte[] TexDataTmp = new byte[1024 * 1024];
        public byte[] CulData;
        List<ushort[]> SubMapList = new List<ushort[]>();
        int TexDataAdd;
        int TexCount;
        System.Drawing.Imaging.ColorPalette tempPalette;
        public bool Check(TreeNode node)
        {
            if (node.Parent != null)
                return false;
            if (node.Nodes.Count != 36)
                return false;
            TexDataAdd = 0;
            TexCount = 0;
            TexDataTmp = new byte[1024 * 1024];
            SubMapList = new List<ushort[]>();
            Controls.Clear();
            TreeNode SubMapNode = node.Nodes[5];
            GetSubMapList(SubMapNode);
            TreeNode SubMapIDNode = node.Nodes[6];
            TreeNode TexsNode = node.Nodes[7];
            GetTexs(TexsNode);
            TreeNode MapPalNode = node.Nodes[8];
            GetPal(MapPalNode);
            GetSubMaps();
            return true;
        }
        void GetSubMapList(TreeNode node)
        {
            _L1 tmp = (_L1)node.Tag;
            int add = (int)tmp.add;
            int SubMapCount = (int)tmp.size / 0x200;
            for (int i = 0; i < SubMapCount; i++)
            {
                ushort[] SubMap = new ushort[0x100];
                for (int j = 0; j < 0x100; j++)
                {
                    SubMap[j] = (ushort)(CulData[add + i * 0x200 + j * 2] + CulData[add + i * 0x200 + j * 2 + 1] * 0x100);
                }
                SubMapList.Add(SubMap);
            }
        }
        void GetTexs(TreeNode node)
        { 
            _L1 tmp = (_L1)node.Tag;
            int texadd = (int)tmp.add;
            TreeNode texlist = node.Nodes[0];
            tmp = (_L1)texlist.Tag;
            texadd += (int)tmp.add;
            TexCount = texlist.Nodes.Count;
            tmp = (_L1)texlist.Nodes[0].Tag;
            texadd += (int)tmp.add;
            TexDataAdd = texadd;
        }
        void GetPal(TreeNode node)
        {
            Color[] pal = new Color[256];
            _L1 tmp = (_L1)node.Tag;
            int add = (int)tmp.add;
            for (int i = 0; i < pal.Length; i++)
            {
                byte alpha = CulData[add + i * 4 + 3];
                if (alpha == 128)
                    alpha = 255;
                else
                    alpha = (byte)(alpha * 2);
                pal[i] = Color.FromArgb(
                    alpha,
                    CulData[add + i * 4 + 0],
                    CulData[add + i * 4 + 1],
                    CulData[add + i * 4 + 2]);
            }
            using (Bitmap tempBmp = new Bitmap(1, 1, System.Drawing.Imaging.PixelFormat.Format8bppIndexed))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 0] = pal[i * 32 + j + 8 * 0];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 2] = pal[i * 32 + j + 8 * 1];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 1] = pal[i * 32 + j + 8 * 2];
                for (int j = 0; j < 8; j++)
                    tempPalette.Entries[i * 32 + j + 8 * 3] = pal[i * 32 + j + 8 * 3];
            }
        }
        void SetTex(int PosX, int PosY, int Add,bool turnX,bool turnY)
        {
            int TurnedX = 0,TurnedY = 0;
            for (int y = 0; y < 64; y++)
                for (int x = 0; x < 64; x++)
                {
                    if (turnY)
                        TurnedY = 63 - y;
                    else
                        TurnedY = y;
                    if (turnX)
                        TurnedX = 63 - x;
                    else
                        TurnedX = x;
                    TexDataTmp[PosX + x + (PosY + y) * 1024] = CulData[Add + TurnedY * 64 + TurnedX];
                }
        }
        void GetSubMaps()
        {
            Height = 1024;
            Width = 1024;
            Height = SubMapList.Count * 1024;
            for (int i = 0; i < SubMapList.Count; i++)
            {
                ushort[] SubMap = SubMapList[i];
                for (int y = 0; y < 16; y++)
                    for (int x = 0; x < 16; x++)
                    {
                        bool turnX=false;
                        bool turnY=false;
                        if ((SubMap[y * 16 + x] / 0x800) % 2 == 1)
                            turnY = true;
                        if ((SubMap[y * 16 + x] / 0x400) % 2 == 1)
                            turnX = true;
                        int TexID = SubMap[y * 16 + x]%0x400;
                        int TexAdd = TexDataAdd + TexID * 0x1000;
                        SetTex(0x40 * x, 0x40 * y, TexAdd, turnX, turnY);
                    }
                Bitmap tmp = new Bitmap(1024, 1024, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);
                tmp.Palette = tempPalette;
                System.Drawing.Imaging.BitmapData bdata = tmp.LockBits(
                    Rectangle.FromLTRB(0, 0, 1024, 1024),
                    System.Drawing.Imaging.ImageLockMode.WriteOnly,
                    System.Drawing.Imaging.PixelFormat.Format8bppIndexed);
                System.Runtime.InteropServices.Marshal.Copy(TexDataTmp, 0, bdata.Scan0, 1024 * 1024);
                tmp.UnlockBits(bdata);
                PictureBox pb = new PictureBox();
                pb.Width = 1024;
                pb.Height = 1024;
                pb.Image = tmp;
                Point point=new Point();
                point.Y = i * 1026;
                pb.Location = point;

                pb.BackColor = Color.FromArgb(255, 0, 0, 0);
                Controls.Add(pb);
            }
        }
    }
}
