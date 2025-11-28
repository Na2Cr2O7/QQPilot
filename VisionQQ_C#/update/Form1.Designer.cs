namespace update
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
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            button1 = new Button();
            textBox1 = new TextBox();
            folder = new FolderBrowserDialog();
            button2 = new Button();
            label1 = new Label();
            status = new RichTextBox();
            label2 = new Label();
            vsNew = new Label();
            vsOld = new Label();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(34, 303);
            button1.Name = "button1";
            button1.Size = new Size(244, 40);
            button1.TabIndex = 0;
            button1.Text = "选择旧版本目录";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // textBox1
            // 
            textBox1.Enabled = false;
            textBox1.Location = new Point(34, 349);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(244, 34);
            textBox1.TabIndex = 1;
            // 
            // button2
            // 
            button2.Location = new Point(34, 389);
            button2.Name = "button2";
            button2.Size = new Size(244, 40);
            button2.TabIndex = 2;
            button2.Text = "迁移";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(73, 28);
            label1.TabIndex = 3;
            label1.Text = "label1";
            label1.Visible = false;
            // 
            // status
            // 
            status.BorderStyle = BorderStyle.None;
            status.Location = new Point(317, 23);
            status.Name = "status";
            status.Size = new Size(479, 406);
            status.TabIndex = 5;
            status.Text = "";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(24, 64);
            label2.Name = "label2";
            label2.Size = new Size(264, 84);
            label2.TabIndex = 6;
            label2.Text = "配置迁移工具能够把旧版本\r\n的VisionQQ升级到新版本\r\n并保留配置。";
            // 
            // vsNew
            // 
            vsNew.AutoSize = true;
            vsNew.Location = new Point(24, 161);
            vsNew.Name = "vsNew";
            vsNew.Size = new Size(26, 28);
            vsNew.TabIndex = 7;
            vsNew.Text = "V";
            // 
            // vsOld
            // 
            vsOld.AutoSize = true;
            vsOld.Location = new Point(24, 202);
            vsOld.Name = "vsOld";
            vsOld.Size = new Size(0, 28);
            vsOld.TabIndex = 8;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 28F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(808, 450);
            Controls.Add(vsOld);
            Controls.Add(vsNew);
            Controls.Add(label2);
            Controls.Add(status);
            Controls.Add(label1);
            Controls.Add(button2);
            Controls.Add(textBox1);
            Controls.Add(button1);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "Form1";
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "配置迁移";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private TextBox textBox1;
        private FolderBrowserDialog folder;
        private Button button2;
        private Label label1;
        private RichTextBox status;
        private Label label2;
        private Label vsNew;
        private Label vsOld;
    }
}
