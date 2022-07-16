#include <iostream>
#include <winsock2.h>
#include<memory.h>
using namespace std;
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 1024*10
//颜色输出 来自：https://blog.csdn.net/qq_42885747/article/details/103835671
void COLOR_PRINT(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
}
char buffer[BUF_SIZE];  //缓冲区
int main(int argc,char *argv[]) 
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    //绑定套接字
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
    servAddr.sin_family = PF_INET;  //使用IPv4地址
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
    servAddr.sin_port = htons(2333);  //端口
    bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
    //接收客户端请求
    SOCKADDR clntAddr;  //客户端地址信息
    int nSize = sizeof(SOCKADDR);
    COLOR_PRINT(15);
    cout << "your world 日志查看器\n0.0.0版\n";
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &clntAddr, &nSize);
        COLOR_PRINT(15);
        if (buffer[1] == 'C')
        {
            cout << "客户端：";
        }
        else
        {
            cout << "服务端：";
        }
        switch (buffer[0])
        {
        case 1:
            COLOR_PRINT(15);
            break;
        case 2:
            COLOR_PRINT(6);
            break;
        case 3:
            COLOR_PRINT(4);
            break;
        case 4:
            COLOR_PRINT(4 * 16 + 15);
            cout << "致命错误！  ";
            break;
        default:
            COLOR_PRINT(1);
            break;
        }
        for (int i = 2; i < strLen; ++i)
        {
            cout << buffer[i];
        }
        cout << endl;
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}