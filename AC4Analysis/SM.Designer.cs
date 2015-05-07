namespace AC4Analysis
{
    partial class SM
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.cboxPart = new System.Windows.Forms.ComboBox();
            this.txt旋转Z = new System.Windows.Forms.TextBox();
            this.txt旋转Y = new System.Windows.Forms.TextBox();
            this.txt旋转X = new System.Windows.Forms.TextBox();
            this.txt位置Z = new System.Windows.Forms.TextBox();
            this.txt位置Y = new System.Windows.Forms.TextBox();
            this.txt位置X = new System.Windows.Forms.TextBox();
            this.btn导出 = new System.Windows.Forms.Button();
            this.btn应用位置旋转 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.cbox单独设置 = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tb关键帧 = new System.Windows.Forms.TrackBar();
            this.txt部件类型 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.tb关键帧)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.AutoScroll = true;
            this.panel1.Location = new System.Drawing.Point(0, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(787, 608);
            this.panel1.TabIndex = 0;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // cboxPart
            // 
            this.cboxPart.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cboxPart.Font = new System.Drawing.Font("SimSun", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cboxPart.FormattingEnabled = true;
            this.cboxPart.Location = new System.Drawing.Point(3, 3);
            this.cboxPart.Name = "cboxPart";
            this.cboxPart.Size = new System.Drawing.Size(872, 19);
            this.cboxPart.TabIndex = 3;
            this.cboxPart.SelectedIndexChanged += new System.EventHandler(this.cboxPart_SelectedIndexChanged);
            // 
            // txt旋转Z
            // 
            this.txt旋转Z.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.txt旋转Z.Location = new System.Drawing.Point(814, 301);
            this.txt旋转Z.Name = "txt旋转Z";
            this.txt旋转Z.Size = new System.Drawing.Size(61, 20);
            this.txt旋转Z.TabIndex = 11;
            // 
            // txt旋转Y
            // 
            this.txt旋转Y.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.txt旋转Y.Location = new System.Drawing.Point(814, 272);
            this.txt旋转Y.Name = "txt旋转Y";
            this.txt旋转Y.Size = new System.Drawing.Size(61, 20);
            this.txt旋转Y.TabIndex = 10;
            // 
            // txt旋转X
            // 
            this.txt旋转X.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.txt旋转X.Location = new System.Drawing.Point(814, 243);
            this.txt旋转X.Name = "txt旋转X";
            this.txt旋转X.Size = new System.Drawing.Size(61, 20);
            this.txt旋转X.TabIndex = 9;
            // 
            // txt位置Z
            // 
            this.txt位置Z.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.txt位置Z.Location = new System.Drawing.Point(814, 202);
            this.txt位置Z.Name = "txt位置Z";
            this.txt位置Z.Size = new System.Drawing.Size(61, 20);
            this.txt位置Z.TabIndex = 8;
            // 
            // txt位置Y
            // 
            this.txt位置Y.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.txt位置Y.Location = new System.Drawing.Point(814, 172);
            this.txt位置Y.Name = "txt位置Y";
            this.txt位置Y.Size = new System.Drawing.Size(61, 20);
            this.txt位置Y.TabIndex = 7;
            // 
            // txt位置X
            // 
            this.txt位置X.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.txt位置X.Location = new System.Drawing.Point(814, 143);
            this.txt位置X.Name = "txt位置X";
            this.txt位置X.Size = new System.Drawing.Size(61, 20);
            this.txt位置X.TabIndex = 6;
            // 
            // btn导出
            // 
            this.btn导出.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.btn导出.Location = new System.Drawing.Point(793, 356);
            this.btn导出.Name = "btn导出";
            this.btn导出.Size = new System.Drawing.Size(82, 23);
            this.btn导出.TabIndex = 12;
            this.btn导出.Text = "Export";
            this.btn导出.UseVisualStyleBackColor = true;
            this.btn导出.Click += new System.EventHandler(this.btn导出_Click);
            // 
            // btn应用位置旋转
            // 
            this.btn应用位置旋转.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.btn应用位置旋转.Location = new System.Drawing.Point(793, 327);
            this.btn应用位置旋转.Name = "btn应用位置旋转";
            this.btn应用位置旋转.Size = new System.Drawing.Size(82, 23);
            this.btn应用位置旋转.TabIndex = 13;
            this.btn应用位置旋转.Text = "Apply";
            this.btn应用位置旋转.UseVisualStyleBackColor = true;
            this.btn应用位置旋转.Click += new System.EventHandler(this.btn应用位置旋转_Click);
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(793, 246);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(22, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "RX";
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(793, 275);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(22, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "RY";
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(793, 146);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(21, 13);
            this.label4.TabIndex = 17;
            this.label4.Text = "TX";
            // 
            // label5
            // 
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(793, 175);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(21, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "TY";
            // 
            // label6
            // 
            this.label6.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(793, 205);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(21, 13);
            this.label6.TabIndex = 19;
            this.label6.Text = "TZ";
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(793, 304);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(22, 13);
            this.label3.TabIndex = 16;
            this.label3.Text = "RZ";
            // 
            // cbox单独设置
            // 
            this.cbox单独设置.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.cbox单独设置.FormattingEnabled = true;
            this.cbox单独设置.Location = new System.Drawing.Point(793, 28);
            this.cbox单独设置.Name = "cbox单独设置";
            this.cbox单独设置.Size = new System.Drawing.Size(80, 21);
            this.cbox单独设置.TabIndex = 20;
            this.cbox单独设置.SelectedIndexChanged += new System.EventHandler(this.cbox单独设置_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(818, 52);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(28, 13);
            this.label7.TabIndex = 21;
            this.label7.Text = "SET";
            // 
            // tb关键帧
            // 
            this.tb关键帧.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.tb关键帧.LargeChange = 10;
            this.tb关键帧.Location = new System.Drawing.Point(782, 63);
            this.tb关键帧.Maximum = 100;
            this.tb关键帧.Name = "tb关键帧";
            this.tb关键帧.Size = new System.Drawing.Size(91, 45);
            this.tb关键帧.TabIndex = 22;
            this.tb关键帧.Scroll += new System.EventHandler(this.tb关键帧_Scroll);
            // 
            // txt部件类型
            // 
            this.txt部件类型.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.txt部件类型.Location = new System.Drawing.Point(793, 114);
            this.txt部件类型.Name = "txt部件类型";
            this.txt部件类型.Size = new System.Drawing.Size(82, 20);
            this.txt部件类型.TabIndex = 23;
            // 
            // label8
            // 
            this.label8.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(811, 98);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 13);
            this.label8.TabIndex = 24;
            this.label8.Text = "TYPE";
            // 
            // SM
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.txt部件类型);
            this.Controls.Add(this.tb关键帧);
            this.Controls.Add(this.cbox单独设置);
            this.Controls.Add(this.txt旋转Z);
            this.Controls.Add(this.txt旋转Y);
            this.Controls.Add(this.txt旋转X);
            this.Controls.Add(this.txt位置Z);
            this.Controls.Add(this.txt位置Y);
            this.Controls.Add(this.txt位置X);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn应用位置旋转);
            this.Controls.Add(this.btn导出);
            this.Controls.Add(this.cboxPart);
            this.Controls.Add(this.panel1);
            this.Name = "SM";
            this.Size = new System.Drawing.Size(878, 633);
            ((System.ComponentModel.ISupportInitialize)(this.tb关键帧)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ComboBox cboxPart;
        private System.Windows.Forms.TextBox txt旋转Z;
        private System.Windows.Forms.TextBox txt旋转Y;
        private System.Windows.Forms.TextBox txt旋转X;
        private System.Windows.Forms.TextBox txt位置Z;
        private System.Windows.Forms.TextBox txt位置Y;
        private System.Windows.Forms.TextBox txt位置X;
        private System.Windows.Forms.Button btn导出;
        private System.Windows.Forms.Button btn应用位置旋转;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cbox单独设置;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TrackBar tb关键帧;
        private System.Windows.Forms.TextBox txt部件类型;
        private System.Windows.Forms.Label label8;

    }
}
