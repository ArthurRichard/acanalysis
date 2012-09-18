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
        public static extern void ChangeMapSize(int Size);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMapData(int ID,byte [] Data);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMapTex(int ID, byte[] Data);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMapIndex(byte[] Data);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShowMap();

        public byte[] TexDataTmp = new byte[1024 * 1024];
        public byte[] CulData;
        List<ushort[]> SubMapList = new List<ushort[]>();
        int TexDataAdd;
        int TexCount;
        Bitmap[] Images;
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
            panel1.Controls.Clear();
            TreeNode SubMapNode = node.Nodes[5];
            GetSubMapList(SubMapNode);
            TreeNode SubMapIDNode = node.Nodes[6];
            GetMapIDs(SubMapIDNode);
            TreeNode TexsNode = node.Nodes[7];
            GetTexs(TexsNode);
            TreeNode MapPalNode = node.Nodes[8];
            GetPal(MapPalNode);
            TreeNode MeshNode = node.Nodes[9];
            GetMesh(MeshNode);

            GetSubMaps();
            SetDataTo3DWin();
            ShowMap();
            return true;
        }
        void GetMesh(TreeNode node)
        {
            _L1 tmp = (_L1)node.Tag;
            int add = (int)tmp.add;
            int SubMeshCount = (int)tmp.size / 0x400;
            byte [] datatmp=new byte[0x400];

            for (int j = 0; j < Images.Length; j++)
            {
                for (int i = 0; i < 0x400; i++)
                {
                    datatmp[i] = CulData[add + i+j*0x400];
                }
                SetMapData(j, datatmp);
            }
            //InputMap(datatmp, 0x400);
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
            Images = new Bitmap[SubMapCount];
            ChangeMapSize(SubMapCount);
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
                    //if (!turnX)
                    TexDataTmp[PosX + x + (PosY + y) * 1024] = CulData[Add + TurnedY * 64 + TurnedX];
                }
        }
        void GetSubMaps()
        {
            //Height = SubMapList.Count * 1024;
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
                //Controls.Add(pb);
                Images[i] = tmp;
                progressBar1.Value = 50 * i / SubMapList.Count;
            }
        }
        void GetMapIDs(TreeNode node)
        {
            _L1 tmp = (_L1)node.Tag;
            int add = (int)tmp.add;
            byte[] datatmp = new byte[0x100];
            for (int i = 0; i < 0x100; i++)
            {
                datatmp[i] = CulData[add + i];
            }
            SetMapIndex(datatmp);
        }
        public void Set3Dwin(Control control)
        {
            Height = control.Height+35;
            Width = control.Width + 5;
            panel1.Height = control.Height + 2;
            panel1.Width = control.Width + 2;
            panel1.Controls.Add(control);
        }
        public void Unset3Dwin()
        {
            panel1.Controls.Clear();
        }
        //[DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void InputTex(byte[] TexDataIn, int SizeX, int SizeY, int DataSize);
        void SetDataTo3DWin()
        {
            for (int i = 0; i < SubMapList.Count; i++)
            {
                System.Drawing.Bitmap gb = Images[i];
                System.Drawing.Bitmap newb = new Bitmap(gb.Width, gb.Height, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                for (int y = 0; y < gb.Height; y++)
                    for (int x = 0; x < gb.Width; x++)
                    {
                        newb.SetPixel(x, y, gb.GetPixel(x, y));
                    }
                byte[] TexDataIn = new byte[gb.Width * gb.Height * 4];
                System.Drawing.Imaging.BitmapData bdata = newb.LockBits(Rectangle.FromLTRB(0, 0, gb.Width, gb.Height), System.Drawing.Imaging.ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

                System.Runtime.InteropServices.Marshal.Copy(bdata.Scan0, TexDataIn, 0, gb.Width * gb.Height * 4);
                newb.UnlockBits(bdata);
                //InputTex(TexDataIn, gb.Width, gb.Height, gb.Width * gb.Height * 4);
                SetMapTex(i, TexDataIn);
                progressBar1.Value = 50+50 * (i+1) / SubMapList.Count;
                Update();
            }
        }
    }
}
