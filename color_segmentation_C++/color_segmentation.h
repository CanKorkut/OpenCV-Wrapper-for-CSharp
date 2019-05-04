#pragma once

#include "opencv2\opencv.hpp"
#include <string>
#include <windows.h> // BYTE Sýnýfý için

using namespace cv;

namespace MIA
{
			class image_process {
			private:
				Mat image;
			public:
				int colors;																					// Renk Sayýsýný Tutar
				int colors_shape [10];																		// Renklere Göre Þekil Sayýsýný Tutar
				Mat img_sonuc;																				// Sonucun Yazýldýðý Frame
				image_process(std::string Path);															// Constructor (Path Alýr)	
				image_process();																			// Constructor 
				int get_color();																			// Colors deðiþkenini döndürür.
				int* get_colors_shape();																	// Renklere Göre þekil sayýlarýnýn tutulduðu diziyi döndürür.
				Mat mask_frame(Mat frame, Scalar lowwer, Scalar upper);										// inRange fonksiyonunu çalýþtýrýr.
				Mat dilated_images(Mat frame, int element_size);											// Þekilleri Bütünleþtirir.
				void set_image(std::string path);															// Kaynak Resmi Deðiþtirir.
				Mat get_image();																			// Kaynak Resmi Döndürür.
				BYTE* mat_sonuc(Mat mat);																	// Sonucun Yazýldýðý Frame'in Byte Datasýnýn Tutuldðu Dizinin Adresini Döndürür.
				Mat RGB2HSV(Mat mat);																		// Örnek Amaçlý fonksiyon
				Mat BitmapToMat(BYTE * pArray, int nSize, int image_width, int image_height, int Channel);  // C# Bitmap resmin Byte Datalarýnýn Adresini Alarak  memcp fonksiyonu ile Mata Dönüþtürür.
				BYTE* MatToByte(Mat mat, int image_height, int image_width,int Channel);					// C++ da Mat datayý Byte Aray dönüþtürüp adresi  return eder.
				int  find_contours_numbers(Mat frame);														// Framedeki contour sayýsýný sayar.
				void find_color(Mat frame);																	// Yukarýdaki fonksiyonlarýn çaðrýldýðý ana fonksiyon

			};
}


