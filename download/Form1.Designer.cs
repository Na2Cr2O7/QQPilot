namespace download
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            if (disposing)
            {
                httpClient?.Dispose();
                cts?.Cancel();
                cts?.Dispose();
            }
            base.Dispose(disposing);
            base.Dispose(disposing);

        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            button1 = new Button();
            cancel = new Button();
            status = new Label();
            progressBar1 = new ProgressBar();
            label1 = new Label();
            textBox1 = new TextBox();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(23, 12);
            button1.Name = "button1";
            button1.Size = new Size(131, 40);
            button1.TabIndex = 0;
            button1.Text = "开始下载";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // cancel
            // 
            cancel.Location = new Point(23, 58);
            cancel.Name = "cancel";
            cancel.Size = new Size(131, 40);
            cancel.TabIndex = 1;
            cancel.Text = "取消";
            cancel.UseVisualStyleBackColor = true;
            cancel.Click += cancel_Click;
            // 
            // status
            // 
            status.AutoSize = true;
            status.Location = new Point(0, 142);
            status.Name = "status";
            status.Size = new Size(73, 28);
            status.TabIndex = 2;
            status.Text = "label1";
            status.Click += status_Click;
            // 
            // progressBar1
            // 
            progressBar1.Dock = DockStyle.Bottom;
            progressBar1.Location = new Point(0, 206);
            progressBar1.Name = "progressBar1";
            progressBar1.Size = new Size(510, 24);
            progressBar1.TabIndex = 3;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(192, 18);
            label1.Name = "label1";
            label1.Size = new Size(274, 56);
            label1.TabIndex = 4;
            label1.Text = "Ollama下载工具可以便捷\r\n地下载Ollama安装包到本地\r\n";
            // 
            // textBox1
            // 
            textBox1.BackColor = SystemColors.Menu;
            textBox1.BorderStyle = BorderStyle.None;
            textBox1.Location = new Point(0, 173);
            textBox1.Name = "textBox1";
            textBox1.ReadOnly = true;
            textBox1.Size = new Size(510, 27);
            textBox1.TabIndex = 5;
            textBox1.Text = "https://ollama.com/download/OllamaSetup.exe";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 28F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(510, 230);
            Controls.Add(textBox1);
            Controls.Add(label1);
            Controls.Add(progressBar1);
            Controls.Add(status);
            Controls.Add(cancel);
            Controls.Add(button1);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            Icon = (Icon)resources.GetObject("$this.Icon");
            MaximizeBox = false;
            Name = "Form1";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Ollama下载工具";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private Button cancel;
        private Label status;
        private ProgressBar progressBar1;
        private Label label1;
        private TextBox textBox1;
    }
}
