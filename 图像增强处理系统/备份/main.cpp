#include <opencv2/highgui/highgui.hpp>
#include "Image_enhancement.h"
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:/Users/HRQ/Pictures/lena.jpg");
	Demo demo;
	// 图像文件的基本操作：打开、保存、另存、打印、退出
	demo.Image_basic_operation(src, "D:/桌面/");

	//数字图像的统计信息功能：直方图的统计及绘制
	//demo.Draw_histogram(src);

	//数字图像的增强处理功能：直方图均衡化
	//demo.Histogram_equalization(src);

	//数字图像的增强处理功能：灰度拉伸
	 //demo.Grayscale_stretching(src);

	//数字图像的增强处理功能：动态范围调整
	// demo.quantizie(src, 8);

	//空间域平滑算法：均值滤波
	// demo.Mean_filtering(src);

	//空间域平滑算法：中值滤波
	// demo.Median_filtering(src);

	// 空间域平滑算法：高斯滤波
	 //demo.Gaussian_filtering(src);

	// 空间域平滑算法：双边滤波
	// demo.Bilateral_filtering(src);

	//空间域锐化算法：Sobel算子
	// demo.Sobel_operator(src);

	//空间域锐化算法：Laplacian算子
	 //demo.Laplacian_operator(src);

	//空间域锐化算法：Roberts算子
	// demo.Roberts_operator(src);

	//空间域锐化算法：Prewitt算子
	// demo.Prewitt_operator( src);

	//彩色数字图像由RGB转换成HIS空间并分别显示其分量图*
	 //demo.RGB_to_HSI(src);

	//数字图像分割：大津法
	 //demo.Otsu_segmentation(src);

	//数字图像分割：区域生长法
	//demo.Regional_growth_segmentation(src);

	//数字图像分割：分水岭算法
	// demo.Watershed_segmentation(src);

	return 0;
}
