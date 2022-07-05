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
	_getch();
}