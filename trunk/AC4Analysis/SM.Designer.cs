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
            this.btn保存 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn保存
            // 
            this.btn保存.Location = new System.Drawing.Point(27, 16);
            this.btn保存.Name = "btn保存";
            this.btn保存.Size = new System.Drawing.Size(75, 23);
            this.btn保存.TabIndex = 0;
            this.btn保存.Text = "save";
            this.btn保存.UseVisualStyleBackColor = true;
            // 
            // SM
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btn保存);
            this.Name = "SM";
            this.Size = new System.Drawing.Size(489, 405);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn保存;
    }
}
