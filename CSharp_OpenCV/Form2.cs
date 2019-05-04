using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace CSharp_OpenCV
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            LinQDataContext lq = new LinQDataContext();
            dataGridView1.DataSource = from data_table in lq.MIAs
                                       select new
                                       {
                                           data_table.ID,
                                           data_table.Image_Name,
                                           data_table.Sekil_Sayisi,
                                           data_table.Renk_Sayisi,
                                           data_table.Resim,
                                           data_table.Tarih

                                       };
        }
    }
}
