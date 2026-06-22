#include <GNetwork/GTcp/GTcpServer.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>

int TestGTcpServer(int argc, char **argv)
{
    std::cout << "hello, world" << std::endl;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 监听所有网卡
    server_addr.sin_port = htons(8080);        // 端口号，转为网络字节序

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 128) < 0) {  // 128 是等待连接队列的最大长度
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        int client_fd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("accept");
            exit(1);
        }

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
        printf("客户端 %s:%d 已连接\n", ip, ntohs(client_addr.sin_port));
    }
    return 0;
}



#define BUFFER_SIZE 4096
#define DEFAULT_PORT 8080
#define CONNECT_TIMEOUT 5  // 连接超时（秒）
#define READ_TIMEOUT 10    // 读超时（秒）

// 打印错误并退出
void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// 设置 socket 非阻塞
int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

// 设置 socket 超时（使用 setsockopt）
int set_socket_timeout(int fd, int recv_sec, int send_sec) {
    struct timeval tv;

    if (recv_sec > 0) {
        tv.tv_sec = recv_sec;
        tv.tv_usec = 0;
        if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
            return -1;
    }

    if (send_sec > 0) {
        tv.tv_sec = send_sec;
        tv.tv_usec = 0;
        if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
            return -1;
    }
    return 0;
}

// 带超时的 connect（使用非阻塞 + select）
int connect_with_timeout(int sockfd, struct sockaddr *addr, socklen_t addrlen, int timeout_sec) {
    if (timeout_sec <= 0) {
        return connect(sockfd, addr, addrlen);
    }

    // 设置为非阻塞
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    int ret = connect(sockfd, addr, addrlen);
    if (ret == 0) {
        // 立即连接成功
        fcntl(sockfd, F_SETFL, flags);
        return 0;
    }

    if (errno != EINPROGRESS) {
        fcntl(sockfd, F_SETFL, flags);
        return -1;
    }

    // 等待连接完成
    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);

    struct timeval tv;
    tv.tv_sec = timeout_sec;
    tv.tv_usec = 0;

    ret = select(sockfd + 1, NULL, &fdset, NULL, &tv);
    if (ret == 0) {
        // 超时
        errno = ETIMEDOUT;
        fcntl(sockfd, F_SETFL, flags);
        return -1;
    }

    if (ret == -1) {
        fcntl(sockfd, F_SETFL, flags);
        return -1;
    }

    // 检查连接是否成功
    int error = 0;
    socklen_t len = sizeof(error);
    if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
        fcntl(sockfd, F_SETFL, flags);
        return -1;
    }

    if (error != 0) {
        errno = error;
        fcntl(sockfd, F_SETFL, flags);
        return -1;
    }

    // 恢复阻塞模式
    fcntl(sockfd, F_SETFL, flags);
    return 0;
}

// 解析域名或 IP
struct sockaddr_in resolve_host(const char *hostname, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // 尝试直接解析为 IP
    if (inet_pton(AF_INET, hostname, &addr.sin_addr) == 1) {
        return addr;
    }

    // DNS 解析
    struct hostent *he = gethostbyname(hostname);
    if (he == NULL) {
        fprintf(stderr, "无法解析主机名: %s\n", hostname);
        exit(EXIT_FAILURE);
    }

    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
    return addr;
}

// 发送完整数据（处理部分发送）
ssize_t send_all(int fd, const char *buffer, size_t len) {
    size_t total_sent = 0;
    while (total_sent < len) {
        ssize_t sent = send(fd, buffer + total_sent, len - total_sent, 0);
        if (sent < 0) {
            if (errno == EINTR) continue;  // 被信号中断，重试
            return -1;
        }
        if (sent == 0) break;  // 连接关闭
        total_sent += sent;
    }
    return total_sent;
}

// 接收完整数据（直到缓冲区满或连接关闭）
ssize_t recv_all(int fd, char *buffer, size_t max_len) {
    size_t total_recv = 0;
    while (total_recv < max_len) {
        ssize_t recvd = recv(fd, buffer + total_recv, max_len - total_recv, 0);
        if (recvd < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        if (recvd == 0) break;  // 对端关闭
        total_recv += recvd;
    }
    return total_recv;
}

// ============ 主函数 ============
int TestGTcpClient(int argc, char *argv[]) {

    printf("TestGTcpClient\n");
    // 参数处理
    const char *server_ip = "127.0.0.1";
    int port = 8080;

  //  if (argc >= 2) server_ip = argv[1];
   // if (argc >= 3) port = atoi(argv[2]);

    printf("连接目标: %s:%d\n", server_ip, port);

    // 1. 创建 socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error_exit("socket");
    }

    // 2. 设置 SO_REUSEADDR（客户端可选，但有利于快速重连）
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt SO_REUSEADDR");
        // 非致命错误，继续执行
    }

    // 3. 设置超时
    if (set_socket_timeout(sockfd, READ_TIMEOUT, 5) < 0) {
        perror("set_socket_timeout");
    }

    // 4. 解析服务器地址
    struct sockaddr_in server_addr = resolve_host(server_ip, port);

    // 5. 连接服务器（带超时）
    printf("正在连接...\n");
    if (connect_with_timeout(sockfd, (struct sockaddr*)&server_addr,
                             sizeof(server_addr), CONNECT_TIMEOUT) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("✅ 连接成功！\n");

    // 6. 发送数据
    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];

    for (int i = 0; i < 3; i++) {
        // 构造消息
        snprintf(send_buffer, sizeof(send_buffer),
                "Hello from client, message #%d\n", i + 1);

        // 发送
        ssize_t sent = send_all(sockfd, send_buffer, strlen(send_buffer));
        if (sent < 0) {
            perror("send");
            break;
        }
        printf("📤 发送: %s", send_buffer);

        // 接收回应
        ssize_t recvd = recv_all(sockfd, recv_buffer, sizeof(recv_buffer) - 1);
        if (recvd < 0) {
            perror("recv");
            break;
        } else if (recvd == 0) {
            printf("⚠️  服务器关闭了连接\n");
            break;
        }

        recv_buffer[recvd] = '\0';
        printf("📥 收到: %s", recv_buffer);

        sleep(1);
    }

    // 7. 关闭连接
    // 优雅关闭：发送 FIN
    if (shutdown(sockfd, SHUT_WR) < 0) {
        perror("shutdown");
    }

    // 继续接收直到对端关闭（可选）
    ssize_t remaining;
    while ((remaining = recv(sockfd, recv_buffer, sizeof(recv_buffer), 0)) > 0) {
        printf("📥 剩余数据: %.*s", (int)remaining, recv_buffer);
    }

    close(sockfd);
    printf("🔚 连接已关闭\n");

    return 0;
}