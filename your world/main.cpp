//��Ϸ����
#include"yourWorld.h"
//��ʼ������ط���
#include"gameInit.h"
//DLC����
#include"DLC.h"
int main()
{
	gameInit();
	gameLoad();
#pragma warning(disable : 6031)
//������ȷ��
	_getch();
#pragma warning(disable : 6031)
}