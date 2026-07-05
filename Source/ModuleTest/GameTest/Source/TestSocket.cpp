#include <iostream>
#include <GSockets/GSocket.h>
#include <GSockets/GSocketSubsystem.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
int TestTcpServer(int argc, char **argv)
{
#if 0
    // 1.
    GSocketSubsystem *SocketSubsystemWindows = GSocketSubsystem::CreateGSocketSubsystem();
    SocketSubsystemWindows->Init();

    // 2.
    GSocket *Socket = SocketSubsystemWindows->CreateGSocket(GSocketType::SOCKTYPE_Streaming, GSocketProtocolFamily::IPv4);
    Socket->Create();

    Socket->Bind(GSpecialAddress::Any, 8888);

    Socket->Listen();

    char recvBuf[1024];
    int count = 0;
    while (1)
    {
        GSocket *SocketClient = nullptr;
        SocketClient = Socket->Accept();
        if (!SocketClient)
        {
            printf("continue = %d\n", count++);
            continue;
        }
        while (1)
        {
            auto bytesReceived = SocketClient->Read(recvBuf, sizeof(recvBuf) - 1);
            printf("bytesReceived = %d\n", bytesReceived);
            if (bytesReceived > 0)
            {
                recvBuf[bytesReceived] = '\0';
                printf("recv : %s\n", recvBuf);

                // 原样回发给客户端
                SocketClient->Write(recvBuf, bytesReceived);
            }
            else if (bytesReceived == 0)
            {
                printf("client disconnect\n");
                break;
            }
            else
            {
                break;
            }

        }
        SocketClient->Close();
    }

    return 0;
#else

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
#endif
}

int TestTcpClient(int argc, char **argv)
{
    char sendBuf[1024];
    char recvBuf[1024];
    int bytesSent, bytesReceived;

    // 1.
    GSocketSubsystem *SocketSubsystemWindows = GSocketSubsystem::CreateGSocketSubsystem();
    SocketSubsystemWindows->Init();

    // 2.
    GSocket *Socket = SocketSubsystemWindows->CreateGSocket(GSocketType::SOCKTYPE_Streaming, GSocketProtocolFamily::IPv4);
    Socket->Create();

    // 3.
    Socket->Connect(argv[1], 8888);
    printf("成功连接到服务器 127.0.0.1:8888\n");

    // 4.
    //strcpy(sendBuf, "Hello Server!");
    strcpy(sendBuf, argv[2]);
    bytesSent = Socket->Write(sendBuf, (int)strlen(sendBuf));
    printf("send %d nBytes: %s\n", bytesSent, sendBuf);

    // 5. 接收数据
    bytesReceived = 0;
    //bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0);
    bytesReceived = Socket->Read(recvBuf, sizeof(recvBuf) - 1);
    if (bytesReceived > 0) {
        recvBuf[bytesReceived] = '\0';
        printf("recv %d bytes, data: %s\n", bytesReceived, recvBuf);
    } else if (bytesReceived == 0) {
        printf("服务器关闭连接\n");
    } else {
       // printf("recv 失败: %d\n", WSAGetLastError());
    }

    // 6. 清理资源
    Socket->Close();
    delete Socket;
    delete SocketSubsystemWindows;
    return 0;
}

int TestGSockets(int argc, char **argv)
{
    if (1 == argc)
        return TestTcpServer(argc, argv);
    else
        return TestTcpClient(argc, argv);
}
