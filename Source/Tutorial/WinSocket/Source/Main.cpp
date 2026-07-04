#include <iostream>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")  // 链接 Winsock 库

int main() {
    WSADATA wsaData;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char recvBuf[1024];
    int bytesReceived;

    // 1. 初始化 Winsock (请求 2.2 版本)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup 失败\n");
        return 1;
    }

    // 2. 创建监听 Socket (IPv4, TCP)
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        printf("socket 创建失败: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 3. 绑定到本机所有网卡的 8888 端口
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    serverAddr.sin_port = htons(8888);

    if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("bind 失败: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // 4. 开始监听 (最大等待队列长度 5)
    if (listen(listenSocket, 5) == SOCKET_ERROR) {
        printf("listen 失败: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("TCP Server 已启动，监听端口 8888...\n");

    // 5. 循环接受客户端连接
    while (1) {
        clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            printf("accept 失败: %d\n", WSAGetLastError());
            continue;
        }

        // 打印客户端 IP 和端口
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
        printf("新客户端连接: %s:%d\n", clientIP, ntohs(clientAddr.sin_port));

        // 6. 收发数据（回显服务示例）
        while (1) {
            bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0);
            if (bytesReceived > 0) {
                recvBuf[bytesReceived] = '\0';
                printf("收到数据: %s\n", recvBuf);

                // 原样回发给客户端
                send(clientSocket, recvBuf, bytesReceived, 0);
            }
            else if (bytesReceived == 0) {
                printf("客户端主动断开连接\n");
                break;
            }
            else {
                int err = WSAGetLastError();
                if (err != WSAEWOULDBLOCK) {
                    printf("recv 错误: %d\n", err);
                }
                break;
            }
        }

        // 7. 关闭客户端 Socket
        closesocket(clientSocket);
    }

    // 清理资源（通常不会执行到这里，因为上面是死循环）
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}