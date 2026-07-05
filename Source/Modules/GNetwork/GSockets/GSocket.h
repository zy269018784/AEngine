#pragma once
#include <GCore/GExport.h>
#include <GCore/GString.h>
#include <cstdint>

/** Indicates the socket protocol of socket being used, typically for BSD Sockets */
enum class GSocketProtocolFamily : std::uint8_t
{
    /** No protocol family specification. Typically defined as AF_UNSPEC */
    None,
    /** IPv4 and IPv6 respectively. */
    IPv4,
    IPv6
};

enum GSocketType
{
    /** Not bound to a protocol yet */
    SOCKTYPE_Unknown,
    /** A UDP type socket */
    SOCKTYPE_Datagram,
    /** A TCP type socket */
    SOCKTYPE_Streaming,
    /** A Raw type socket */
    SOCKTYPE_Raw
};

enum GSocketProtocol : std::uint8_t
{
    /** A UDP type socket */
    SOCKPROTOCOL_UDP,
    /** A TCP type socket */
    SOCKPROTOCOL_TCP,
};

enum GSpecialAddress {
    Null = 0,           // 空地址对象
    Broadcast = 1,      // IPv4 广播地址 (255.255.255.255)
    LocalHost = 2,      // IPv4 本地回环地址 (127.0.0.1)
    LocalHostIPv6 = 3,  // IPv6 本地回环地址 (::1)
    Any = 4,            // 双栈 Any 地址（IPv4 + IPv6）
    AnyIPv6 = 5,        // IPv6 Any 地址 (::)
    AnyIPv4 = 6         // IPv4 Any 地址 (0.0.0.0)
};

class GEXPORT GSocket
{
public:
    GSocket();
    inline GSocket(GSocketType InSocketType, GSocketProtocolFamily InSocketProtocol) :
        SocketType(InSocketType),  ProtocolFamily(InSocketProtocol)
    {

    }
    virtual ~GSocket();
public:
    virtual int Create() = 0;
    virtual void Close() = 0;
    virtual bool Bind(const GSpecialAddress InAddress, std::uint16_t InPort = 0) = 0;
    virtual bool Bind(const GString InAddress, std::uint16_t InPort = 0) = 0;
    virtual bool Listen() = 0;
    virtual bool Listen(const GSpecialAddress InAddress, std::uint16_t InPort = 0) = 0;
    virtual bool Listen(const GString InAddress, std::uint16_t InPort = 0) = 0;
    virtual bool Connect(const GString InAddress, std::uint16_t InPort = 0) = 0;
    virtual std::int64_t Read(char *Data, std::int64_t MaxSize) = 0;
    virtual std::int64_t Write(const char *Data, std::int64_t MaxSize) = 0;
    virtual GSocket *Accept() = 0;
public:
    int SetListenBacklogSize(int InSize)
    {
        ListenBacklogSize = InSize;
        return 0;
    }
protected:
    /** Indicates the type of socket this is */
    GSocketType SocketType;
    GSocketProtocolFamily ProtocolFamily;
    int ListenBacklogSize = 5;
};

