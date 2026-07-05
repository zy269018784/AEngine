#include <GSockets/Windows/GSocketWindows.h>
#include <ws2tcpip.h>

GSocketWindows::GSocketWindows()
{

}

GSocketWindows::~GSocketWindows()
{

}

int GSocketWindows::Create()
{
    int Ret = 0;
    Handle = socket(WindowsAddressFamily, WindowsSocketType, WindowsProtocol);
    if (Handle == INVALID_SOCKET)
        Ret = -1;
    return Ret;
}

void GSocketWindows::Close()
{
    closesocket(Handle);
}

bool GSocketWindows::Bind(const GSpecialAddress InAddress, std::uint16_t InPort)
{
    SockAddress.sin_family = WindowsAddressFamily;
    SockAddress.sin_addr.s_addr = ToWindowsSpecialAddress(InAddress);  // 0.0.0.0
    SockAddress.sin_port = htons(InPort);

    SockAddress.sin_family = AF_INET;
    SockAddress.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    SockAddress.sin_port = htons(8888);


    if (bind(Handle, (struct sockaddr*)&SockAddress, sizeof(SockAddress)) == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

bool GSocketWindows::Bind(const GString InAddress, std::uint16_t InPort)
{
    SockAddress.sin_family = WindowsAddressFamily;
    SockAddress.sin_port = htons(InPort);

    if (inet_pton(AF_INET, InAddress.ConstStr(), &SockAddress.sin_addr) != 1)
    {
        std::cerr << "invaild ip address" << std::endl;
        return false;
    }

    if (bind(Handle, (struct sockaddr*)&SockAddress, sizeof(SockAddress)) == SOCKET_ERROR)
    {
        return false;
    }

    return true;
}

bool GSocketWindows::Listen()
{
    if (listen(Handle, ListenBacklogSize) == SOCKET_ERROR)
    {
        return false;
    }

    return true;
}


bool GSocketWindows::Listen(const GSpecialAddress InAddress, std::uint16_t InPort)
{
    Bind(InAddress, InPort);

    return Listen();
}

bool GSocketWindows::Listen(const GString InAddress, std::uint16_t InPort)
{
    Bind(InAddress, InPort);

    return Listen();
}

bool GSocketWindows::Connect(const GString InAddress, std::uint16_t InPort)
{
    struct sockaddr_in DstSockAddress;
    DstSockAddress.sin_family = WindowsAddressFamily;
    DstSockAddress.sin_port = htons(InPort);
    if (inet_pton(AF_INET, InAddress.ConstStr(), &DstSockAddress.sin_addr) != 1)
    {
        std::cerr << "invaild ip address" << std::endl;
        return false;
    }

    if (connect(Handle, (struct sockaddr*)&DstSockAddress, sizeof(DstSockAddress)) == SOCKET_ERROR)
    {
        closesocket(Handle);
        return false;
    }

    return true;
}

std::int64_t GSocketWindows::Read(char *Data, std::int64_t MaxSize)
{
    return recv(Handle, Data, MaxSize, 0);
}

std::int64_t GSocketWindows::Write(const char *Data, std::int64_t MaxSize)
{
    return send(Handle, Data, MaxSize, 0);
}

GSocket *GSocketWindows::Accept()
{
    GSocketWindows *Socket = nullptr;

    struct sockaddr_in ClientSockAddress;
    int AddrLen = sizeof (ClientSockAddress);
    SOCKET ClientHandle =  accept(Handle, (struct sockaddr*)&ClientSockAddress, &AddrLen);
    if (ClientHandle != INVALID_SOCKET) {
        // 输出客户端 IP 和端口
        std::cout << "client " << std::endl;
        std::cout << "ip: " << inet_ntoa(ClientSockAddress.sin_addr) << std::endl;
        std::cout << "port: " << ntohs(ClientSockAddress.sin_port) << std::endl;

        // 或者在一行输出
        std::cout << "client: " << inet_ntoa(ClientSockAddress.sin_addr)
                  << ":" << ntohs(ClientSockAddress.sin_port) << std::endl;
    }
    if (INVALID_SOCKET == ClientHandle)
    {
        return nullptr;
    }
    Socket = new GSocketWindows(SocketType, ProtocolFamily, ClientHandle);
    Socket->SetSockAddress(ClientSockAddress);
    return Socket;
}

void GSocketWindows::SetSockAddress(struct sockaddr_in InSockAddress)
{
    SockAddress = InSockAddress;
}