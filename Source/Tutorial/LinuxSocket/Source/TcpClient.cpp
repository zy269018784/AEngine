#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int TcpClient() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char sendBuf[1024];
    char recvBuf[1024];
    int bytesSent, bytesReceived;

    // 1. 创建客户端 Socket（Linux 不需要 WSAStartup）
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == -1) {
        perror("socket 创建失败");
        return 1;
    }

    // 2. 设置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);  // 服务器端口

    // 将 IP 地址从字符串转换为网络字节序
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) != 1) {
        fprintf(stderr, "无效的 IP 地址\n");
        close(clientSocket);
        return 1;
    }

    // 3. 连接到服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("连接失败");
        close(clientSocket);
        return 1;
    }
    printf("成功连接到服务器 127.0.0.1:8888\n");

    // 4. 发送数据
    strcpy(sendBuf, "Hello Server!");
    bytesSent = send(clientSocket, sendBuf, strlen(sendBuf), 0);
    if (bytesSent == -1) {
        perror("send 失败");
        close(clientSocket);
        return 1;
    }
    printf("发送 %d 字节: %s\n", bytesSent, sendBuf);

    // 5. 接收数据
    bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0);
    if (bytesReceived > 0) {
        recvBuf[bytesReceived] = '\0';
        printf("收到 %d 字节: %s\n", bytesReceived, recvBuf);
    } else if (bytesReceived == 0) {
        printf("服务器关闭连接\n");
    } else {
        perror("recv 失败");
    }

    // 6. 清理资源
    close(clientSocket);
    return 0;
}

int main() {
    return TcpClient();
}