#pragma once
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#ifndef _WIN32
#error ֻ֧��winƽ̨�������������ƽ̨����ɾ��λ��yourWorld.h��#error
#endif //_WIN32
using namespace std;
const int windowA = 1200;
const int windowB = 675;

//�ж��ļ�����
bool existsTest(const std::string& name);
//��͸����ͼ�����
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);
//�ڴ����ļ��������
void putError(const string x);
//ע������һ��ͼ��
unsigned long long newImg(const string name, const IMAGE img);
//��������ID���ͼ��
IMAGE getImg(const unsigned long long id);
//�������Ʋ���ͼƬ
IMAGE getImg(const string name);
//�������Ʋ���ID
unsigned long long getImgId(const string name);
//��ȫ�ؼ���һ��ͼƬ
void loadimage_s(IMAGE* img, const string name);
//����loadimg_s��ȫ���벢ע��һ��ͼ��
unsigned long long loadAndNewImg_s(const string imgName, const string nameInGame);
//����loadAndNewImg_s�������ļ�����Ϸ��ͬ����ͼ��ע�ắ��
unsigned long long loadAndNewImg_s(const string imgName);
//����loadimage���벢ע��һ��ͼ��
unsigned long long loadAndNewImg(const string imgName, const string nameInGame);
//����loadAndNewImg�������ļ�����Ϸ��ͬ����ͼ��ע�ắ��
unsigned long long loadAndNewImg(const string imgName);