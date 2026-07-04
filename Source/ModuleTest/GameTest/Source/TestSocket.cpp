#include <iostream>
#include <GSockets/Windows/GSocketWindows.h>


int TestTcpServer(int argc, char **argv)
{
    return 0;
}

int TestTcpClient(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET clientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;
    char sendBuf[1024];
    char recvBuf[1024];
    int bytesSent, bytesReceived;

    // 1. 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup 失败\n");
        return 1;
    }

    GSocketWindows *SocketWindows = new GSocketWindows(GSocketType::SOCKTYPE_Streaming, GSocketProtocolFamily::IPv4);
    SocketWindows->Create();
    clientSocket = SocketWindows->GetHandle();

    SocketWindows->Connect("127.0.0.1", 8888);
    printf("成功连接到服务器 127.0.0.1:8888\n");

    // 5. 发送数据
    strcpy(sendBuf, "Hello Server!");
    bytesSent = SocketWindows->Write(sendBuf, (int)strlen(sendBuf));
    if (bytesSent == SOCKET_ERROR) {
        printf("send 失败: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    printf("发送 %d 字节: %s\n", bytesSent, sendBuf);

    // 6. 接收数据
    bytesReceived = 0;
    //bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0);
    bytesReceived = SocketWindows->Read(recvBuf, sizeof(recvBuf) - 1);
    if (bytesReceived > 0) {
        recvBuf[bytesReceived] = '\0';
        printf("收到 %d 字节: %s\n", bytesReceived, recvBuf);
    } else if (bytesReceived == 0) {
        printf("服务器关闭连接\n");
    } else {
        printf("recv 失败: %d\n", WSAGetLastError());
    }

    // 7. 清理资源
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

int TestGSockets(int argc, char **argv)
{
    if (1 == argc)
        return TestTcpServer(argc, argv);
    else
        return TestTcpClient(argc, argv);
}
