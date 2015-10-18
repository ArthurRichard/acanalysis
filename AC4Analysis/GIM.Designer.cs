namespace AC4Analysis
{
    partial class GIM
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.btn保存图像 = new System.Windows.Forms.Button();
            this.btn导入图像 = new System.Windows.Forms.Button();
            this.btn保存非调色板图像 = new System.Windows.Forms.Button();
            this.btn在3D窗口里使用 = new System.Windows.Forms.Button();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 4);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "label1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(4, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "label2";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(0, 35);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(605, 522);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // btn保存图像
            // 
            this.btn保存图像.Location = new System.Drawing.Point(133, 6);
            this.btn保存图像.Name = "btn保存图像";
            this.btn保存图像.Size = new System.Drawing.Size(75, 23);
            this.btn保存图像.TabIndex = 3;
            this.btn保存图像.Text = "Save Image";
            this.btn保存图像.UseVisualStyleBackColor = true;
            this.btn保存图像.Click += new System.EventHandler(this.btn保存图像_Click);
            // 
            // btn导入图像
            // 
            this.btn导入图像.Location = new System.Drawing.Point(214, 6);
            this.btn导入图像.Name = "btn导入图像";
            this.btn导入图像.Size = new System.Drawing.Size(86, 23);
            this.btn导入图像.TabIndex = 4;
            this.btn导入图像.Text = "Import Image";
            this.btn导入图像.UseVisualStyleBackColor = true;
            this.btn导入图像.Click += new System.EventHandler(this.btn导入图像_Click);
            // 
            // btn保存非调色板图像
            // 
            this.btn保存非调色板图像.Location = new System.Drawing.Point(307, 6);
            this.btn保存非调色板图像.Name = "btn保存非调色板图像";
            this.btn保存非调色板图像.Size = new System.Drawing.Size(155, 23);
            this.btn保存非调色板图像.TabIndex = 5;
            this.btn保存非调色板图像.Text = "Save no palette image ";
            this.btn保存非调色板图像.UseVisualStyleBackColor = true;
            this.btn保存非调色板图像.Click += new System.EventHandler(this.btn保存非调色板图像_Click);
            // 
            // btn在3D窗口里使用
            // 
            this.btn在3D窗口里使用.Location = new System.Drawing.Point(469, 5);
            this.btn在3D窗口里使用.Name = "btn在3D窗口里使用";
            this.btn在3D窗口里使用.Size = new System.Drawing.Size(75, 23);
            this.btn在3D窗口里使用.TabIndex = 6;
            this.btn在3D窗口里使用.Text = "Use In 3D";
            this.btn在3D窗口里使用.UseVisualStyleBackColor = true;
            this.btn在3D窗口里使用.Click += new System.EventHandler(this.btn在3D窗口里使用_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Location = new System.Drawing.Point(597, 35);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(8, 8);
            this.pictureBox2.TabIndex = 7;
            this.pictureBox2.TabStop = false;
            this.pictureBox2.Visible = false;
            // 
            // GIM
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.btn在3D窗口里使用);
            this.Controls.Add(this.btn保存非调色板图像);
            this.Controls.Add(this.btn导入图像);
            this.Controls.Add(this.btn保存图像);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "GIM";
            this.Size = new System.Drawing.Size(605, 557);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btn保存图像;
        private System.Windows.Forms.Button btn导入图像;
        private System.Windows.Forms.Button btn保存非调色板图像;
        private System.Windows.Forms.Button btn在3D窗口里使用;
        private System.Windows.Forms.PictureBox pictureBox2;
    }
}
