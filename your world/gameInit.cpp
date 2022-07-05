#include "resource.h"
#include<Windows.h>
#include<conio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<graphics.h>
#include"yourWorld.h"
#include"DLC.h"

using namespace std;

RECT rect;
void gameInit()
{
	//初始化error.txt
	fstream a;
	a.open("error.txt", ios::out);
	a << "开始记录" << endl;
	a.close();
	//居中窗口
	int scrWidth, scrHeight;
	HWND hWnd = GetHWnd();
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, HWND_TOPMOST, (scrWidth - rect.right) / 2, (scrHeight - rect.bottom) / 2, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
	//初始化窗体
	initgraph(windowA, windowB);
	cleardevice();
	setbkmode(TRANSPARENT);
	SetConsoleTitle("your world");
	//加载背景
	if (existsTest("gameData/loading.png"))
		loadimage(NULL, _T("gameData/loading.png"), windowA, windowB);
	else
	{
		settextstyle(16, 8, _T("Courier"));	// 设置字体
		settextcolor(GREEN);
		outtextxy(0, 0, "警告：文件gameData/loading.png缺失");
	}
	//注册空的DLC
	DLC d;
	newDLC("NULL", d);
}
void gameLoad()
{
	IMAGE img;
	//首先，导入资源文件中的NotFind，它是固定好了的，不会变动(但一般，不会使用）
	loadimage(&img, _T("PNG"), MAKEINTRESOURCE(NotFind));
	newImg("NULL", img);
	//导入system DLC
}