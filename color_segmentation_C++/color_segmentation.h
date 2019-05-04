#pragma once

#include "opencv2\opencv.hpp"
#include <string>
#include <windows.h> // BYTE S�n�f� i�in

using namespace cv;

namespace MIA
{
			class image_process {
			private:
				Mat image;
			public:
				int colors;																					// Renk Say�s�n� Tutar
				int colors_shape [10];																		// Renklere G�re �ekil Say�s�n� Tutar
				Mat img_sonuc;																				// Sonucun Yaz�ld��� Frame
				image_process(std::string Path);															// Constructor (Path Al�r)	
				image_process();																			// Constructor 
				int get_color();																			// Colors de�i�kenini d�nd�r�r.
				int* get_colors_shape();																	// Renklere G�re �ekil say�lar�n�n tutuldu�u diziyi d�nd�r�r.
				Mat mask_frame(Mat frame, Scalar lowwer, Scalar upper);										// inRange fonksiyonunu �al��t�r�r.
				Mat dilated_images(Mat frame, int element_size);											// �ekilleri B�t�nle�tirir.
				void set_image(std::string path);															// Kaynak Resmi De�i�tirir.
				Mat get_image();																			// Kaynak Resmi D�nd�r�r.
				BYTE* mat_sonuc(Mat mat);																	// Sonucun Yaz�ld��� Frame'in Byte Datas�n�n Tutuld�u Dizinin Adresini D�nd�r�r.
				Mat RGB2HSV(Mat mat);																		// �rnek Ama�l� fonksiyon
				Mat BitmapToMat(BYTE * pArray, int nSize, int image_width, int image_height, int Channel);  // C# Bitmap resmin Byte Datalar�n�n Adresini Alarak  memcp fonksiyonu ile Mata D�n��t�r�r.
				BYTE* MatToByte(Mat mat, int image_height, int image_width,int Channel);					// C++ da Mat datay� Byte Aray d�n��t�r�p adresi  return eder.
				int  find_contours_numbers(Mat frame);														// Framedeki contour say�s�n� sayar.
				void find_color(Mat frame);																	// Yukar�daki fonksiyonlar�n �a�r�ld��� ana fonksiyon

			};
}


