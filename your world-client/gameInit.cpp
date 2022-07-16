#include"your world.h"
#include"log.h"
#include<graphics.h>
void gameload()
{

}
void gameinit()
{
	initgraph(windowWidth, windowHeight);//初始化屏幕
	logInit();
	sendLog(log_message, "game initialized");
}