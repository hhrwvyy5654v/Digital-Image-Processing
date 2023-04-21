#include <vector>
#include <iostream>
#include "Image_enhancement.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define PI 3.141592

using namespace std;

// 图像文件的基本操作：打开、保存、另存、打印、退出
void Demo::Image_basic_operation(const cv::Mat& src, const string save_path)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::namedWindow("image", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("image", src);				  //显示图像
	cv::imwrite(save_path + "副本.jpg", src); //另存为图像

	cv::VideoCapture capture(0); //调用摄像头
	string name;
	int i = 0;
	printf("按下空格键拍照，按esc键退出\n");
	while (1)
	{
		cv::Mat frame;
		capture >> frame;
		if (cv::waitKey(20) == 32) //空格拍照
		{
			name = save_path + to_string(i) + ".jpg";
			cv::imwrite(name, frame);
			cout << name << endl;
			i++;
		}
		if (cv::waitKey(10) == 27) // esc退出
		{
			break;
		}
		cv::namedWindow("调用摄像头", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
		cv::imshow("调用摄像头", frame);
	}
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//数字图像的统计信息功能：直方图的统计及绘制
void Demo::Draw_histogram(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::namedWindow("原始图像", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("原始图像", src);
	cv::Mat hist = cv::Mat::zeros(1, 256, CV_32FC1);
	//遍历图像的每行每列的像素点
	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			hist.at<float>(0, src.at<uchar>(i, j))++;
		}
	}
	cv::Mat histogram = cv::Mat::zeros(540, 1020, CV_8UC1);
	const int bins = 255;
	double maxValue;
	cv::Point2i maxLoc;
	//寻找全局最小和最大值
	minMaxLoc(hist, 0, &maxValue, 0, &maxLoc);
	int scale = 4;
	int histHeight = 540;
	//绘制直方图
	for (int i = 0; i < bins; i++)
	{
		float binValue = (hist.at<float>(i));
		int height = cvRound(binValue * histHeight / maxValue);
		rectangle(histogram, cv::Point(i * scale, histHeight),
			cv::Point((i + 1) * scale - 1, histHeight - height), cv::Scalar(255), -1);
	}
	cv::namedWindow("直方图", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("直方图", histogram);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//数字图像的增强处理功能：直方图均衡化
void Demo::Histogram_equalization(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::Mat gray, dst;
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	//直方图均衡化只支持灰度图像，不支持彩色图像。
	cv::imshow("灰度图像", gray);
	// equalizeHist()函数用于实现直方图均衡化，提高图像的质量
	cv::equalizeHist(gray, dst);
	cv::namedWindow("直方图均衡化", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("直方图均衡化", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//数字图像的增强处理功能：灰度拉伸
void Demo::Grayscale_stretching(const cv::Mat& src)
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
		lut[i] = cv::saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
	}
	cv::Mat dst = src.clone();
	//获取图像通道数
	const int channels = dst.channels();
	switch (channels)
	{
	case 1: //灰度图
	{
		cv::MatIterator_<uchar> it, end;
		for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
		{
			*it = lut[(*it)];
		}
		break;
	}
	case 3: //彩色图
	{
		cv::MatIterator_<cv::Vec3b> it, end;
		for (it = dst.begin<cv::Vec3b>(), end = dst.end<cv::Vec3b>(); it != end; it++)
		{
			(*it)[0] = lut[((*it)[0])];
			(*it)[1] = lut[((*it)[1])];
			(*it)[2] = lut[((*it)[2])];
		}
		break;
	}
	}
	cv::imshow("原始图像", src);
	cv::namedWindow("灰度拉伸图像", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("灰度拉伸图像", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
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

void Demo::quantizie(cv::Mat& src, int level)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::Mat dst = src.clone();
	dst.setTo(0);
	//重置每一个像素点的值
	for (int i = 0; i < dst.rows; i++)
	{
		uchar* p1 = src.ptr<uchar>(i);
		uchar* p2 = dst.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++)
		{
			p2[j] = get_value(level, p1[j]);
		}
	}
	cv::namedWindow("原始图像", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("原始图像", src);
	cv::namedWindow("图像动态范围调整", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("图像动态范围调整", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

// 空间域平滑算法：均值滤波
void Demo::Mean_filtering(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::imshow("原始图像", src);
	cv::Mat dst;
	blur(src, dst, cv::Size(5, 5));
	cv::namedWindow("均值滤波效果图", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("均值滤波效果图", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

// 空间域平滑算法：中值滤波
void Demo::Median_filtering(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::imshow("原始图像", src);
	cv::Mat dst;
	medianBlur(src, dst, 7);
	cv::namedWindow("中值滤波效果图", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("中值滤波效果图", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

// 空间域平滑算法：高斯滤波
void Demo::Gaussian_filtering(const cv::Mat& src)
{
	cv::Mat dst;
	GaussianBlur(src, dst, cv::Size(5, 5), 0, 0);
	cv::imshow("原始图像", src);
	cv::namedWindow("高斯滤波效果图", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("高斯滤波效果图", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//空间域平滑算法:双边滤波
void Demo::Bilateral_filtering(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::imshow("原始图像", src);
	cv::Mat dst;
	bilateralFilter(src, dst, 25, 25 * 2, int(25 / 2));
	cv::namedWindow("双边滤波效果图", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("双边滤波效果图", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

/*空间域锐化算法：Sobel算子
使用Sobel算子提取图像边缘,包含以下四个步骤:
①对图像进行高斯模糊;
②将图像转换到灰度空间;
③利用Sobel算子或者Scharr算子计算图像梯度;
④利用提取的梯度,调整图像灰度值,提取图像边缘;
*/
void Demo::Sobel_operator(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	// 1. 高斯模糊
	cv::Mat srcBlur;
	GaussianBlur(src, srcBlur, cv::Size(3, 3), 0, 0);
	// 2. 转灰度
	cv::Mat srcGray;
	cvtColor(srcBlur, srcGray, cv::COLOR_BGR2GRAY);
	// 3. 求方向梯度
	cv::Mat gradX, gradY;
	Sobel(srcGray, gradX, CV_16S, 1, 0, 3);
	Sobel(srcGray, gradY, CV_16S, 0, 1, 3);
	convertScaleAbs(gradX, gradX);
	convertScaleAbs(gradY, gradY);
	// 4. 图像混合
	cv::Mat dst;
	addWeighted(gradX, 0.5, gradY, 0.5, 0, dst);
	cv::Mat gradXY = cv::Mat(gradX.size(), gradX.type());
	for (int row = 0; row < gradX.rows; row++)
	{
		for (int col = 0; col < gradX.cols; col++)
		{
			int gX = gradX.at<uchar>(row, col);
			int gY = gradY.at<uchar>(row, col);
			gradXY.at<uchar>(row, col) = cv::saturate_cast<uchar>(gX + gY);
		}
	}
	cv::imshow("原始图像", src);
	cv::namedWindow("使用Sobel算子进行边缘检测", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("使用Sobel算子进行边缘检测", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//空间域锐化算法：Laplacian算子
void Demo::Laplacian_operator(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	// 1. 高斯模糊
	cv::Mat srcBlur;
	GaussianBlur(src, srcBlur, cv::Size(3, 3), 0, 0);

	// 2. 转灰度图
	cv::Mat srcGray;
	cvtColor(srcBlur, srcGray, cv::COLOR_BGR2GRAY);
	cout << srcGray.type() << endl;

	// 3. 拉普拉斯-计算二阶导数
	cv::Mat srcGrad;
	Laplacian(srcGray, srcGrad, CV_16S, 3);

	cv::Mat dst;
	convertScaleAbs(srcGrad, dst);
	threshold(dst, dst, 0, 244, cv::THRESH_OTSU);
	cv::imshow("原始图像", src);
	cv::namedWindow("使用Laplacian算子进行边缘检测", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("使用Laplacian算子进行边缘检测", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//空间域锐化算法：Roberts算子边缘检测
void Demo::Roberts_operator(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::Mat robert_x = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);
	cv::Mat robert_y = (cv::Mat_<int>(2, 2) << 0, -1, 1, 0);
	cv::Mat robert_grad_x, robert_grad_y, robert_grad;
	//对图像进行卷积操作
	filter2D(src, robert_grad_x, CV_16S, robert_x);
	filter2D(src, robert_grad_y, CV_16S, robert_y);
	//对像素取绝对值
	convertScaleAbs(robert_grad_x, robert_grad_x);
	convertScaleAbs(robert_grad_y, robert_grad_y);
	//融合水平方向和垂直方向的像素
	add(robert_grad_x, robert_grad_y, robert_grad);
	convertScaleAbs(robert_grad, robert_grad);
	cv::imshow("原始图像", src);
	cv::namedWindow("使用Roberts算子进行边缘检测", cv::WINDOW_FREERATIO);
	cv::imshow("使用Roberts算子进行边缘检测", robert_grad);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//空间域锐化算法：Prewitt算子边缘检测
void Demo::Prewitt_operator(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	//自定义水平方向和垂直方向的卷积核
	cv::Mat prewitt_x = (cv::Mat_<char>(3, 3) << -1, 0, 1,
		-1, 0, 1,
		-1, 0, 1);
	cv::Mat prewitt_y = (cv::Mat_<char>(3, 3) << -1, -1, -1,
		0, 0, 0,
		1, 1, 1);
	cv::Mat prewitt_grad_x, prewitt_grad_y, prewitt_grad;
	//卷积操作
	filter2D(src, prewitt_grad_x, CV_32F, prewitt_x);
	filter2D(src, prewitt_grad_y, CV_32F, prewitt_y);
	//对像素取绝对值
	convertScaleAbs(prewitt_grad_x, prewitt_grad_x);
	convertScaleAbs(prewitt_grad_y, prewitt_grad_y);
	add(prewitt_grad_x, prewitt_grad_y, prewitt_grad);
	convertScaleAbs(prewitt_grad, prewitt_grad);
	cv::imshow("原始图像", src);
	cv::namedWindow("使用Prewitt算子进行边缘检测", cv::WINDOW_FREERATIO);
	cv::imshow("使用Prewitt算子进行边缘检测", prewitt_grad);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//彩色数字图像由RGB转换成HIS空间并分别显示其分量图，对彩色图像进行图像增强
void Demo::RGB_to_HSI(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::Mat hsi(src.rows, src.cols, src.type());
	float r, g, b, H, S, I, num, den, theta, sum, min_RGB;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			//获取每一个像素点的BGR值
			b = src.at<cv::Vec3b>(i, j)[0];
			g = src.at<cv::Vec3b>(i, j)[1];
			r = src.at<cv::Vec3b>(i, j)[2];

			// 归一化处理
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
			hsi.at<cv::Vec3b>(i, j)[0] = H * 255;
			hsi.at<cv::Vec3b>(i, j)[1] = S * 255;
			hsi.at<cv::Vec3b>(i, j)[2] = I * 255;
		}
	}
	cv::namedWindow("原始RGB图像", cv::WINDOW_FREERATIO);
	cv::namedWindow("转换后HSI图像", cv::WINDOW_FREERATIO);
	cv::imshow("原始RGB图像", src);
	cv::imshow("转换后HSI图像", hsi);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void Demo::Otsu_segmentation(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::Mat dst, gray;
	cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	// 大津法自动寻求全局阈值
	threshold(gray, dst, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	cv::imshow("原始图像", src);
	cv::namedWindow("使用大津法分割图像", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("使用大津法分割图像", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

// 数字图像分割功能：区域生长法
void Demo::Regional_growth_segmentation(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}

	//四舍五入取整，防止坐标为小数
	int firstSeed_x = round(src.cols / 2); //x坐标是列数
	int firstSeed_y = round(src.rows / 2); //y坐标是行数
	//定义第一个种子点位置为图片最中心处
	cv::Point firstSeed = cv::Point(firstSeed_x, firstSeed_y);

	cv::Mat dst = cv::Mat::zeros(src.size(), CV_8UC1); //生长区域
											   //为第一个生长点赋值
	dst.at<uchar>(cv::Point(firstSeed.x, firstSeed.y)) = src.at<uchar>(cv::Point(firstSeed.x, firstSeed.y));
	cv::Point waitSeed;										   //待生长种子点
	int waitSeed_value = 0;								   //待生长种子点像素值
	int opp_waitSeed_value = 0;							   // src_thresh中对应待生长种子点处的像素值
	vector<cv::Point> seedVector;							   //种子栈
	seedVector.push_back(firstSeed);					   //将种子放入栈中最后一个位置
	int direct[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} }; // 4邻域,应该用4邻域减小时间复杂度
	// int direct[8][2] = { {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0} };  //8邻域

	while (!seedVector.empty()) //种子栈不为空则生长，即遍历栈中所有元素后停止生长
	{
		cv::Point seed = seedVector.back(); //取出最后一个元素
		seedVector.pop_back();			//删除栈中最后一个元素,防止重复扫描
		for (int i = 0; i < 4; i++)		//遍历种子点的4邻域
		{
			waitSeed.x = seed.x + direct[i][0]; //第i个坐标0行，即x坐标值
			waitSeed.y = seed.y + direct[i][1]; //第i个坐标1行，即y坐标值

			//检查是否是边缘点
			if (waitSeed.x < 0 || waitSeed.y < 0 ||
				waitSeed.x >(src.cols - 1) || (waitSeed.y > src.rows - 1))
			{
				continue;
			}

			waitSeed_value = dst.at<uchar>(cv::Point(waitSeed.x, waitSeed.y)); //为待生长种子点赋对应位置的像素值
			opp_waitSeed_value = src.at<uchar>(cv::Point(waitSeed.x, waitSeed.y));
			if (waitSeed_value == 0) //判断waitSeed是否已经被生长，避免重复生长造成死循环
			{
				if (opp_waitSeed_value != 0) //区域生长条件
				{
					dst.at<uchar>(cv::Point(waitSeed.x, waitSeed.y)) = src.at<uchar>(cv::Point(waitSeed.x, waitSeed.y));
					seedVector.push_back(waitSeed); //将满足生长条件的待生长种子点放入种子栈中
				}
			}
		}
	}
	cv::imshow("原始图像", src);
	cv::namedWindow("使用区域生长法分割图像", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("使用区域生长法分割图像", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//数字图像分割：分水岭算法
void Demo::Watershed_segmentation(const cv::Mat& src)
{
	if (src.empty())
	{
		printf("无法加载图像\n");
	}
	cv::Mat gray;
	int row = src.rows;
	int col = src.cols;
	// 1. 将RGB图像灰度化
	cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	// 2. 使用大津法转为二值图，并做形态学闭合操作
	threshold(gray, gray, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	// 3. 形态学闭操作
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9), cv::Point(-1, -1));
	morphologyEx(gray, gray, cv::MORPH_CLOSE, kernel);
	// 4. 距离变换
	distanceTransform(gray, gray, cv::DIST_L2, cv::DIST_MASK_3, 5);
	// 5. 将图像归一化到[0, 1]范围
	normalize(gray, gray, 0, 1, cv::NORM_MINMAX);
	// 6. 将图像取值范围变为8位(0-255)
	gray.convertTo(gray, CV_8UC1);
	// 7. 再使用大津法转为二值图，并做形态学闭合操作
	threshold(gray, gray, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	morphologyEx(gray, gray, cv::MORPH_CLOSE, kernel);
	// 8. 使用findContours寻找marks
	vector<vector<cv::Point>> contours;
	findContours(gray, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(-1, -1));
	cv::Mat marks = cv::Mat::zeros(gray.size(), CV_32SC1);
	for (size_t i = 0; i < contours.size(); i++)
	{
		// static_cast<int>(i+1)是为了分水岭的标记不同，区域1、2、3...这样才能分割
		drawContours(marks, contours, static_cast<int>(i), cv::Scalar::all(static_cast<int>(i + 1)), 2);
	}
	// 9. 对原图做形态学的腐蚀操作
	cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
	morphologyEx(src, src, cv::MORPH_ERODE, k);
	// 10. 调用opencv的分水岭算法
	watershed(src, marks);
	// 11. 随机分配颜色
	vector<cv::Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++)
	{
		int r = cv::theRNG().uniform(0, 255);
		int g = cv::theRNG().uniform(0, 255);
		int b = cv::theRNG().uniform(0, 255);
		colors.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	// 12. 显示图像
	cv::Mat dst = cv::Mat::zeros(marks.size(), CV_8UC3);
	int index = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			index = marks.at<int>(i, j);
			if (index > 0 && index <= contours.size())
			{
				dst.at<cv::Vec3b>(i, j) = colors[index - 1];
			}
			else if (index == -1)
			{
				dst.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);
			}
			else
			{
				dst.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
			}
		}
	}
	cv::imshow("原始图像", src);
	cv::namedWindow("使用区域生长法分割图像", cv::WINDOW_AUTOSIZE | cv::WINDOW_NORMAL);
	cv::imshow("使用区域生长法分割图像", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}