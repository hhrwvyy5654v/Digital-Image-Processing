#include"quickdemo.h"

#include<mmsystem.h>//包含多媒体设备接口头文件
#pragma comment(lib,"winmm.lib")//加载静态库
void GUI::plcircle()
{


	setfillcolor(YELLOW);//填充颜色
	setlinecolor(BLUE);  //填充线条颜色
	setlinestyle(PS_SOLID, 10);//边框线条形式与宽

	//circle(50, 50, 50);//绘画圆圈
	//fillcircle(50, 50, 50);//绘画xy,半径
	solidcircle(50, 50, 50);
}

void GUI::setbk(int type)
{
	setbkcolor(type);//设置背景颜色
	cleardevice();//清屏函数必须在设置完新的背景颜色后才清楚上一个背景颜色***🐱‍🚀
}

/*
	   void settextstyle(int nHeight,int nWidth,LPCTSTR lpszFace);
	   nHeight  指定高度（逻辑单位）
	   nWidth 字符的平均宽度（逻辑单位）。如果为 0，则比例自适应
	   lpszFace字体名称。

*/
void GUI::puttext(int x, int y, const wchar_t* str, unsigned long type, int height, int width)
{
	settextcolor(type);//设置文字颜色
	settextstyle(height, width, L"楷体");//高度、宽度、字体
	setbkmode(TRANSPARENT);//考虑到文字背景也有默认颜色，可能发生遮挡，所以将文字背景改为透明
	outtextxy(x, y, str);//打印xy位置的字符串
	printf("%d %d\n", textheight(str), textwidth(str));
}
/*
6.2 loadimage()–从文件中读取图像函数
// 从资源文件获取图像(bmp/gif/jpg/png/tif/emf/wmf/ico)
void loadimage(
	IMAGE * pDstImg, // 保存图像的 IMAGE 对象指针
	LPCTSTR pResType, // 资源类型
	LPCTSTR pResName, // 资源名称
	int nWidth = 0, // 图片的拉伸宽度
	int nHeight = 0, // 图片的拉伸高度
	bool bResize = false // 是否调整 IMAGE 的大小以适应图片
);

6.3 putimage()–当前设备上绘制图像函数
// 绘制图像(指定宽高和起始位置)
void putimage(
	int dstX, // 绘制位置的 x 坐标
	int dstY, // 绘制位置的 y 坐标
	int dstWidth, // 绘制的宽度
	int dstHeight, // 绘制的高度
	IMAGE * pSrcImg, // 要绘制的 IMAGE 对象指针
	int srcX, // 绘制内容在 IMAGE 对象中的左上角 x 坐标
	int srcY, // 绘制内容在 IMAGE 对象中的左上角 y 坐标
	DWORD dwRop = SRCCOPY // 三元光栅操作码
);
*/
void GUI::setimgbk(const wchar_t* imgurl)
{
	IMAGE img;
	loadimage(&img, imgurl, 1080, 640);
	putimage(0, 0, &img);
}

void GUI::monitorleftmouse(int width, int height)
{
	int flag = 1;
	while (flag)
	{
		ExMessage msg = { 0 };
		if (peekmessage(&msg, EM_MOUSE));//检测鼠标信息
		{
			switch (msg.message)//筛选鼠标信息类型
			{
			case WM_LBUTTONDOWN://左键信息
				if (msg.x >= 0 && msg.x <= width && msg.y >= 0 && msg.y <= height)
				{
					printf("左键激活\n");
					flag = 0;
				}
				break;
			default:
				break;
			}
		}
	}

}

/*
   getch()函数需要引用头文件conio.h,GetAsyncKeyState(键值)需要引头文件windows.h,但是由于Easyx包含了windows.h,所以无需自己包含。
   getch()需要使用返回值来判断
   1. 与非ASCLL表字符的按键比较，需要使用虚拟键值（上:72,下:80,左:75,右:77）
   2.如果是与字母比较直接写字母如‘A’
   GetAsyncKeyState(键值）：
   1.需要传入一个键值，如果按下返回（上:VK_UP,下:VK_DOWN,左:VK_LEFT,右:VK_RIGHT）
	为了防止控制物体移动打印时窗口发生频闪，我们可以使用双缓冲绘图避免频闪，即在绘画代码块前后分别加上FlushBatchDraw()和EndBatchDraw()

*/
void GUI::keyboardcontrol()
{
	int x = 10;
	int y = 10;
	while (x > 8)
	{
		FlushBatchDraw();
		cleardevice();//清除上一次绘画的图形防止发生重叠
		solidcircle(x, y, 10);//无边框填充画圆
		EndBatchDraw();
		if (GetAsyncKeyState(VK_UP))
		{
			y -= 1;
			printf("向上运动");
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			y += 1;
			printf("向下运动");
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			x -= 1;
			printf("向左运动");
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			x += 1;
			printf("向右运动");
		}
	}
}

void GUI::msg()
{
	HWND hn = GetHWnd();//获取窗口名字的函数
	SetWindowText(hn, L"GUI测试程序");//修改窗口名字函数
	MessageBox(hn, L"我是消息框", L"提示", MB_OKCANCEL);//消息框弹出设置函数


}


void GUI::BGM()
{
	mciSendString(L"open  ./经典钢琴纯音乐.mp3", 0, 0, 0);
	mciSendString(L"play  ./经典钢琴纯音乐.mp3", 0, 0, 0);
}

void GUI::loadImg(const wchar_t* imgurl, int x, int y, int width, int height)
{
	IMAGE img;
	loadimage(&img, imgurl, width, height);
	putimage(x, y, &img);
}
