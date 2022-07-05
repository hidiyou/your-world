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
	//��ʼ��error.txt
	fstream a;
	a.open("error.txt", ios::out);
	a << "��ʼ��¼" << endl;
	a.close();
	//���д���
	int scrWidth, scrHeight;
	HWND hWnd = GetHWnd();
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, HWND_TOPMOST, (scrWidth - rect.right) / 2, (scrHeight - rect.bottom) / 2, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
	//��ʼ������
	initgraph(windowA, windowB);
	cleardevice();
	setbkmode(TRANSPARENT);
	SetConsoleTitle("your world");
	//���ر���
	if (existsTest("gameData/loading.png"))
		loadimage(NULL, _T("gameData/loading.png"), windowA, windowB);
	else
	{
		settextstyle(16, 8, _T("Courier"));	// ��������
		settextcolor(GREEN);
		outtextxy(0, 0, "���棺�ļ�gameData/loading.pngȱʧ");
	}
	//ע��յ�DLC
	DLC d;
	newDLC("NULL", d);
}
void gameLoad()
{
	IMAGE img;
	//���ȣ�������Դ�ļ��е�NotFind�����ǹ̶����˵ģ�����䶯(��һ�㣬����ʹ�ã�
	loadimage(&img, _T("PNG"), MAKEINTRESOURCE(NotFind));
	newImg("NULL", img);
	//����system DLC
}