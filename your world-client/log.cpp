#include <winsock2.h>
#include <string.h>
#include"log.h"
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
WSADATA wsaData;
SOCKET sock;
sockaddr_in servAddr;
sockaddr fromAddr;
int addrLen = sizeof(fromAddr);
void logInit()
{
    //初始化DLL
    
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    //服务器地址信息
    memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
    servAddr.sin_family = PF_INET;
#pragma warning(suppress : 4996)
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(2333);
}
void logStop()
{
    closesocket(sock);
    WSACleanup();
}
char buf[bufSize];
void sendLog(const char severity, const char content[bufSize - 2])
{
    buf[0] = severity;
    buf[1] = 'C';
    for (int i = 2; i < bufSize; ++i)
    {
        buf[i] = content[i - 2];
    }
    sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
}