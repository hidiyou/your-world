//游戏服务
#include"yourWorld.h"
//初始化与加载服务
#include"gameInit.h"
//DLC服务
#include"DLC.h"
int main()
{
	gameInit();
	gameLoad();
#pragma warning(disable : 6031)
//问题已确认
	_getch();
#pragma warning(disable : 6031)
}