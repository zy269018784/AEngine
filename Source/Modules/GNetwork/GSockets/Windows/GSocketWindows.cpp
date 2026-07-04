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

bool GSocketWindows::Bind(const GSpecialAddress InAddress, std::uint16_t InPort)
{
    SockAddress.sin_family = WindowsAddressFamily;
    SockAddress.sin_addr.s_addr = ToWindowsSpecialAddress(InAddress);  // 0.0.0.0
    SockAddress.sin_port = htons(InPort);

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
