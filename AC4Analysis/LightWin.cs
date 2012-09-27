using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace AC4Analysis
{
    
    public partial class LightWin : Form
    {
        public LightWin()
        {
            InitializeComponent();
            tbSHININESS.Text = "90";
            MaterialData[0] = MaterialData[1] = MaterialData[2] = 0.8f; MaterialData[3] = 1.0f;
            MaterialData[4] = MaterialData[5] = MaterialData[6] = 1.0f; MaterialData[7] = 1.0f;
            MaterialData[8] = MaterialData[9] = MaterialData[10] = 0.2f; MaterialData[11] = 1.0f;
            MaterialData[12] = MaterialData[13] = MaterialData[14] = 0.0f; MaterialData[15] = 1.0f;
            MaterialData[16] = 90.0f;
            SetMaterial(MaterialData);
            LightSwitch[0] = true;
            SetLightSwitch(0, true);

            for (int i = 0; i < 8; i++)
            {
                LightData[i].data = new float[16];
                for (int j = 0; j < 16; j++)
                {
                    LightData[i].data[j] = 1.0f;
                }
                LightData[i].data[12] = 100.0f; LightData[i].data[13] = -100.0f; LightData[i].data[14] = 0.0f;
            }
            SetLight(0, LightData[0].data);
            
            btnDIFFUSE.BackColor = Color.FromArgb((int)(MaterialData[0] * 255.0f), (int)(MaterialData[1] * 255.0f), (int)(MaterialData[2] * 255.0f));
            btnSPECULAR.BackColor = Color.FromArgb((int)(MaterialData[4] * 255.0f), (int)(MaterialData[5] * 255.0f), (int)(MaterialData[6] * 255.0f));
            btnAMBIENT.BackColor = Color.FromArgb((int)(MaterialData[8] * 255.0f), (int)(MaterialData[9] * 255.0f), (int)(MaterialData[10] * 255.0f));
            btnEMISSION.BackColor = Color.FromArgb((int)(MaterialData[12] * 255.0f), (int)(MaterialData[13] * 255.0f), (int)(MaterialData[14] * 255.0f));
        }

        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMaterial(float [] Data);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetLightSwitch(int LightID, bool Switch);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetLight(int LightID, float[] Data);
        float[] MaterialData = new float[17];//DIFFUSE:0,SPECULAR:4,AMBIENT:8,EMISSION:12,SHININESS:16
        struct _LightData
        { 
            public float[] data;
        }
        int matid = 0;
        _LightData[] LightData = new _LightData[8];
        bool[] LightSwitch = new bool[8];
        private void textBox1_KeyUp(object sender, KeyEventArgs e)
        {
            float SHININESS;
            if (float.TryParse(tbSHININESS.Text, out SHININESS) == false)
            {
                MessageBox.Show("Must number only");
            }
            else
            {
                if (SHININESS < 128.0f)
                {
                    MaterialData[16] = SHININESS;
                    SetMaterial(MaterialData);
                }
                else
                    MessageBox.Show("Must low than 128");
            }
        }

        private void btnDIFFUSE_Click(object sender, EventArgs e)
        {
            matid = 0;
            colorDialog1.Color = btnDIFFUSE.BackColor;
            colorDialog1.ShowDialog();
            btnDIFFUSE.BackColor = colorDialog1.Color;
            MaterialData[matid + 0] = (float)colorDialog1.Color.R / 255.0f;
            MaterialData[matid + 1] = (float)colorDialog1.Color.G / 255.0f;
            MaterialData[matid + 2] = (float)colorDialog1.Color.B / 255.0f;
            SetMaterial(MaterialData);
        }

        private void btnSPECULAR_Click(object sender, EventArgs e)
        {
            matid = 4;
            colorDialog1.Color = btnSPECULAR.BackColor;
            colorDialog1.ShowDialog();
            btnSPECULAR.BackColor = colorDialog1.Color;
            MaterialData[matid + 0] = (float)colorDialog1.Color.R / 255.0f;
            MaterialData[matid + 1] = (float)colorDialog1.Color.G / 255.0f;
            MaterialData[matid + 2] = (float)colorDialog1.Color.B / 255.0f;
            SetMaterial(MaterialData);
        }

        private void btnAMBIENT_Click(object sender, EventArgs e)
        {
            matid = 8;
            colorDialog1.Color = btnAMBIENT.BackColor;
            colorDialog1.ShowDialog();
            btnAMBIENT.BackColor = colorDialog1.Color;
            MaterialData[matid + 0] = (float)colorDialog1.Color.R / 255.0f;
            MaterialData[matid + 1] = (float)colorDialog1.Color.G / 255.0f;
            MaterialData[matid + 2] = (float)colorDialog1.Color.B / 255.0f;
            SetMaterial(MaterialData);
        }

        private void btnEMISSION_Click(object sender, EventArgs e)
        {
            matid = 12;
            colorDialog1.Color = btnEMISSION.BackColor;
            colorDialog1.ShowDialog();
            btnEMISSION.BackColor = colorDialog1.Color;
            MaterialData[matid + 0] = (float)colorDialog1.Color.R / 255.0f;
            MaterialData[matid + 1] = (float)colorDialog1.Color.G / 255.0f;
            MaterialData[matid + 2] = (float)colorDialog1.Color.B / 255.0f;
            SetMaterial(MaterialData);
        }

        private void btnDIFFUSE_Light_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex < 0)
                return;
            int id = comboBox1.SelectedIndex;
            matid = 0;
            colorDialog1.Color = btnDIFFUSE_Light.BackColor;
            colorDialog1.ShowDialog();
            btnDIFFUSE_Light.BackColor = colorDialog1.Color;
            LightData[id].data[matid + 0] = (float)colorDialog1.Color.R / 255.0f;
            LightData[id].data[matid + 1] = (float)colorDialog1.Color.G / 255.0f;
            LightData[id].data[matid + 2] = (float)colorDialog1.Color.B / 255.0f;
            SetLight(id, LightData[id].data);

        }

        private void btnSPECULAR_Light_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex < 0)
                return;
            int id = comboBox1.SelectedIndex;
            matid = 4;
            colorDialog1.Color = btnSPECULAR_Light.BackColor;
            colorDialog1.ShowDialog();
            btnSPECULAR_Light.BackColor = colorDialog1.Color;
            LightData[id].data[matid + 0] = (float)colorDialog1.Color.R / 255.0f;
            LightData[id].data[matid + 1] = (float)colorDialog1.Color.G / 255.0f;
            LightData[id].data[matid + 2] = (float)colorDialog1.Color.B / 255.0f;
            SetLight(id, LightData[id].data);
        }

        private void btnAMBIENT_Light_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex < 0)
                return;
            int id = comboBox1.SelectedIndex;
            matid = 8;
            colorDialog1.Color = btnAMBIENT_Light.BackColor;
            colorDialog1.ShowDialog();
            btnAMBIENT_Light.BackColor = colorDialog1.Color;
            LightData[id].data[matid + 0] = (float)colorDialog1.Color.R / 255.0f;
            LightData[id].data[matid + 1] = (float)colorDialog1.Color.G / 255.0f;
            LightData[id].data[matid + 2] = (float)colorDialog1.Color.B / 255.0f;
            SetLight(id, LightData[id].data);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex < 0)
                return;
            cb开启光源.Checked = LightSwitch[comboBox1.SelectedIndex];
            int id=comboBox1.SelectedIndex;
            btnDIFFUSE_Light.BackColor = Color.FromArgb((int)(LightData[id].data[0] * 255.0f), (int)(LightData[id].data[1] * 255.0f), (int)(LightData[id].data[2] * 255.0f));
            btnSPECULAR_Light.BackColor = Color.FromArgb((int)(LightData[id].data[4] * 255.0f), (int)(LightData[id].data[5] * 255.0f), (int)(LightData[id].data[6] * 255.0f));
            btnAMBIENT_Light.BackColor = Color.FromArgb((int)(LightData[id].data[8] * 255.0f), (int)(LightData[id].data[9] * 255.0f), (int)(LightData[id].data[10] * 255.0f));
            tbPosX.Text = LightData[id].data[12].ToString();
            tbPosY.Text = LightData[id].data[13].ToString();
            tbPosZ.Text = LightData[id].data[14].ToString();
        }

        private void cb开启光源_CheckedChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex < 0)
                return;
            SetLightSwitch(comboBox1.SelectedIndex, cb开启光源.Checked);
        }

        private void tbPos_KeyUp(object sender, KeyEventArgs e)
        {
            if (comboBox1.SelectedIndex < 0)
                return;
            float datatmp;
            if (float.TryParse(((TextBox)sender).Text, out datatmp) == false)
            {
                MessageBox.Show("Must number only");
                return;
            }
            int id = comboBox1.SelectedIndex;
            if (tbPosX == sender)
            {
                LightData[id].data[12] = datatmp;
            }
            if (tbPosY == sender)
            {
                LightData[id].data[13] = datatmp;
            }
            if (tbPosZ == sender)
            {
                LightData[id].data[14] = datatmp;
            }
            SetLight(id, LightData[id].data);
        }
    }
}
