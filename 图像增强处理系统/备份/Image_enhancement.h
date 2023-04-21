#pragma once
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Demo
{
public:
	// 图像文件的基本操作：打开、保存、另存、打印、退出
	void Image_basic_operation(const Mat &src, const string save_path);
	void Draw_histogram(const Mat &src);		 //直方图的统计及绘制
	void Histogram_equalization(const Mat &src); //直方图均衡化
	void Grayscale_stretching(const Mat &src);	 //灰度拉伸

	//图像动态范围调整
	uchar get_value(int level, uchar v);
	void quantizie(Mat &src, int level);

	//空间域平滑算法
	void Mean_filtering(const Mat &src);	  //均值滤波
	void Median_filtering(const Mat &src);	  //中值滤波
	void Gaussian_filtering(const Mat &src);  //高斯滤波
	void Bilateral_filtering(const Mat &src); //双边滤波

	//空间域锐化算法
	void Sobel_operator(const Mat &src);	 // Sobel算子
	void Laplacian_operator(const Mat &src); // Laplacian算子
	void Roberts_operator(const Mat &src);	 // Roberts算子
	void Prewitt_operator(const Mat &src);	 // Prewitt算子

	//彩色数字图像由RGB转换成HIS空间并分别显示其分量图，对彩色图像进行图像增强
	void RGB_to_HSI(const Mat &src);

	// 数字图像分割功能
	void Otsu_segmentation(const Mat &src);			   //大津法（OTSU算法)
	void Regional_growth_segmentation(const Mat &src); //区域生长法
	void Watershed_segmentation(const Mat &src);	   //分水岭算法
};