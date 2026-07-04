#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int TcpServer() {
    int listenSocket;
    int clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char recvBuf[1024];
    int bytesReceived;

    // 1. 创建监听 Socket (IPv4, TCP) - Linux 不需要 WSAStartup
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == -1) {
        perror("socket 创建失败");
        return 1;
    }

    // 2. 设置 SO_REUSEADDR 选项，允许端口重用（防止 "Address already in use"）
    int opt = 1;
    if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt 失败");
        close(listenSocket);
        return 1;
    }

    // 3. 绑定到本机所有网卡的 8888 端口
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    serverAddr.sin_port = htons(8888);

    if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind 失败");
        close(listenSocket);
        return 1;
    }

    // 4. 开始监听 (最大等待队列长度 5)
    if (listen(listenSocket, 5) == -1) {
        perror("listen 失败");
        close(listenSocket);
        return 1;
    }

    printf("TCP Server 已启动，监听端口 8888...\n");

    // 5. 循环接受客户端连接
    while (1) {
        clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("accept 失败");
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
                // Linux 使用 errno 判断错误
                if (errno != EWOULDBLOCK && errno != EAGAIN) {
                    perror("recv 错误");
                }
                break;
            }
        }

        // 7. 关闭客户端 Socket
        close(clientSocket);
    }

    // 清理资源（通常不会执行到这里，因为上面是死循环）
    close(listenSocket);
    return 0;
}
