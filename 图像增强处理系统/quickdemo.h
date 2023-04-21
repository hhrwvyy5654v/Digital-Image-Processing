#pragma once
#include<stdio.h>
#include<graphics.h>
class GUI
{
public:
	void plcircle();//绘画圆
	void setbk(int type);//设置背景
	void puttext(int x, int y, const wchar_t* str, unsigned long type, int height, int width);//向Graph界面输出字段
	void setimgbk(const wchar_t* str);//设置图像背景，用于绘画开始页面于运行页面
	void monitorleftmouse(int x, int y); //鼠标监控，用于开始页面于运行页面切换
	void keyboardcontrol();//键盘控制，这一次并没有用到
	void msg();//信息段
	void BGM();//软件BGM
	void loadImg(const wchar_t* str, int x, int y, int width, int height);//加载图片在页面中输出

};