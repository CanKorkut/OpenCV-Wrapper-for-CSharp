// opencvDLL.cpp : Defines the exported functions for the DLL application.
#pragma once

#include "stdafx.h"

#include "../MIA.Image.Process/color_segmentation.h"
#include "../MIA.Image.Process/color_segmentation.cpp"

#include "opencv2\opencv.hpp"
#include <windows.h>

using namespace MIA;

image_process img;


extern "C" __declspec(dllexport) void find_colors(BYTE * byte, int nSize, int image_width, int image_height, int Channel) {
	Mat mat = img.BitmapToMat(byte, nSize, image_width, image_height, Channel);
	img.find_color(mat);
}


extern "C" __declspec (dllexport) int* get_colors_shape(){
	return img.get_colors_shape();
}

extern "C" __declspec(dllexport) Mat get_image() {
	return img.get_image();
}

extern "C" __declspec (dllexport) BYTE* RGB2HSV(BYTE * byte, int nSize, int image_width, int image_height, int Channel) {
	Mat mat = img.BitmapToMat(byte, nSize, image_width, image_height, Channel);
	return img.MatToByte(img.RGB2HSV(mat),  image_height, image_width,Channel) ;
}

extern "C" __declspec (dllexport) int get_color() {
	return img.get_color();
}

extern "C" __declspec(dllexport) BYTE*mat_sonuc() {
	return img.MatToByte(img.img_sonuc, img.img_sonuc.rows, img.img_sonuc.cols, 4);
}



