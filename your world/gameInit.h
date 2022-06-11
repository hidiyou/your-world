#pragma once
#include "resource.h"
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
}
void gameLoad()
{
	IMAGE img;
	//���ȣ�������Դ�ļ��е�NotFind�����ǹ̶����˵ģ�����䶯
	loadimage(&img, _T("PNG"), MAKEINTRESOURCE(NotFind));
	newImg("NULL", img);
	//����DLC�б�
	ifstream fin;
	if(existsTest("DLC.txt"))
		fin.open("DLC.txt");
	else
	{
		putError("DLC.txtδ�ҵ�����ȷ���ļ��Ƿ���ڣ�һ�㣬����ͨ�����°�װ���");
		Sleep(1000);
		exit(1);
	}
	//���ص�ǰ��DLC��ͼƬ
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
			putError("gameData/DLC/" + s + "/pictrue.txt" + "δ�ҵ�����ȷ���ļ��Ƿ���ڣ�һ�㣬����ͨ�����°�װ���");
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