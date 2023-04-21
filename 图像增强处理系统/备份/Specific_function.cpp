#include <vector>
#include <iostream>
#include "Image_enhancement.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define PI 3.141592
using namespace cv;
using namespace std;

// 图像文件的基本操作：打开、保存、另存、打印、退出
void Demo::Image_basic_operation(const Mat &src, const string save_path)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	namedWindow("image", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("image", src);				  //显示图像
	imwrite(save_path + "副本.jpg", src); //另存为图像

	VideoCapture capture(0); //调用摄像头
	string name;
	int i = 0;
	printf("按下空格键拍照，按esc键退出\n");
	while (1)
	{
		Mat frame;
		capture >> frame;
		if (waitKey(20) == 32) //空格拍照
		{
			name = save_path + to_string(i) + ".jpg";
			imwrite(name, frame);
			cout << name << endl;
			i++;
		}
		if (waitKey(10) == 27) // esc退出
		{
			break;
		}
		namedWindow("调用摄像头", WINDOW_AUTOSIZE | WINDOW_NORMAL);
		imshow("调用摄像头", frame);
	}
	waitKey(0);
	destroyAllWindows();
}

//数字图像的统计信息功能：直方图的统计及绘制
void Demo::Draw_histogram(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	namedWindow("原始图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("原始图像", src);
	Mat hist = Mat::zeros(1, 256, CV_32FC1);
	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			hist.at<float>(0, src.at<uchar>(i, j))++;
		}
	}
	Mat histogram = Mat::zeros(540, 1020, CV_8UC1);
	const int bins = 255;
	double maxValue;
	Point2i maxLoc;
	minMaxLoc(hist, 0, &maxValue, 0, &maxLoc);
	int scale = 4;
	int histHeight = 540;

	for (int i = 0; i < bins; i++)
	{
		float binValue = (hist.at<float>(i));
		int height = cvRound(binValue * histHeight / maxValue);
		rectangle(histogram, Point(i * scale, histHeight),
				  Point((i + 1) * scale - 1, histHeight - height), Scalar(255), -1);
	}
	namedWindow("直方图", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("直方图", histogram);
	waitKey(0);
	destroyAllWindows();
}

//数字图像的增强处理功能：直方图均衡化
void Demo::Histogram_equalization(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	Mat gray, dst;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	//直方图均衡化只支持灰度图像，不支持彩色图像。
	imshow("灰度图像", gray);
	// equalizeHist()函数用于实现直方图均衡化，提高图像的质量
	equalizeHist(gray, dst);
	namedWindow("直方图均衡化", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("直方图均衡化", dst);
	waitKey(0);
	destroyAllWindows();
}

//数字图像的增强处理功能：灰度拉伸
void Demo::Grayscale_stretching(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	float fGamma = 1 / 3.2;
	//建立待查表文件LUT
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		//防止彩色溢出，大于255的像素令其为255，小于0的像素令其为0
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
	}
	Mat dst = src.clone();
	const int channels = dst.channels();
	switch (channels)
	{
	case 1: //灰度图
	{
		MatIterator_<uchar> it, end;
		for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
		{
			*it = lut[(*it)];
		}
		break;
	}
	case 3: //彩色图
	{
		MatIterator_<Vec3b> it, end;
		for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
		{
			(*it)[0] = lut[((*it)[0])];
			(*it)[1] = lut[((*it)[1])];
			(*it)[2] = lut[((*it)[2])];
		}
		break;
	}
	}
	imshow("原始图像", src);
	namedWindow("灰度拉伸图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("灰度拉伸图像", dst);
	waitKey(0);
	destroyAllWindows();
}

//数字图像的增强处理功能：动态范围调整
uchar Demo::get_value(int level, uchar v)
{
	int block_num = level - 1;
	int block_size = 256 / block_num;
	for (int i = 1; i <= block_num; i++)
	{
		if (v > block_size * i)
		{
			continue;
		}
		int mid_value = block_size * i / 2;
		int left = block_size * (i - 1);
		int right = block_size * i - 1;
		if (v < mid_value)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	return v;
}

void Demo::quantizie(Mat &src, int level)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	Mat dst = src.clone();
	dst.setTo(0);

	for (int i = 0; i < dst.rows; i++)
	{
		uchar *p1 = src.ptr<uchar>(i);
		uchar *p2 = dst.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++)
		{
			p2[j] = get_value(level, p1[j]);
		}
	}
	namedWindow("原始图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("原始图像", src);
	namedWindow("图像动态范围调整", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("图像动态范围调整", dst);
	waitKey();
	destroyAllWindows();
}

// 空间域平滑算法：均值滤波
void Demo::Mean_filtering(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	imshow("原始图像", src);
	Mat dst;
	blur(src, dst, Size(5, 5));
	namedWindow("均值滤波效果图", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("均值滤波效果图", dst);
	waitKey(0);
	destroyAllWindows();
}

// 空间域平滑算法：中值滤波
void Demo::Median_filtering(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	imshow("原始图像", src);
	Mat dst;
	medianBlur(src, dst, 7);
	namedWindow("中值滤波效果图", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("中值滤波效果图", dst);
	waitKey(0);
	destroyAllWindows();
}

// 空间域平滑算法：高斯滤波
void Demo::Gaussian_filtering(const Mat &src)
{
	Mat dst;
	GaussianBlur(src, dst, Size(5, 5), 0, 0);
	imshow("原始图像", src);
	namedWindow("高斯滤波效果图", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("高斯滤波效果图", dst);
	waitKey(0);
	destroyAllWindows();
}

//空间域平滑算法:双边滤波
void Demo::Bilateral_filtering(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	imshow("原始图像", src);
	Mat dst;
	bilateralFilter(src, dst, 25, 25 * 2, int(25 / 2));
	namedWindow("双边滤波效果图", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("双边滤波效果图", dst);
	waitKey(0);
	destroyAllWindows();
}

/*空间域锐化算法：Sobel算子
使用Sobel算子提取图像边缘,包含以下四个步骤:
①对图像进行高斯模糊;
②将图像转换到灰度空间;
③利用Sobel算子或者Scharr算子计算图像梯度;
④利用提取的梯度,调整图像灰度值,提取图像边缘;
*/
void Demo::Sobel_operator(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	// 1. 高斯模糊
	Mat srcBlur;
	GaussianBlur(src, srcBlur, Size(3, 3), 0, 0);
	// 2. 转灰度
	Mat srcGray;
	cvtColor(srcBlur, srcGray, COLOR_BGR2GRAY);
	// 3. 求方向梯度
	Mat gradX, gradY;
	Sobel(srcGray, gradX, CV_16S, 1, 0, 3);
	Sobel(srcGray, gradY, CV_16S, 0, 1, 3);
	convertScaleAbs(gradX, gradX);
	convertScaleAbs(gradY, gradY);
	// 4. 图像混合
	Mat dst;
	addWeighted(gradX, 0.5, gradY, 0.5, 0, dst);
	Mat gradXY = Mat(gradX.size(), gradX.type());
	for (int row = 0; row < gradX.rows; row++)
	{
		for (int col = 0; col < gradX.cols; col++)
		{
			int gX = gradX.at<uchar>(row, col);
			int gY = gradY.at<uchar>(row, col);
			gradXY.at<uchar>(row, col) = saturate_cast<uchar>(gX + gY);
		}
	}
	imshow("原始图像", src);
	namedWindow("使用Sobel算子进行边缘检测", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("使用Sobel算子进行边缘检测", dst);
	waitKey(0);
	destroyAllWindows();
}

//空间域锐化算法：Laplacian算子
void Demo::Laplacian_operator(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	// 1. 高斯模糊
	Mat srcBlur;
	GaussianBlur(src, srcBlur, Size(3, 3), 0, 0);

	// 2. 转灰度图
	Mat srcGray;
	cvtColor(srcBlur, srcGray, COLOR_BGR2GRAY);
	cout << srcGray.type() << endl;

	// 3. 拉普拉斯-计算二阶导数
	Mat srcGrad;
	Laplacian(srcGray, srcGrad, CV_16S, 3);

	Mat dst;
	convertScaleAbs(srcGrad, dst);
	threshold(dst, dst, 0, 244, THRESH_OTSU);
	imshow("原始图像", src);
	namedWindow("使用Laplacian算子进行边缘检测", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("使用Laplacian算子进行边缘检测", dst);
	waitKey(0);
	destroyAllWindows();
}

//空间域锐化算法：Roberts算子边缘检测
void Demo::Roberts_operator(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	Mat robert_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
	Mat robert_y = (Mat_<int>(2, 2) << 0, -1, 1, 0);
	Mat robert_grad_x, robert_grad_y, robert_grad;
	filter2D(src, robert_grad_x, CV_16S, robert_x);
	filter2D(src, robert_grad_y, CV_16S, robert_y);
	convertScaleAbs(robert_grad_x, robert_grad_x);
	convertScaleAbs(robert_grad_y, robert_grad_y);
	add(robert_grad_x, robert_grad_y, robert_grad);
	convertScaleAbs(robert_grad, robert_grad);
	imshow("原始图像", src);
	namedWindow("使用Roberts算子进行边缘检测", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("使用Roberts算子进行边缘检测", robert_grad);
	waitKey(0);
	destroyAllWindows();
}

//空间域锐化算法：Prewitt算子边缘检测
void Demo::Prewitt_operator(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	Mat prewitt_x = (Mat_<char>(3, 3) << -1, 0, 1,
					 -1, 0, 1,
					 -1, 0, 1);
	Mat prewitt_y = (Mat_<char>(3, 3) << -1, -1, -1,
					 0, 0, 0,
					 1, 1, 1);
	Mat prewitt_grad_x, prewitt_grad_y, prewitt_grad;
	filter2D(src, prewitt_grad_x, CV_32F, prewitt_x);
	filter2D(src, prewitt_grad_y, CV_32F, prewitt_y);
	convertScaleAbs(prewitt_grad_x, prewitt_grad_x);
	convertScaleAbs(prewitt_grad_y, prewitt_grad_y);
	add(prewitt_grad_x, prewitt_grad_y, prewitt_grad);
	convertScaleAbs(prewitt_grad, prewitt_grad);
	imshow("原始图像", src);
	namedWindow("使用Prewitt算子进行边缘检测", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("使用Prewitt算子进行边缘检测", prewitt_grad);
	waitKey(0);
	destroyAllWindows();
}

//彩色数字图像由RGB转换成HIS空间并分别显示其分量图，对彩色图像进行图像增强
void Demo::RGB_to_HSI(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	Mat hsi(src.rows, src.cols, src.type());
	float r, g, b, H, S, I, num, den, theta, sum, min_RGB;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			b = src.at<Vec3b>(i, j)[0];
			g = src.at<Vec3b>(i, j)[1];
			r = src.at<Vec3b>(i, j)[2];

			// 归一化
			b = b / 255.0;
			g = g / 255.0;
			r = r / 255.0;

			num = 0.5 * ((r - g) + (r - b));
			den = sqrt((r - g) * (r - g) + (r - b) * (g - b));
			theta = acos(num / den);
			if (den == 0)
				H = 0; // 分母不能为0
			else if (b <= g)
				H = theta;
			else
				H = (2 * PI - theta);
			min_RGB = min(min(b, g), r); // min(R,G,B)
			sum = b + g + r;
			if (sum == 0)
				S = 0;
			else
				S = 1 - 3 * min_RGB / sum;
			I = sum / 3.0;
			H = H / (2 * PI);
			// 将S分量和H分量都扩充到[0,255]区间以便于显示
			//一般H分量在[0,2pi]之间，S在[0,1]之间
			hsi.at<Vec3b>(i, j)[0] = H * 255;
			hsi.at<Vec3b>(i, j)[1] = S * 255;
			hsi.at<Vec3b>(i, j)[2] = I * 255;
		}
	}
	namedWindow("原始RGB图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	namedWindow("转换后HSI图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("原始RGB图像", src);
	imshow("转换后HSI图像", hsi);
	waitKey(0);
	destroyAllWindows();
}

void Demo::Otsu_segmentation(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	Mat dst, gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	// 大津法自动寻求全局阈值
	threshold(gray, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("原始图像", src);
	namedWindow("使用大津法分割图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("使用大津法分割图像", dst);
	waitKey(0);
	destroyAllWindows();
}

// 数字图像分割功能：区域生长法
void Demo::Regional_growth_segmentation(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}

	//四舍五入取整，防止坐标为小数
	int firstSeed_x = round(src.cols / 2); //x坐标是列数
	int firstSeed_y = round(src.rows / 2); //y坐标是行数
	//定义第一个种子点位置为图片最中心处
	Point firstSeed = Point(firstSeed_x, firstSeed_y);

	Mat dst = Mat::zeros(src.size(), CV_8UC1); //生长区域
											   //为第一个生长点赋值
	dst.at<uchar>(Point(firstSeed.x, firstSeed.y)) = src.at<uchar>(Point(firstSeed.x, firstSeed.y));
	Point waitSeed;										   //待生长种子点
	int waitSeed_value = 0;								   //待生长种子点像素值
	int opp_waitSeed_value = 0;							   // src_thresh中对应待生长种子点处的像素值
	vector<Point> seedVector;							   //种子栈
	seedVector.push_back(firstSeed);					   //将种子放入栈中最后一个位置
	int direct[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; // 4邻域,应该用4邻域减小时间复杂度
	// int direct[8][2] = { {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0} };  //8邻域

	while (!seedVector.empty()) //种子栈不为空则生长，即遍历栈中所有元素后停止生长
	{
		Point seed = seedVector.back(); //取出最后一个元素
		seedVector.pop_back();			//删除栈中最后一个元素,防止重复扫描
		for (int i = 0; i < 4; i++)		//遍历种子点的4邻域
		{
			waitSeed.x = seed.x + direct[i][0]; //第i个坐标0行，即x坐标值
			waitSeed.y = seed.y + direct[i][1]; //第i个坐标1行，即y坐标值

			//检查是否是边缘点
			if (waitSeed.x < 0 || waitSeed.y < 0 ||
				waitSeed.x > (src.cols - 1) || (waitSeed.y > src.rows - 1))
			{
				continue;
			}

			waitSeed_value = dst.at<uchar>(Point(waitSeed.x, waitSeed.y)); //为待生长种子点赋对应位置的像素值
			opp_waitSeed_value = src.at<uchar>(Point(waitSeed.x, waitSeed.y));
			if (waitSeed_value == 0) //判断waitSeed是否已经被生长，避免重复生长造成死循环
			{
				if (opp_waitSeed_value != 0) //区域生长条件
				{
					dst.at<uchar>(Point(waitSeed.x, waitSeed.y)) = src.at<uchar>(Point(waitSeed.x, waitSeed.y));
					seedVector.push_back(waitSeed); //将满足生长条件的待生长种子点放入种子栈中
				}
			}
		}
	}
	imshow("原始图像", src);
	namedWindow("使用区域生长法分割图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("使用区域生长法分割图像", dst);
	waitKey(0);
	destroyAllWindows();
}

//数字图像分割：分水岭算法
void Demo::Watershed_segmentation(const Mat &src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	Mat gray;
	int row = src.rows;
	int col = src.cols;
	// 1. 将RGB图像灰度化
	cvtColor(src, gray, COLOR_BGR2GRAY);
	// 2. 使用大津法转为二值图，并做形态学闭合操作
	threshold(gray, gray, 0, 255, THRESH_BINARY | THRESH_OTSU);
	// 3. 形态学闭操作
	Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9), Point(-1, -1));
	morphologyEx(gray, gray, MORPH_CLOSE, kernel);
	// 4. 距离变换
	distanceTransform(gray, gray, DIST_L2, DIST_MASK_3, 5);
	// 5. 将图像归一化到[0, 1]范围
	normalize(gray, gray, 0, 1, NORM_MINMAX);
	// 6. 将图像取值范围变为8位(0-255)
	gray.convertTo(gray, CV_8UC1);
	// 7. 再使用大津法转为二值图，并做形态学闭合操作
	threshold(gray, gray, 0, 255, THRESH_BINARY | THRESH_OTSU);
	morphologyEx(gray, gray, MORPH_CLOSE, kernel);
	// 8. 使用findContours寻找marks
	vector<vector<Point>> contours;
	findContours(gray, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));
	Mat marks = Mat::zeros(gray.size(), CV_32SC1);
	for (size_t i = 0; i < contours.size(); i++)
	{
		// static_cast<int>(i+1)是为了分水岭的标记不同，区域1、2、3...这样才能分割
		drawContours(marks, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i + 1)), 2);
	}
	// 9. 对原图做形态学的腐蚀操作
	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(src, src, MORPH_ERODE, k);
	// 10. 调用opencv的分水岭算法
	watershed(src, marks);
	// 11. 随机分配颜色
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++)
	{
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	// 12. 显示图像
	Mat dst = Mat::zeros(marks.size(), CV_8UC3);
	int index = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			index = marks.at<int>(i, j);
			if (index > 0 && index <= contours.size())
			{
				dst.at<Vec3b>(i, j) = colors[index - 1];
			}
			else if (index == -1)
			{
				dst.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			}
			else
			{
				dst.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("原始图像", src);
	namedWindow("使用区域生长法分割图像", WINDOW_AUTOSIZE | WINDOW_NORMAL);
	imshow("使用区域生长法分割图像", dst);
	waitKey(0);
	destroyAllWindows();
}