#pragma once
#ifndef _WIN32
#error 只支持win平台，如果你是做跨平台，请删除位于yourWorld.h的#error
#endif //_WIN32
#include<Windows.h>
#include<graphics.h>
#include<conio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
const int windowA = 1200;
const int windowB = 675;
RECT rect;
vector<IMAGE*> imgs;
//vector<int> imgs;
unsigned long long COI = 1;
map<string, unsigned long long> imgMap;

#pragma warning(disable : 4996)
//判断文件存在
bool existsTest(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
//————————————————
//版权声明：本文为CSDN博主「guotianqing」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https ://blog.csdn.net/guotianqing/article/details/100766120
#pragma warning(default : 4996)

//带透明的图像输出
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
//	————————————————
//		版权声明：本文为CSDN博主「抱起老婆就跑」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
//		原文链接：https ://blog.csdn.net/weixin_45779485/article/details/102757315

//在错误文件输出错误
void putError(const string x)
{
	settextstyle(16, 8, _T("Courier"));	// 设置字体
	settextcolor(GREEN);
	outtextxy(0, 16, "警告：出现故障，详细见运行目录地error.txt。");
	fstream a;
	a.open("error.txt", ios::out | ios::app);
	a << x << endl;
	a.close();
}
//注册或更换一个图像
inline unsigned long long newImg(const string name, IMAGE &img)
{
	IMAGE* Img = new IMAGE;
	Img->operator=(img);
	if (imgMap[name] != 0)
	{
		imgs[imgMap[name]] = Img;
		return imgMap[name];
	}
	imgs.push_back(Img);
	//imgs.push_back(1);
	imgMap[name] = COI++;
	return imgMap[name];
}
//根据数字ID获得图像
IMAGE getImg(const unsigned long long id)
{
	if (imgs.size() >= id)
		return *imgs[id - 1];
	return *imgs[0];
}
//根据名称查找图片
IMAGE getImg(const string name)
{
	if (imgMap[name] != 0)
	{
		return getImg(imgMap[name]);
	}
	return *imgs[0];
}
//安全地加载一个图片
void loadimage_s(IMAGE* img, const string name)
{
	if (existsTest(name))
	{
		loadimage(img, _T(name.c_str()));
	}
	else
	{
		putError("无法加载" + name + "文件");
	}
}
//利用loadimg_s安全读入并注册一个图像
unsigned long long loadAndNewImg_s(const string imgName,const string nameInGame)
{
	IMAGE img;
	loadimage_s(&img, imgName);
	return newImg(nameInGame, img);
}
//利用loadAndNewImg_s制作的文件、游戏内同名的图像注册函数
unsigned long long loadAndNewImg_s(const string imgName)
{
	return loadAndNewImg_s(imgName, imgName);
}
//利用loadimage读入并注册一个图像
unsigned long long loadAndNewImg(const string imgName, const string nameInGame)
{
	IMAGE img;
	loadimage(&img, _T(imgName.c_str()));
	return newImg(nameInGame, img);
}
//利用loadAndNewImg制作的文件、游戏内同名的图像注册函数
unsigned long long loadAndNewImg(const string imgName)
{
	return loadAndNewImg(imgName, imgName);
}
