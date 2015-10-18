namespace AC4Analysis
{
    partial class ViewWin
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
            this.rbView1 = new System.Windows.Forms.RadioButton();
            this.rbView2 = new System.Windows.Forms.RadioButton();
            this.tbFov = new System.Windows.Forms.TextBox();
            this.lblFov = new System.Windows.Forms.Label();
            this.lblWidth = new System.Windows.Forms.Label();
            this.tbWidth = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tbHeight = new System.Windows.Forms.TextBox();
            this.btnOK = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // rbView1
            // 
            this.rbView1.AutoSize = true;
            this.rbView1.Checked = true;
            this.rbView1.Location = new System.Drawing.Point(13, 13);
            this.rbView1.Name = "rbView1";
            this.rbView1.Size = new System.Drawing.Size(89, 16);
            this.rbView1.TabIndex = 0;
            this.rbView1.TabStop = true;
            this.rbView1.Text = "Perspective";
            this.rbView1.UseVisualStyleBackColor = true;
            this.rbView1.CheckedChanged += new System.EventHandler(this.rbView1_CheckedChanged);
            // 
            // rbView2
            // 
            this.rbView2.AutoSize = true;
            this.rbView2.Location = new System.Drawing.Point(13, 54);
            this.rbView2.Name = "rbView2";
            this.rbView2.Size = new System.Drawing.Size(83, 16);
            this.rbView2.TabIndex = 1;
            this.rbView2.Text = "Orthogonal";
            this.rbView2.UseVisualStyleBackColor = true;
            this.rbView2.CheckedChanged += new System.EventHandler(this.rbView2_CheckedChanged);
            // 
            // tbFov
            // 
            this.tbFov.Location = new System.Drawing.Point(163, 12);
            this.tbFov.Name = "tbFov";
            this.tbFov.Size = new System.Drawing.Size(44, 21);
            this.tbFov.TabIndex = 2;
            this.tbFov.Text = "45";
            // 
            // lblFov
            // 
            this.lblFov.AutoSize = true;
            this.lblFov.Location = new System.Drawing.Point(131, 15);
            this.lblFov.Name = "lblFov";
            this.lblFov.Size = new System.Drawing.Size(23, 12);
            this.lblFov.TabIndex = 3;
            this.lblFov.Text = "Fov";
            // 
            // lblWidth
            // 
            this.lblWidth.AutoSize = true;
            this.lblWidth.Location = new System.Drawing.Point(111, 56);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(35, 12);
            this.lblWidth.TabIndex = 5;
            this.lblWidth.Text = "Width";
            // 
            // tbWidth
            // 
            this.tbWidth.Enabled = false;
            this.tbWidth.Location = new System.Drawing.Point(146, 53);
            this.tbWidth.Name = "tbWidth";
            this.tbWidth.Size = new System.Drawing.Size(44, 21);
            this.tbWidth.TabIndex = 4;
            this.tbWidth.Text = "640";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(195, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 7;
            this.label3.Text = "Height";
            // 
            // tbHeight
            // 
            this.tbHeight.Enabled = false;
            this.tbHeight.Location = new System.Drawing.Point(236, 53);
            this.tbHeight.Name = "tbHeight";
            this.tbHeight.Size = new System.Drawing.Size(44, 21);
            this.tbHeight.TabIndex = 6;
            this.tbHeight.Text = "480";
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(103, 80);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 8;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // ViewWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 109);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tbHeight);
            this.Controls.Add(this.lblWidth);
            this.Controls.Add(this.tbWidth);
            this.Controls.Add(this.lblFov);
            this.Controls.Add(this.tbFov);
            this.Controls.Add(this.rbView2);
            this.Controls.Add(this.rbView1);
            this.Name = "ViewWin";
            this.Text = "ViewWin";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbView1;
        private System.Windows.Forms.RadioButton rbView2;
        private System.Windows.Forms.TextBox tbFov;
        private System.Windows.Forms.Label lblFov;
        private System.Windows.Forms.Label lblWidth;
        private System.Windows.Forms.TextBox tbWidth;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbHeight;
        private System.Windows.Forms.Button btnOK;
    }
}