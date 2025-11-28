using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Opt
{
    public partial class splash : Form
    {
        public splash()
        {
            InitializeComponent();
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public Size SizeofForm { get; set; }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public Vector2 LocationofForm { get; set; }
        private readonly System.Windows.Forms.Timer Timer1 = new();
        private readonly System.Windows.Forms.Timer Timer2 = new();
        private readonly System.Windows.Forms.Timer Timer0= new();
        private void splash_Load(object sender, EventArgs e)
        {
            this.Left = (int)this.LocationofForm.X;
            this.Top = (int)this.LocationofForm.Y;
            this.Size = SizeofForm;


            
            Timer1.Interval= 500;
            Timer1.Tick += Timer1_Tick;
            Timer1.Start();
            Timer0.Interval = 10;
            Timer0.Tick += Timer0_Tick;
            Timer0.Start();

        }

        private void Timer0_Tick(object? sender, EventArgs e)
        {
            this.StartPosition = FormStartPosition.CenterScreen;
            this.Left = (int)this.LocationofForm.X;
            this.Top = (int)this.LocationofForm.Y;
            //this.FormBorderStyle = FormBorderStyle.None;
        }

        private void Timer1_Tick(object? sender, EventArgs e)
        {
            Timer1.Stop();
            Timer2.Interval = 10;
            Timer2.Tick += Timer2_Tick;
            Timer2.Start();

        }

        private void Timer2_Tick(object? sender, EventArgs e)
        {
            Opacity -= .1;
            if (Opacity < 0.1)
            {
                Opacity = 0.1;
                this.Close();
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
