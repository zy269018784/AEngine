#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

int TcpClient(int argc, char* argv[]) {
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

    // 2. 创建客户端 Socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        printf("socket 创建失败: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 3. 设置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);  // 服务器端口
    
    // 方式1：使用 inet_addr（仅 IPv4）
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);  // 本机服务器
    
    // 方式2：使用 inet_pton（推荐）
    // if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) != 1) {
    //     printf("无效的 IP 地址\n");
    //     closesocket(clientSocket);
    //     WSACleanup();
    //     return 1;
    // }

    // 4. 连接到服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("连接失败: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    printf("成功连接到服务器 127.0.0.1:8888\n");

    // 5. 发送数据
    strcpy(sendBuf, "Hello Server!");
    bytesSent = send(clientSocket, sendBuf, (int)strlen(sendBuf), 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("send 失败: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    printf("发送 %d 字节: %s\n", bytesSent, sendBuf);

    // 6. 接收数据
    bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0);
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