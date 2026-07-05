#include <GSockets/Unix/GSocketUnix.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

GSocketUnix::GSocketUnix()
    : GSocket(GSocketType::SOCKTYPE_Streaming, GSocketProtocolFamily::IPv4)
{
    UnixAddressFamily = AF_INET;
    UnixSocketType = SOCK_STREAM;
    UnixProtocol = IPPROTO_TCP;
    Handle = -1;
    bIsIPv6 = false;
    memset(&SockAddress, 0, sizeof(SockAddress));
    memset(&SockAddress6, 0, sizeof(SockAddress6));
}

GSocketUnix::~GSocketUnix()
{
    Close();
}

bool GSocketUnix::SetSocketOptions()
{
    // 设置 SO_REUSEADDR 选项，允许端口重用
    int opt = 1;
    if (setsockopt(Handle, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        return false;
    }

    // 设置 SO_REUSEPORT（可选，某些系统支持）
    #ifdef SO_REUSEPORT
    if (setsockopt(Handle, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        // 某些系统可能不支持 SO_REUSEPORT，不视为致命错误
    }
    #endif

    return true;
}

int GSocketUnix::Create()
{
    if (Handle != -1) {
        return 0;
    }

    // 创建 Socket
    Handle = socket(UnixAddressFamily, UnixSocketType, UnixProtocol);
    if (Handle == -1) {
        return -1;
    }

    // 设置 Socket 选项
    if (!SetSocketOptions()) {
        Close();
        return -1;
    }

    return 0;
}

void GSocketUnix::Close()
{
    if (Handle != -1) {
        close(Handle);
        Handle = -1;
    }
}

bool GSocketUnix::Bind(const GSpecialAddress InSpecialAddress, std::uint16_t InPort)
{
    if (Handle == -1) {
        return false;
    }

    // 根据特殊地址类型设置
    switch (InSpecialAddress)
    {
    case GSpecialAddress::Any:
    case GSpecialAddress::AnyIPv4:
    {
        // IPv4 绑定所有网卡
        SockAddress.sin_family = AF_INET;
        SockAddress.sin_addr.s_addr = INADDR_ANY;
        SockAddress.sin_port = htons(InPort);
        bIsIPv6 = false;

        if (bind(Handle, (struct sockaddr*)&SockAddress, sizeof(SockAddress)) == -1) {
            return false;
        }
        break;
    }
    case GSpecialAddress::AnyIPv6:
    {
        // IPv6 绑定所有网卡
        SockAddress6.sin6_family = AF_INET6;
        SockAddress6.sin6_addr = in6addr_any;
        SockAddress6.sin6_port = htons(InPort);
        bIsIPv6 = true;

        if (bind(Handle, (struct sockaddr*)&SockAddress6, sizeof(SockAddress6)) == -1) {
            return false;
        }
        break;
    }
    case GSpecialAddress::LocalHost:
    {
        // IPv4 本地回环
        SockAddress.sin_family = AF_INET;
        SockAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        SockAddress.sin_port = htons(InPort);
        bIsIPv6 = false;

        if (bind(Handle, (struct sockaddr*)&SockAddress, sizeof(SockAddress)) == -1) {
            return false;
        }
        break;
    }
    case GSpecialAddress::LocalHostIPv6:
    {
        // IPv6 本地回环
        SockAddress6.sin6_family = AF_INET6;
        SockAddress6.sin6_addr = in6addr_loopback;
        SockAddress6.sin6_port = htons(InPort);
        bIsIPv6 = true;

        if (bind(Handle, (struct sockaddr*)&SockAddress6, sizeof(SockAddress6)) == -1) {
            return false;
        }
        break;
    }
    default:
        return false;
    }

    return true;
}

bool GSocketUnix::Bind(const GString InAddress, std::uint16_t InPort)
{
    if (Handle == -1) {
        return false;
    }

    // 尝试解析 IPv4 地址
    SockAddress.sin_family = AF_INET;
    SockAddress.sin_port = htons(InPort);

    if (inet_pton(AF_INET, InAddress.ConstStr(), &SockAddress.sin_addr) == 1) {
        // IPv4 地址解析成功
        bIsIPv6 = false;
        if (bind(Handle, (struct sockaddr*)&SockAddress, sizeof(SockAddress)) == -1) {
            return false;
        }
        return true;
    }

    // 尝试解析 IPv6 地址
    SockAddress6.sin6_family = AF_INET6;
    SockAddress6.sin6_port = htons(InPort);

    if (inet_pton(AF_INET6, InAddress.ConstStr(), &SockAddress6.sin6_addr) == 1) {
        // IPv6 地址解析成功
        bIsIPv6 = true;
        if (bind(Handle, (struct sockaddr*)&SockAddress6, sizeof(SockAddress6)) == -1) {
            return false;
        }
        return true;
    }

    return false;
}

bool GSocketUnix::Listen()
{
    if (Handle == -1) {
        return false;
    }

    if (listen(Handle, 5) == -1) {
        return false;
    }

    return true;
}

bool GSocketUnix::Listen(const GSpecialAddress InSpecialAddress, std::uint16_t InPort)
{
    if (!Bind(InSpecialAddress, InPort)) {
        return false;
    }
    return Listen();
}

bool GSocketUnix::Listen(const GString InAddress, std::uint16_t InPort)
{
    if (!Bind(InAddress, InPort)) {
        return false;
    }
    return Listen();
}

bool GSocketUnix::Connect(const GString InAddress, std::uint16_t InPort)
{
    if (Handle == -1) {
        return false;
    }

    struct sockaddr_in serverAddr;
    struct sockaddr_in6 serverAddr6;
    bool bIsIPv6Addr = false;

    // 尝试解析 IPv4
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(InPort);

    if (inet_pton(AF_INET, InAddress.ConstStr(), &serverAddr.sin_addr) == 1) {
        if (connect(Handle, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            return false;
        }
        return true;
    }

    // 尝试解析 IPv6
    serverAddr6.sin6_family = AF_INET6;
    serverAddr6.sin6_port = htons(InPort);

    if (inet_pton(AF_INET6, InAddress.ConstStr(), &serverAddr6.sin6_addr) == 1) {
        if (connect(Handle, (struct sockaddr*)&serverAddr6, sizeof(serverAddr6)) == -1) {
            return false;
        }
        return true;
    }

    return false;
}

std::int64_t GSocketUnix::Read(char* Data, std::int64_t MaxSize)
{
    if (Handle == -1) {
        return 0;
    }

    if (Data == nullptr || MaxSize == 0) {
        return 0;
    }

    ssize_t bytesReceived = recv(Handle, Data, MaxSize, 0);

    if (bytesReceived > 0) {
        return static_cast<std::uint64_t>(bytesReceived);
    }
    else if (bytesReceived == 0) {
        return 0;
    }
    else {
        if (errno != EWOULDBLOCK && errno != EAGAIN) {
            // 错误处理，但不再输出日志
        }
        return 0;
    }
}

std::int64_t GSocketUnix::Write(const char* Data, std::int64_t MaxSize)
{
    if (Handle == -1) {
        return 0;
    }

    if (Data == nullptr || MaxSize == 0) {
        return 0;
    }

    ssize_t bytesSent = send(Handle, Data, MaxSize, 0);

    if (bytesSent > 0) {
        return static_cast<std::uint64_t>(bytesSent);
    }
    else if (bytesSent == -1) {
        if (errno != EWOULDBLOCK && errno != EAGAIN) {
            // 错误处理，但不再输出日志
        }
        return 0;
    }
    
    return 0;
}

GSocket *GSocketUnix::Accept()
{
    GSocketWindows *Socket = nullptr;
    int AddrLen = 0;
    struct sockaddr_in ClientSockAddress;
    SOCKET ClientHandle = accept(Handle, (struct sockaddr*)&ClientSockAddress, &AddrLen);

    Socket = new GSocketUnix(SocketType, ProtocolFamily, ClientHandle);
    Socket->SetSockAddress(ClientSockAddress);
    return Socket;
}