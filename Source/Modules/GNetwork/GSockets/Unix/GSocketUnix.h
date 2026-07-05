#pragma once
#include <GSockets/GSocket.h>
#include <GCore/GString.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


// Unix/Linux 地址族转换
inline int ToUnixAddressFamily(GSocketProtocolFamily InProtocolFamily)
{
    int AddressFamily;
    switch (InProtocolFamily)
    {
    case GSocketProtocolFamily::IPv4:
        AddressFamily = AF_INET;
        break;
    case GSocketProtocolFamily::IPv6:
        AddressFamily = AF_INET6;
        break;
    default:
        AddressFamily = AF_UNSPEC;
        break;
    }
    return AddressFamily;
}

// Unix/Linux Socket 类型转换
inline int ToUnixSocketType(GSocketType InSocketType)
{
    int SocketType;
    switch (InSocketType)
    {
    case GSocketType::SOCKTYPE_Datagram:
        SocketType = SOCK_DGRAM;
        break;
    case GSocketType::SOCKTYPE_Streaming:
        SocketType = SOCK_STREAM;
        break;
    case GSocketType::SOCKTYPE_Raw:
        SocketType = SOCK_RAW;
        break;
    default:
        SocketType = -1;
    }
    return SocketType;
}

// Unix/Linux 协议转换
inline int ToUnixProtocol(GSocketType InSocketType)
{
    int Protocol;
    switch (InSocketType)
    {
    case GSocketType::SOCKTYPE_Datagram:
        Protocol = IPPROTO_UDP;
        break;
    case GSocketType::SOCKTYPE_Streaming:
        Protocol = IPPROTO_TCP;
        break;
    default:
        Protocol = -1;
        break;
    }
    return Protocol;
}

// Unix/Linux 特殊地址转换
inline int ToUnixSpecialAddress(GSpecialAddress InSpecialAddress)
{
    int UnixSpecialAddress;
    switch (InSpecialAddress)
    {
    case GSpecialAddress::Any:
        UnixSpecialAddress = INADDR_ANY;
        break;
    case GSpecialAddress::AnyIPv4:
        UnixSpecialAddress = INADDR_ANY;
        break;
    case GSpecialAddress::AnyIPv6:
        // IPv6 使用不同的结构，这里返回 INADDR_ANY 作为默认值
        UnixSpecialAddress = INADDR_ANY;
        break;
    default:
        UnixSpecialAddress = -1;
        break;
    }
    return UnixSpecialAddress;
}

class GEXPORT GSocketUnix : public GSocket
{
public:
    GSocketUnix();
    GSocketUnix(GSocketType InSocketType, GSocketProtocolFamily InSocketProtocol) :
            GSocket(InSocketType, InSocketProtocol)
    {
        UnixAddressFamily    = ToUnixAddressFamily(ProtocolFamily);
        UnixSocketType       = ToUnixSocketType(SocketType);
        UnixProtocol         = ToUnixProtocol(SocketType);
        Handle               = -1;  // Unix 使用 -1 表示无效 Socket
        memset(&SockAddress, 0, sizeof(SockAddress));
        memset(&SockAddress6, 0, sizeof(SockAddress6));
    }

    GSocketUnix(GSocketType InSocketType, GSocketProtocolFamily InSocketProtocol, int InHandle) :
          GSocket(InSocketType, InSocketProtocol), Handle(InHandle)
    {
        UnixAddressFamily    = ToUnixAddressFamily(ProtocolFamily);
        UnixSocketType       = ToUnixSocketType(SocketType);
        UnixProtocol         = ToUnixProtocol(SocketType);
        memset(&SockAddress, 0, sizeof(SockAddress));
        memset(&SockAddress6, 0, sizeof(SockAddress6));
    }
    virtual ~GSocketUnix();

    // 获取 Socket 句柄（文件描述符）
    int GetHandle() const { return Handle; };

    // 纯虚函数实现
    virtual int Create() override final;
    virtual void Close() override final;
    virtual bool Bind(const GSpecialAddress InSpecialAddress, std::uint16_t InPort = 0) override final;
    virtual bool Bind(const GString InAddress, std::uint16_t InPort = 0) override final;
    virtual bool Listen() override final;
    virtual bool Listen(const GSpecialAddress InSpecialAddress, std::uint16_t InPort = 0) override final;
    virtual bool Listen(const GString InAddress, std::uint16_t InPort = 0) override final;
    virtual bool Connect(const GString InAddress, std::uint16_t InPort = 0) override final;
    virtual std::int64_t Read(char* Data, std::int64_t MaxSize) override final;
    virtual std::int64_t Write(const char* Data, std::int64_t MaxSize) override final;
    virtual GSocket *Accept() override final;
private:
    void SetSockAddress(struct sockaddr_in InSockAddress);
private:
    // 设置 Socket 选项（端口重用等）
    bool SetSocketOptions();

    int Handle;                     // Socket 文件描述符 (Unix 使用 int)
    struct sockaddr_in SockAddress;   // IPv4 地址结构
    struct sockaddr_in6 SockAddress6; // IPv6 地址结构
    int UnixAddressFamily;
    int UnixSocketType;
    int UnixProtocol;
    bool bIsIPv6;  // 标记是否使用 IPv6
};