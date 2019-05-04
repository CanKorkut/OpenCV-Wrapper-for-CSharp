#pragma once

#include <iostream>
#include "stdafx.h"
#include "color_segmentation.h"
//#include "opencv2\opencv.hpp"
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\core.hpp>
#include <string>
#include <Windows.h>


using namespace std;

namespace MIA {
			image_process::image_process(std::string Path) 
			{

				image_process::set_image(Path);
			}


			image_process::image_process() {};


			Mat image_process::BitmapToMat(BYTE * pArray, int nSize, int image_width, int image_height, int Channel)
			{

				cv::Size size = cv::Size(image_width, image_height);
				Mat mat;
				switch (Channel)
				{
				case 0:
					break;
				case 1:
					mat = Mat(size, CV_8UC1);
					break;
				case 2:
					mat = Mat(size, CV_8UC2);
					break;
				case 3:
					mat = Mat(size, CV_8UC4);
					break;
				case 4:
					mat = Mat(size, CV_8UC4);
					break;
				default:
					cout << "Gecersiz Kanal sayisi" << endl;
					break;
				}
				std::memcpy(mat.data, pArray, image_width * image_height *4);
				Mat mat3 = Mat();
				cvtColor(mat, mat3, CV_RGBA2RGB);
				
				return mat3;
			}

			BYTE* image_process::MatToByte(Mat mat, int image_height, int image_width,int Channel) 
			{
				BYTE * bytes = NULL;
				cvtColor(mat, mat, CV_RGB2RGBA);
				bytes = new BYTE[image_height *image_width * 4];
				std::memcpy(bytes, mat.data, image_height *image_width * 4);
				return bytes;
			}

			int* image_process::get_colors_shape() 
			{
				return image_process::colors_shape;
			}

			BYTE* image_process::mat_sonuc(Mat mat) 
			{
				return image_process::MatToByte(mat, mat.rows, mat.cols, 4);

			}
			Mat image_process::mask_frame(Mat frame, Scalar lowwer, Scalar upper)
			{

				Mat masked_image;
				inRange(frame, lowwer, upper, masked_image);
				return masked_image;

			}
			Mat image_process::dilated_images(Mat frame, int element_size) 
			{

				Mat dilated_images;
				Mat element = getStructuringElement(MORPH_RECT, Size(element_size * element_size + 1, element_size * element_size + 1), Point(element_size, element_size));
				dilate(frame, dilated_images, element);
				return dilated_images;

			}

			int image_process::get_color()
			{
				return image_process::colors;
			}

			int image_process::find_contours_numbers(Mat frame)
			{

				int contours_numbers;
				vector<vector< Point> > contours;
				vector<Vec4i> hierarchy;
				findContours(frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
				contours_numbers = hierarchy.size();
				return contours_numbers;

			}
			void image_process::set_image(std::string Path)
			{
				image_process::image = imread(Path, 1);
		   }
			Mat image_process::get_image() 
			{
				return image_process::image;
			}
			Mat image_process::RGB2HSV(Mat mat)
			{
				cvtColor(mat, mat, CV_RGB2HSV);
				return mat;
			}
			void image_process::find_color(Mat frame)
			{
				image_process img_process;
				int x = 0;
				int y = 0;
				String state = "new color";
				int R, G, B;
				threshold(frame, frame, 220, 255, CV_THRESH_TRUNC);
				int colors[15][3] = {};
				int rect_size = 25;
				int hsv_values[10][3] = {};
				for (int i = 0; i <= 15; i++) {
					for (int x = 0; x <= 3; x++) {
						colors[i][x] = 0;
					}
				}
				int index = 0;
				//--------------- Resim üzerinde 25 * 25 lik kareler halinde gezilerek renk deðerleri okunup farklý renkler tespit ediliyor.-----------------
				while (x < frame.cols - rect_size) {
					while (y < frame.rows - rect_size) {
						Rect crop(x, y, rect_size, rect_size);
						Mat cropped_image = frame(crop);

						cout << cropped_image.at<cv::Vec3b>(rect_size/2, rect_size / 2) << endl;
						R = cropped_image.at<cv::Vec3b>(rect_size / 2, rect_size / 2)[0];
						G = cropped_image.at<cv::Vec3b>(rect_size / 2, rect_size / 2)[1];
						B = cropped_image.at<cv::Vec3b>(rect_size / 2, rect_size / 2)[2];
						if (R == 220 && G == 220 && B == 220) {
							y = y + rect_size;
							continue;
						}
						else {
							state = "new color";
							for (int i = 0; i <= 15; i++) {
								if (colors[i][0] == R && colors[i][1] == G && colors[i][2] == B) {
									state = "same color";
									break;
								}
							}
							if (state == "new color") {
								state = "new color";
								colors[index][0] = R;
								colors[index][1] = G;
								colors[index][2] = B;
								state = "new color";
								Mat hsv_image;
								cvtColor(cropped_image, hsv_image, CV_RGB2HSV);
								Vec3b hsv_value = hsv_image.at<Vec3b>(12, 12);
								hsv_values[index][0] = hsv_value[0];
								hsv_values[index][1] = hsv_value[1];
								hsv_values[index][2] = hsv_value[2];
								cout << "This is the new color !" << endl;
								++index;
							}
						}
						y = y + rect_size;
					}
					y = 0;
					x = x + rect_size;
				}
				//-------------------------------------------------------------------------------------------------------------------
				Mat hsv;
				cvtColor(frame, hsv, CV_RGB2HSV);
				Mat masked_images[10];
				// maskeleme fonksiyonu çaðrýlýyor
				for (int i = 0; i < index; i++) {
					masked_images[i] = img_process.mask_frame(hsv, Scalar(hsv_values[i][0]-2, hsv_values[i][1]-20, hsv_values[i][2]-20), Scalar(hsv_values[i][0]+2, hsv_values[i][1]+20, hsv_values[i][2]+20));
					
				}



				Mat dilated_images[10];

				for (int i = 0; i < index; i++) {
					dilated_images[i] = img_process.dilated_images(masked_images[i], 2);
				}
				// þekil sayýsý hesaplanýypr
				int contour_size[10];
				for (int i = 0; i < index; i++) {
					contour_size[i] = img_process.find_contours_numbers(dilated_images[i]);
				}
				Mat mat_sonuc = Mat(frame.cols, frame.rows, CV_8UC3);
				// sonuçlar ekrana yazdýrýlýyor
				cout << "Tespit edilen renk sayisi:	" << index << endl;
				image_process::colors = index;
				for (int i = 0; i < index; i++) {
					image_process::colors_shape[i] = contour_size[i];
					putText(mat_sonuc, to_string(i+1)+". sekil sayisi:"+to_string(contour_size[i]), cvPoint(100, (i*50)+50),
						FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255, 0, 0), 1, CV_AA);
				}
				image_process::img_sonuc = mat_sonuc;
			}

		
}

