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
    public partial class SM : UserControl
    {
        public byte[] data;
        public class SMPart
        {
            // 0x00
            public Single[] Pos = new Single[4];
            // 0x10
            public Single[] Rot = new Single[4];
            // 0x20
            public Int32 unknowData1;      // 不明 多为0x00
            public Int32 meshOffset;       // 网格数据偏址
            public Single unknowData2;     // 不明 一个单精浮点
            public Single unknowData3;     // 不明 多为0x00
            // 0x30
            public Int32 subPartCount;     // 子部件数量
            public Int32 subPartOffset;    // 子部件偏址
            public Int32 unknowData4;      // 不明 多为0x00
            public Int32 unknowData5;      // 不明 多为0xFF

            public Int32 parentID;          // 父对象索引
            public Int32 vertStartID;       // 起始顶点
            public Int32 vertCount;         // 顶点数

            public void LoadPart(Byte[] data, Int32 startOffset, Int32 pID)
            {
                for (Int32 i = 0; i < 4; i++)
                {
                    Pos[i] = BitConverter.ToSingle(data, startOffset + sizeof(Single) * i);
                    Rot[i] = BitConverter.ToSingle(data, startOffset + 0x10 + sizeof(Single) * i);
                }

                unknowData1 = BitConverter.ToInt32(data, startOffset + 0x20);
                meshOffset = BitConverter.ToInt32(data, startOffset + 0x20 + 4);
                unknowData2 = BitConverter.ToInt32(data, startOffset + 0x20 + 8);
                unknowData3 = BitConverter.ToInt32(data, startOffset + 0x20 + 12);

                subPartCount = BitConverter.ToInt32(data, startOffset + 0x30);
                subPartOffset = BitConverter.ToInt32(data, startOffset + 0x30 + 4);
                unknowData4 = BitConverter.ToInt32(data, startOffset + 0x30 + 8);
                unknowData5 = BitConverter.ToInt32(data, startOffset + 0x30 + 12);

                parentID = pID;
            }
        };
        List<Single> Verts = new List<Single>();
        List<Single> Normals = new List<Single>();
        List<Single> TexCoords = new List<Single>();
        List<SMPart> Parts = new List<SMPart>();

        float[] Vesout;
        float[] Norout;
        float[] Texout;
        float[] PartTR;
        int[] PartInfo;
        
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Set3DData(float[] VecsIn, float[] NorsIn, int VecSizeIn, float[] TexsIn, int TexsSizeIn);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPartData(float[] PartTRIn, int[] PartInfoIn, int PartSizeIn);

        private void LoadSMPart(Int32 startOffset, Int32 pID)
        {
            SMPart mPart = new SMPart();
            mPart.LoadPart(data, startOffset, pID);
            Parts.Add(mPart);

            Int32 mID = Parts.Count - 1;

            Parts[mID].vertStartID = Verts.Count / 3;
            LoadSMMesh(mPart.meshOffset);
            Parts[mID].vertCount = Verts.Count / 3 - Parts[mID].vertStartID;

            for (Int32 i = 0; i < mPart.subPartCount; i++)
            {
                LoadSMPart(BitConverter.ToInt32(data, mPart.subPartOffset + sizeof(Int32) * i), mID);
            }
        }

        private void LoadSMMesh(Int32 startOffset)
        {
            Int32 mOffset = BitConverter.ToInt32(data, startOffset + 4);
            while (BitConverter.ToInt32(data, mOffset) == 0x1000000A || BitConverter.ToInt32(data, mOffset) == 0x10000008)
            {
                if (data[mOffset] == 0x0A)
                {
                    for (Int32 i = 2; i > -1; i--)
                    {
                        Int32 mTexCoordsOffset = mOffset + 20 + i * 8;      // UV数据起始位置
                        TexCoords.Add((Single)BitConverter.ToInt16(data, mTexCoordsOffset) / 0x1000);
                        TexCoords.Add((Single)BitConverter.ToInt16(data, mTexCoordsOffset + 2) / 0x1000);

                        Int32 mNormalsOffset = mOffset + 144 + i * 8;        // Normal数据起始位置
                        Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset) / 0x1000);
                        Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset + 2) / 0x1000);
                        Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset + 4) / 0x1000);

                        Int32 mVertsOffset = mOffset + 76 + i * 16;        // Vertex数据起始位置
                        Verts.Add(BitConverter.ToSingle(data, mVertsOffset));
                        Verts.Add(BitConverter.ToSingle(data, mVertsOffset + 4));
                        Verts.Add(BitConverter.ToSingle(data, mVertsOffset + 8));
                    }

                    for (Int32 i = 1; i < 4; i++)
                    {
                        Int32 mTexCoordsOffset = mOffset + 20 + i * 8;      // UV数据起始位置
                        TexCoords.Add((Single)BitConverter.ToInt16(data, mTexCoordsOffset) / 0x1000);
                        TexCoords.Add((Single)BitConverter.ToInt16(data, mTexCoordsOffset + 2) / 0x1000);

                        Int32 mNormalsOffset = mOffset + 144 + i * 8;        // Normal数据起始位置
                        Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset) / 0x1000);
                        Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset + 2) / 0x1000);
                        Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset + 4) / 0x1000);

                        Int32 mVertsOffset = mOffset + 76 + i * 16;        // Vertex数据起始位置
                        Verts.Add(BitConverter.ToSingle(data, mVertsOffset));
                        Verts.Add(BitConverter.ToSingle(data, mVertsOffset + 4));
                        Verts.Add(BitConverter.ToSingle(data, mVertsOffset + 8));
                    }
                    mOffset += 256;
                }
                else
                {
                    if (data[mOffset] == 0x08)
                    {
                        for (Int32 i = 2; i > -1; i--)
                        {
                            Int32 mTexCoordsOffset = mOffset + 24 + i * 8;      // UV数据起始位置
                            TexCoords.Add((Single)BitConverter.ToInt16(data, mTexCoordsOffset) / 0x1000);
                            TexCoords.Add((Single)BitConverter.ToInt16(data, mTexCoordsOffset + 2) / 0x1000);

                            Int32 mNormalsOffset = mOffset + 120 + i * 8;        // Normal数据起始位置
                            Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset) / 0x1000);
                            Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset + 2) / 0x1000);
                            Normals.Add(-(Single)BitConverter.ToInt16(data, mNormalsOffset + 4) / 0x1000);

                            Int32 mVertsOffset = mOffset + 68 + i * 16;        // Vertex数据起始位置
                            Verts.Add(BitConverter.ToSingle(data, mVertsOffset));
                            Verts.Add(BitConverter.ToSingle(data, mVertsOffset + 4));
                            Verts.Add(BitConverter.ToSingle(data, mVertsOffset + 8));
                        }
                        mOffset += 224;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        public SM()
        {
            InitializeComponent();
        }
        public IntPtr GetHwnd()
        {
            return panel1.Handle;
        }
        public void Analysis_SM()
        {
            if (data == null)
                return;

            Verts = new List<Single>();
            Normals = new List<Single>();
            TexCoords = new List<Single>();
            Parts = new List<SMPart>();
            Int32 mOffset = 0;
            mOffset = BitConverter.ToInt32(data, 20);              // Model.Offset

            LoadSMPart(mOffset, -1);
            /*
            float[] Vesout = new float[Verts.Count];
            float[] Norout = new float[Verts.Count];
            float[] Texout = new float[TexCoords.Count];
            float[] PartTR = new float[Parts.Count*6];
            int[] PartInfo = new int[Parts.Count*3];
            */

            Vesout = new float[Verts.Count];
            Norout = new float[Verts.Count];
            Texout = new float[TexCoords.Count];
            PartTR = new float[Parts.Count * 6];
            PartInfo = new int[Parts.Count * 3];

            for (int i = 0; i < TexCoords.Count; i++)
            {
                Texout[i] = TexCoords[i];
            }
            for (int i = 0; i < Verts.Count; i++)
            {
                Vesout[i] = Verts[i];
                Norout[i] = Normals[i];
            }
            cboxPart.Items.Clear();
            cboxPart.Items.Add("All Part, Verts:" + (Verts.Count / 3).ToString() + ", Parts:" + Parts.Count.ToString());
            cboxPart.SelectedIndex = 0;
            for (int i = 0; i < Parts.Count; i++)
            {
                PartTR[i * 6] = Parts[i].Pos[0];
                PartTR[i * 6 + 1] = Parts[i].Pos[1];
                PartTR[i * 6 + 2] = Parts[i].Pos[2];

                PartTR[i * 6 + 3] = Parts[i].Rot[0];
                PartTR[i * 6 + 4] = Parts[i].Rot[1];
                PartTR[i * 6 + 5] = Parts[i].Rot[2];

                PartInfo[i * 3] = Parts[i].subPartCount;
                PartInfo[i * 3 + 1] = Parts[i].vertStartID;
                PartInfo[i * 3 + 2] = Parts[i].vertCount;

                cboxPart.Items.Add("Part_" + i.ToString() + 
                                 ", Verts:" + Parts[i].vertCount.ToString() + 
                                 ", PID:" + Parts[i].parentID.ToString() + 
                                 ", Sub:" + Parts[i].subPartCount.ToString() + 
                                 ", POS:" + Parts[i].Pos[0] + ", " + Parts[i].Pos[1] + ", " + Parts[i].Pos[2] + 
                                 ", ROT:" + Parts[i].Rot[0] + ", " + Parts[i].Rot[1] + ", " + Parts[i].Rot[2] + 
                                 ";");
            }
            
            
            
            Set3DData(Vesout, Norout, Vesout.Length, Texout, TexCoords.Count);
            SetPartData(PartTR, PartInfo, Parts.Count);

            RenderPart(0);

            //Verts.Clear();
            //Normals.Clear();
            //TexCoords.Clear();
            //Parts.Clear();

        }

        private Int32 RenderPart(Int32 PartID)
        {
            Int32 mNextID = PartID + 1;
            Int32 mSubCount = PartInfo[PartID*3];

            for (Int32 i = 0; i < mSubCount; i++)
            {
                mNextID = RenderPart(mNextID);
            }
            return mNextID;
        }



        private void cboxPart_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboxPart.SelectedIndex > 0)
            {
                Int32 sel = cboxPart.SelectedIndex - 1;
                if (sel > Parts.Count -1)
                    sel = Parts.Count -1;

                float[] mPartTR = new float[6];
                int[] mPartInfo = new int[3];

                mPartTR[0] = Parts[sel].Pos[0];
                mPartTR[1] = Parts[sel].Pos[1];
                mPartTR[2] = Parts[sel].Pos[2];

                mPartTR[3] = Parts[sel].Rot[0];
                mPartTR[4] = Parts[sel].Rot[1];
                mPartTR[5] = Parts[sel].Rot[2];

                mPartInfo[0] = 0;
                mPartInfo[1] = Parts[sel].vertStartID;
                mPartInfo[2] = Parts[sel].vertCount;

                SetPartData(mPartTR, mPartInfo, 1);
            }
            else
            {
                SetPartData(PartTR, PartInfo, Parts.Count);
            }

        }
        public void Set3Dwin(Control control)
        {
            panel1.Controls.Add(control);
        }
        public void Unset3Dwin()
        {
            panel1.Controls.Clear();
        }
    }
}
