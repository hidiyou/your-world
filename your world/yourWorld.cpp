#include<Windows.h>
#include<conio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<graphics.h>
#include"DLC.h"


using namespace std;
vector<IMAGE*> imgs;
unsigned long long COI = 1;
map<string, unsigned long long> imgMap;

#pragma warning(disable : 4996)
bool existsTest(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
#pragma warning(default : 4996)
//��������������������������������
//��Ȩ����������ΪCSDN������guotianqing����ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/guotianqing/article/details/100766120

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
unsigned long long newImg(const string name,const IMAGE img)
{
	IMAGE* Img = new IMAGE;
	Img->operator=(img);
	if (imgMap[name] != 0)
	{
		imgs[imgMap[name]] = Img;
		return imgMap[name];
	}
	imgs.push_back(Img);
	imgMap[name] = COI++;
	return imgMap[name];
}
IMAGE getImg(const unsigned long long id)
{
	if (imgs.size() >= id)
		return *imgs[id - 1];
	return *imgs[0];//�Ҳ��������ش���ͼƬ
}
IMAGE getImg(const string name)
{
	if (imgMap[name] != 0)
	{
		return getImg(imgMap[name]);
	}
	return *imgs[0];
}
unsigned long long getImgId(const string name)
{
	return imgMap[name];
}
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
unsigned long long loadAndNewImg_s(const string imgName, const string nameInGame)
{
	IMAGE img;
	loadimage_s(&img, imgName);
	return newImg(nameInGame, img);
}
unsigned long long loadAndNewImg_s(const string imgName)
{
	return loadAndNewImg_s(imgName, imgName);
}
unsigned long long loadAndNewImg(const string imgName, const string nameInGame)
{
	IMAGE img;
	loadimage(&img, _T(imgName.c_str()));
	return newImg(nameInGame, img);
}
unsigned long long loadAndNewImg(const string imgName)
{
	return loadAndNewImg(imgName, imgName);
}