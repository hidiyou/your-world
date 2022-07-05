#pragma once
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#ifndef _WIN32
#error 只支持win平台，如果你是做跨平台，请删除位于yourWorld.h的#error
#endif //_WIN32
using namespace std;
const int windowA = 1200;
const int windowB = 675;

//判断文件存在
bool existsTest(const std::string& name);
//带透明的图像输出
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);
//在错误文件输出错误
void putError(const string x);
//注册或更换一个图像
unsigned long long newImg(const string name, const IMAGE img);
//根据数字ID获得图像
IMAGE getImg(const unsigned long long id);
//根据名称查找图片
IMAGE getImg(const string name);
//根据名称查找ID
unsigned long long getImgId(const string name);
//安全地加载一个图片
void loadimage_s(IMAGE* img, const string name);
//利用loadimg_s安全读入并注册一个图像
unsigned long long loadAndNewImg_s(const string imgName, const string nameInGame);
//利用loadAndNewImg_s制作的文件、游戏内同名的图像注册函数
unsigned long long loadAndNewImg_s(const string imgName);
//利用loadimage读入并注册一个图像
unsigned long long loadAndNewImg(const string imgName, const string nameInGame);
//利用loadAndNewImg制作的文件、游戏内同名的图像注册函数
unsigned long long loadAndNewImg(const string imgName);