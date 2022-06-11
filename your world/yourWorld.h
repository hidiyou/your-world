#pragma once
#ifndef _WIN32
#error ֻ֧��winƽ̨�������������ƽ̨����ɾ��λ��yourWorld.h��#error
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
//�ж��ļ�����
bool existsTest(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
//��������������������������������
//��Ȩ����������ΪCSDN������guotianqing����ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/guotianqing/article/details/100766120
#pragma warning(default : 4996)

//��͸����ͼ�����
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
//	��������������������������������
//		��Ȩ����������ΪCSDN�������������ž��ܡ���ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//		ԭ�����ӣ�https ://blog.csdn.net/weixin_45779485/article/details/102757315

//�ڴ����ļ��������
void putError(const string x)
{
	settextstyle(16, 8, _T("Courier"));	// ��������
	settextcolor(GREEN);
	outtextxy(0, 16, "���棺���ֹ��ϣ���ϸ������Ŀ¼��error.txt��");
	fstream a;
	a.open("error.txt", ios::out | ios::app);
	a << x << endl;
	a.close();
}
//ע������һ��ͼ��
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
//��������ID���ͼ��
IMAGE getImg(const unsigned long long id)
{
	if (imgs.size() >= id)
		return *imgs[id - 1];
	return *imgs[0];
}
//�������Ʋ���ͼƬ
IMAGE getImg(const string name)
{
	if (imgMap[name] != 0)
	{
		return getImg(imgMap[name]);
	}
	return *imgs[0];
}
//��ȫ�ؼ���һ��ͼƬ
void loadimage_s(IMAGE* img, const string name)
{
	if (existsTest(name))
	{
		loadimage(img, _T(name.c_str()));
	}
	else
	{
		putError("�޷�����" + name + "�ļ�");
	}
}
//����loadimg_s��ȫ���벢ע��һ��ͼ��
unsigned long long loadAndNewImg_s(const string imgName,const string nameInGame)
{
	IMAGE img;
	loadimage_s(&img, imgName);
	return newImg(nameInGame, img);
}
//����loadAndNewImg_s�������ļ�����Ϸ��ͬ����ͼ��ע�ắ��
unsigned long long loadAndNewImg_s(const string imgName)
{
	return loadAndNewImg_s(imgName, imgName);
}
//����loadimage���벢ע��һ��ͼ��
unsigned long long loadAndNewImg(const string imgName, const string nameInGame)
{
	IMAGE img;
	loadimage(&img, _T(imgName.c_str()));
	return newImg(nameInGame, img);
}
//����loadAndNewImg�������ļ�����Ϸ��ͬ����ͼ��ע�ắ��
unsigned long long loadAndNewImg(const string imgName)
{
	return loadAndNewImg(imgName, imgName);
}
