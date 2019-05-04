using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;

namespace CSharp_Image_Process
{
    public class openCV
    {
        const string DLL = "Your C++ DLL Path";
       
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl,SetLastError =true)]
        public static  extern IntPtr mask_frame(IntPtr pArray, int nSize,int width,int height,int Channel);
        public IntPtr Csharp_get_image(IntPtr pArray, int nSize,int width,int height,int Channel)
        {
            return mask_frame( pArray,nSize,width,height,Channel);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl, SetLastError = true)]
        public static extern IntPtr RGB2HSV(IntPtr pArray, int nSize, int width, int height, int Channel);
        public IntPtr RGB_HSV(IntPtr pArray, int nSize, int width, int height, int Channel)
        {
            return RGB2HSV( pArray,  nSize,  width,  height,  Channel);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl, SetLastError = true)]
        public static extern void find_colors(IntPtr ptr, int nSize, int image_width, int image_height, int Channel);
        public void find_colors_contours(IntPtr ptr, int nSize, int image_width, int image_height, int Channel)
        {
             find_colors( ptr, nSize, image_width, image_height, Channel);
        }

        [DllImport(DLL)]
        public static extern int get_color();
        public int get_color_number()
        {
            return get_color();
        }
        
        [DllImport(DLL)]
        public static extern IntPtr get_colors_shape();
        public IntPtr  get_shapes()
        {
            return get_colors_shape();
        }


        [DllImport(DLL)]
        public static extern IntPtr mat_sonuc();
        public IntPtr img_sonuc()
        {
            return mat_sonuc();
        }


        public int channel_size;
        public int array_size;
        public IntPtr BitmapToPtr(Bitmap bitmap)
        {

            IntPtr ptr = IntPtr.Zero;

            PixelFormat pixelformat = bitmap.PixelFormat;

            switch (pixelformat)
            {
                case PixelFormat.Format24bppRgb:
                    channel_size = 3;
                    break;
                case PixelFormat.Format32bppArgb:
                    channel_size = 4;
                    break;
                default:
                    Console.WriteLine("Unknown format");
                    channel_size = 0;
                    break;


            }

            Console.WriteLine(bitmap.PixelFormat);
            if (channel_size != 0)
            {
                Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
                BitmapData bmpData = bitmap.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);
                ptr = bmpData.Scan0;
                array_size = bitmap.Width * bitmap.Height * 4;
            }

            return ptr;

        }

        public Bitmap PtrToBitmap(Bitmap bitmap, IntPtr ptr)
        {

            int Bitmap_Width = bitmap.Width;
            int Bitmap_Height = bitmap.Height;
            Bitmap bitmap_mat = new Bitmap(Bitmap_Width, Bitmap_Height, PixelFormat.Format32bppArgb);
            BitmapData bitmap_data = bitmap_mat.LockBits(new Rectangle(0, 0, Bitmap_Width, Bitmap_Height), ImageLockMode.WriteOnly, PixelFormat.Format32bppArgb);
            byte[] mat_frame = new byte[Bitmap_Width * Bitmap_Height * 4];
            Marshal.Copy(ptr, mat_frame, 0, Bitmap_Width * Bitmap_Height * 4);
            Marshal.Copy(mat_frame, 0, bitmap_data.Scan0, Bitmap_Width * Bitmap_Height * 4);
            bitmap_mat.UnlockBits(bitmap_data);
            return bitmap_mat;

        }

        public Bitmap process_bitmap(Bitmap bitmap)
        {
            IntPtr ptr = BitmapToPtr(bitmap);
            IntPtr mat_byte = Csharp_get_image(ptr, array_size, bitmap.Width, bitmap.Height, channel_size);
            Bitmap result_bitmap = PtrToBitmap(bitmap, mat_byte);
            return result_bitmap;
        }

        public Bitmap RGB2HSV(Bitmap bitmap)
        {
            IntPtr ptr = BitmapToPtr(bitmap);
            IntPtr mat_byte = RGB_HSV(ptr, array_size, bitmap.Width, bitmap.Height, channel_size);
            Bitmap result_bitmap = PtrToBitmap(bitmap, mat_byte);
            return result_bitmap;
        }

        public Bitmap sonuc(Bitmap bitmap)
        {
            IntPtr mat_byte = img_sonuc();
            Bitmap result_bitmap = PtrToBitmap(bitmap, mat_byte);
            return result_bitmap;
        }

        public void find_contours(Bitmap bitmap)
        {
            IntPtr ptr = BitmapToPtr(bitmap);
            find_colors_contours(ptr, array_size, bitmap.Width, bitmap.Height, channel_size);
        }

    }

}
