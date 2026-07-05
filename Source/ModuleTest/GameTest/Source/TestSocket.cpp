#include <iostream>
#include <GSockets/GSocket.h>
#include <GSockets/GSocketSubsystem.h>

int TestTcpServer(int argc, char **argv)
{
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
