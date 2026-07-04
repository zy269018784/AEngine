#pragma once
#include <GSockets/GSocket.h>
#include <winsock2.h>
#include <GCore/GString.h>
inline int ToWindowsAddressFamily(GSocketProtocolFamily InProtocolFamily)
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

inline int ToWindowsSocketType(GSocketType InSocketType)
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

inline int ToWindowsProtocol(GSocketType InSocketType)
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

inline int ToWindowsSpecialAddress(GSpecialAddress InSpecialAddress)
{
    int WindowsSpecialAddress;
    switch (InSpecialAddress)
    {
    case GSpecialAddress::Any:
        WindowsSpecialAddress = INADDR_ANY;
        break;
    case GSpecialAddress::AnyIPv4:
        WindowsSpecialAddress = INADDR_ANY;
        break;
    case GSpecialAddress::AnyIPv6:
        WindowsSpecialAddress = INADDR_ANY;
        break;
    default:
        WindowsSpecialAddress = -1;
        break;
    }
    return WindowsSpecialAddress;
}

class GEXPORT GSocketWindows : public GSocket
{
public:
    GSocketWindows();
    inline GSocketWindows(GSocketType InSocketType, GSocketProtocolFamily InSocketProtocol) :
            GSocket(InSocketType, InSocketProtocol)
    {
        WindowsAddressFamily    = ToWindowsAddressFamily(ProtocolFamily);
        WindowsSocketType       = ToWindowsSocketType(SocketType);
        WindowsProtocol         = ToWindowsProtocol(SocketType);
    }
    virtual ~GSocketWindows();
    SOCKET GetHandle() const { return Handle; };

    virtual int Create() override final;
    virtual bool Bind(const GSpecialAddress, std::uint16_t InPort = 0) override final;
    virtual bool Bind(const GString InAddress, std::uint16_t InPort = 0) override final;
    virtual bool Listen()  override final;
    virtual bool Listen(const GSpecialAddress, std::uint16_t InPort = 0) override final;
    virtual bool Listen(const GString InAddress, std::uint16_t InPort = 0) override final;
    virtual bool Connect(const GString InAddress, std::uint16_t InPort = 0) override final;
    virtual std::uint64_t Read(char *Data, std::uint64_t MaxSize)  override final;
    virtual std::uint64_t Write(const char *Data, std::uint64_t MaxSize)  override final;
private:
    SOCKET Handle;
    struct sockaddr_in SockAddress;
    int WindowsAddressFamily;
    int WindowsSocketType;
    int WindowsProtocol;
};

