#pragma once
#include "resource.h"
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
}
void gameLoad()
{
	IMAGE img;
	//首先，导入资源文件中的NotFind，它是固定好了的，不会变动
	loadimage(&img, _T("PNG"), MAKEINTRESOURCE(NotFind));
	newImg("NULL", img);
	//加载DLC列表
	ifstream fin;
	if(existsTest("DLC.txt"))
		fin.open("DLC.txt");
	else
	{
		putError("DLC.txt未找到，请确认文件是否存在，一般，可以通过重新安装解决");
		Sleep(1000);
		exit(1);
	}
	//加载当前的DLC的图片
	string s;
	while (getline(fin,s))
	{
		if (s[0] == '#')
		{
			continue;
		}
		ifstream FIN;
		if (existsTest("gameData/DLC/" + s + "/pictrue.txt"))
			FIN.open("gameData/DLC/" + s + "/pictrue.txt");
		else
		{
			putError("gameData/DLC/" + s + "/pictrue.txt" + "未找到，请确认文件是否存在，一般，可以通过重新安装解决");
			Sleep(1000);
			exit(1);
		}
		string S;
		while (getline(FIN, S))
		{
			loadAndNewImg_s("gameData/DLC/" + s + "/pictrue.txt" + S, S);
		}
	}
}