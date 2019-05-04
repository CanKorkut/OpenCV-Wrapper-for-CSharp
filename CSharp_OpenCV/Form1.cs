using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Drawing.Imaging;
using CSharp_Image_Process;
using System.Data.SqlClient;
using System.IO;

namespace CSharp_OpenCV
{
    public partial class Form1 : Form
    {
     
        CSharp_Image_Process.openCV cs = new openCV();
        SqlConnection con;
        openCV cv = new openCV();
        Form2 frm2 = new Form2();
        string img_name = "";
        Bitmap bmp;
        string path;

        // Adresini aldığı Frame'i Byte Arraye çevirir.
        public static byte[] GetPhoto(string filePath)
        {
            FileStream stream = new FileStream(
                filePath, FileMode.Open, FileAccess.Read);
            BinaryReader reader = new BinaryReader(stream);

            byte[] photo = reader.ReadBytes((int)stream.Length);

            reader.Close();
            stream.Close();

            return photo;
        }


        // Aldığı adresten isim bulur.
        public string path2name(string path)
        {
            string name = "";
            int index = 0;
            int index2 = 0;
            char[] path_array = path.ToCharArray();
            for (int i = 0; i < path_array.Length; i++)
            {
                if (path_array[i] == '.')
                {
                    index = i;
                }
                else if (path_array[i] == '\\')
                    index2 = i;
            }

            for (int i = index2 + 1; i < index; i++)
                name = name + path_array[i];
            return name;
        }
       
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openfile = new OpenFileDialog();
            if (openfile.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                path = openfile.FileName;
            }
            try
            {
                bmp = new Bitmap(path, true);
                img_name = path2name(path);
                pictureBox1.Image = bmp;
            }
            catch (ArgumentNullException)
            {
                Console.WriteLine("ArgumentNullException");
            }
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                bmp = new Bitmap(path, true);
                Console.WriteLine(path);
                Bitmap result_bitmap;
                result_bitmap = cs.RGB2HSV(bmp);
                pictureBox2.Height = result_bitmap.Height;
                pictureBox2.Width = result_bitmap.Width;
                pictureBox2.Image = result_bitmap;
            }
            catch(ArgumentNullException)
            {
                Console.WriteLine("ArgumentNullException");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            bmp = new Bitmap(path, true);
            cs.find_contours(bmp);
            Bitmap result_bitmap;
            result_bitmap = cs.sonuc(bmp);
            pictureBox2.Height = bmp.Height;
            pictureBox2.Width = bmp.Width;
            pictureBox2.Image = result_bitmap;

        }

        private void button4_Click(object sender, EventArgs e)
        {

            byte[] photo = GetPhoto(path);
            int renk_sayisi = cs.get_color_number();
            IntPtr ptr = cs.get_shapes();
            int[] array = new int[10];
            Marshal.Copy(ptr, array, 0, 10);
            string sekil_sayisi = "";
            int i = 0;
            while(array[i] != 0)
            {
                sekil_sayisi = sekil_sayisi  + array[i].ToString() + ",";
                i++;
            }
            Console.WriteLine(sekil_sayisi);
            string time = DateTime.Now.ToString("h:mm:ss tt");
    

            LinQDataContext lq = new LinQDataContext();
            MIA table = new MIA();
            table.Image_Name = img_name;
            table.Sekil_Sayisi = sekil_sayisi;
            table.Renk_Sayisi = renk_sayisi;
            table.Tarih = time;
            table.Resim = photo;
            lq.MIAs.InsertOnSubmit(table);
            lq.SubmitChanges();
            MessageBox.Show("Kayıt işlemi Başarılı");
            Console.WriteLine(time);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            frm2.Show();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}

