namespace AC4Analysis
{
    partial class EESub
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
            this.pictureBoxRGB = new System.Windows.Forms.PictureBox();
            this.pictureBoxAlpha = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxRGB)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxAlpha)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBoxRGB
            // 
            this.pictureBoxRGB.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.pictureBoxRGB.Location = new System.Drawing.Point(0, 0);
            this.pictureBoxRGB.Name = "pictureBoxRGB";
            this.pictureBoxRGB.Size = new System.Drawing.Size(215, 164);
            this.pictureBoxRGB.TabIndex = 0;
            this.pictureBoxRGB.TabStop = false;
            // 
            // pictureBoxAlpha
            // 
            this.pictureBoxAlpha.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.pictureBoxAlpha.Location = new System.Drawing.Point(221, 0);
            this.pictureBoxAlpha.Name = "pictureBoxAlpha";
            this.pictureBoxAlpha.Size = new System.Drawing.Size(215, 164);
            this.pictureBoxAlpha.TabIndex = 1;
            this.pictureBoxAlpha.TabStop = false;
            // 
            // EESub
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pictureBoxAlpha);
            this.Controls.Add(this.pictureBoxRGB);
            this.Name = "EESub";
            this.Size = new System.Drawing.Size(466, 164);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxRGB)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxAlpha)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBoxRGB;
        private System.Windows.Forms.PictureBox pictureBoxAlpha;
    }
}
