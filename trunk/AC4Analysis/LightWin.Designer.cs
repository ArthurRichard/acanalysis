namespace AC4Analysis
{
    partial class LightWin
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.cb开启光源 = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnSPECULAR = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.btnDIFFUSE = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.btnEMISSION = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.btnAMBIENT = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.tbSHININESS = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.btnSPECULAR_Light = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.btnDIFFUSE_Light = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.btnAMBIENT_Light = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.tbPosX = new System.Windows.Forms.TextBox();
            this.tbPosY = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.tbPosZ = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "Light0",
            "Light1",
            "Light2",
            "Light3",
            "Light4",
            "Light5",
            "Light6",
            "Light7"});
            this.comboBox1.Location = new System.Drawing.Point(13, 114);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(78, 20);
            this.comboBox1.TabIndex = 0;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // cb开启光源
            // 
            this.cb开启光源.AutoSize = true;
            this.cb开启光源.Location = new System.Drawing.Point(111, 118);
            this.cb开启光源.Name = "cb开启光源";
            this.cb开启光源.Size = new System.Drawing.Size(60, 16);
            this.cb开启光源.TabIndex = 1;
            this.cb开启光源.Text = "Enable";
            this.cb开启光源.UseVisualStyleBackColor = true;
            this.cb开启光源.CheckedChanged += new System.EventHandler(this.cb开启光源_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnSPECULAR);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.btnDIFFUSE);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.btnEMISSION);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.btnAMBIENT);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.tbSHININESS);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(400, 81);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Material";
            // 
            // btnSPECULAR
            // 
            this.btnSPECULAR.BackColor = System.Drawing.SystemColors.ControlText;
            this.btnSPECULAR.Location = new System.Drawing.Point(327, 14);
            this.btnSPECULAR.Name = "btnSPECULAR";
            this.btnSPECULAR.Size = new System.Drawing.Size(24, 20);
            this.btnSPECULAR.TabIndex = 9;
            this.btnSPECULAR.UseVisualStyleBackColor = false;
            this.btnSPECULAR.Click += new System.EventHandler(this.btnSPECULAR_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(272, 18);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "SPECULAR";
            // 
            // btnDIFFUSE
            // 
            this.btnDIFFUSE.BackColor = System.Drawing.SystemColors.ControlText;
            this.btnDIFFUSE.Location = new System.Drawing.Point(202, 13);
            this.btnDIFFUSE.Name = "btnDIFFUSE";
            this.btnDIFFUSE.Size = new System.Drawing.Size(24, 20);
            this.btnDIFFUSE.TabIndex = 7;
            this.btnDIFFUSE.UseVisualStyleBackColor = false;
            this.btnDIFFUSE.Click += new System.EventHandler(this.btnDIFFUSE_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(147, 17);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "DIFFUSE";
            // 
            // btnEMISSION
            // 
            this.btnEMISSION.BackColor = System.Drawing.SystemColors.ControlText;
            this.btnEMISSION.Location = new System.Drawing.Point(327, 45);
            this.btnEMISSION.Name = "btnEMISSION";
            this.btnEMISSION.Size = new System.Drawing.Size(24, 20);
            this.btnEMISSION.TabIndex = 5;
            this.btnEMISSION.UseVisualStyleBackColor = false;
            this.btnEMISSION.Click += new System.EventHandler(this.btnEMISSION_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(272, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "EMISSION";
            // 
            // btnAMBIENT
            // 
            this.btnAMBIENT.BackColor = System.Drawing.SystemColors.ControlText;
            this.btnAMBIENT.Location = new System.Drawing.Point(202, 45);
            this.btnAMBIENT.Name = "btnAMBIENT";
            this.btnAMBIENT.Size = new System.Drawing.Size(24, 20);
            this.btnAMBIENT.TabIndex = 3;
            this.btnAMBIENT.UseVisualStyleBackColor = false;
            this.btnAMBIENT.Click += new System.EventHandler(this.btnAMBIENT_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(147, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "AMBIENT";
            // 
            // tbSHININESS
            // 
            this.tbSHININESS.Location = new System.Drawing.Point(63, 14);
            this.tbSHININESS.MaxLength = 20;
            this.tbSHININESS.Name = "tbSHININESS";
            this.tbSHININESS.Size = new System.Drawing.Size(47, 21);
            this.tbSHININESS.TabIndex = 1;
            this.tbSHININESS.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBox1_KeyUp);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "SHININESS";
            // 
            // btnSPECULAR_Light
            // 
            this.btnSPECULAR_Light.BackColor = System.Drawing.SystemColors.ControlText;
            this.btnSPECULAR_Light.Location = new System.Drawing.Point(192, 150);
            this.btnSPECULAR_Light.Name = "btnSPECULAR_Light";
            this.btnSPECULAR_Light.Size = new System.Drawing.Size(21, 20);
            this.btnSPECULAR_Light.TabIndex = 13;
            this.btnSPECULAR_Light.UseVisualStyleBackColor = false;
            this.btnSPECULAR_Light.Click += new System.EventHandler(this.btnSPECULAR_Light_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(137, 154);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 12;
            this.label6.Text = "SPECULAR";
            // 
            // btnDIFFUSE_Light
            // 
            this.btnDIFFUSE_Light.BackColor = System.Drawing.SystemColors.ControlText;
            this.btnDIFFUSE_Light.Location = new System.Drawing.Point(67, 149);
            this.btnDIFFUSE_Light.Name = "btnDIFFUSE_Light";
            this.btnDIFFUSE_Light.Size = new System.Drawing.Size(21, 20);
            this.btnDIFFUSE_Light.TabIndex = 11;
            this.btnDIFFUSE_Light.UseVisualStyleBackColor = false;
            this.btnDIFFUSE_Light.Click += new System.EventHandler(this.btnDIFFUSE_Light_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 153);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(47, 12);
            this.label7.TabIndex = 10;
            this.label7.Text = "DIFFUSE";
            // 
            // btnAMBIENT_Light
            // 
            this.btnAMBIENT_Light.BackColor = System.Drawing.SystemColors.ControlText;
            this.btnAMBIENT_Light.Location = new System.Drawing.Point(323, 149);
            this.btnAMBIENT_Light.Name = "btnAMBIENT_Light";
            this.btnAMBIENT_Light.Size = new System.Drawing.Size(24, 20);
            this.btnAMBIENT_Light.TabIndex = 11;
            this.btnAMBIENT_Light.UseVisualStyleBackColor = false;
            this.btnAMBIENT_Light.Click += new System.EventHandler(this.btnAMBIENT_Light_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(268, 153);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 10;
            this.label8.Text = "AMBIENT";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 194);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(35, 12);
            this.label9.TabIndex = 14;
            this.label9.Text = "Pos X";
            // 
            // tbPosX
            // 
            this.tbPosX.Location = new System.Drawing.Point(58, 191);
            this.tbPosX.Name = "tbPosX";
            this.tbPosX.Size = new System.Drawing.Size(47, 21);
            this.tbPosX.TabIndex = 15;
            this.tbPosX.KeyUp += new System.Windows.Forms.KeyEventHandler(this.tbPos_KeyUp);
            // 
            // tbPosY
            // 
            this.tbPosY.Location = new System.Drawing.Point(166, 191);
            this.tbPosY.Name = "tbPosY";
            this.tbPosY.Size = new System.Drawing.Size(47, 21);
            this.tbPosY.TabIndex = 17;
            this.tbPosY.KeyUp += new System.Windows.Forms.KeyEventHandler(this.tbPos_KeyUp);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(120, 194);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 12);
            this.label10.TabIndex = 16;
            this.label10.Text = "Pos Y";
            // 
            // tbPosZ
            // 
            this.tbPosZ.Location = new System.Drawing.Point(287, 191);
            this.tbPosZ.Name = "tbPosZ";
            this.tbPosZ.Size = new System.Drawing.Size(47, 21);
            this.tbPosZ.TabIndex = 19;
            this.tbPosZ.KeyUp += new System.Windows.Forms.KeyEventHandler(this.tbPos_KeyUp);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(241, 194);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(35, 12);
            this.label11.TabIndex = 18;
            this.label11.Text = "Pos Z";
            // 
            // LightWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(425, 247);
            this.Controls.Add(this.tbPosZ);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.tbPosY);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.tbPosX);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.btnAMBIENT_Light);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.btnSPECULAR_Light);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.cb开启光源);
            this.Controls.Add(this.btnDIFFUSE_Light);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label7);
            this.MaximizeBox = false;
            this.Name = "LightWin";
            this.ShowIcon = false;
            this.Text = "Light";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.CheckBox cb开启光源;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbSHININESS;
        private System.Windows.Forms.Button btnAMBIENT;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Button btnSPECULAR;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btnDIFFUSE;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnEMISSION;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnSPECULAR_Light;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnDIFFUSE_Light;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button btnAMBIENT_Light;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox tbPosX;
        private System.Windows.Forms.TextBox tbPosY;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox tbPosZ;
        private System.Windows.Forms.Label label11;
    }
}