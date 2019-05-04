using System;
using System.Windows.Forms;

namespace CSharp_OpenCV
{
    public partial class Form3 : Form
    {

        private Timer _timer;
        private Form1 _form;
        public Form3()
        {
            InitializeComponent();

            _form = new Form1();
            _form.FormClosed += _form_FormClosed;

            _timer = new Timer();
            _timer.Interval = 2000;
            _timer.Tick += _timer_Tick;
        }

        private void _form_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Close();
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            _timer.Stop();
            _timer.Dispose();


            this.Hide();
            _form.Show();
        }

        private void Form3_Load(object sender, EventArgs e)
        {
            _timer.Start();
        }
    }
}
