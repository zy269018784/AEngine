#include <iostream>
#include <GSockets/Windows/GSocketWindows.h>
int TestGSockets(int argc, char **argv)
{
    std::cout << "hello world" << std::endl;

    WSADATA wsaData;
    // 1. 初始化 Winsock (请求 2.2 版本)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup 失败\n");
        return 1;
    }


    GSocketWindows *Socket = new GSocketWindows();
    Socket->Create();
  //  Socket->Bind();

    delete Socket;
    return 0;
}