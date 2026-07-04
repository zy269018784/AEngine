#include "GSocketSubsystemWindows.h"
#include <winsock2.h>

GSocketSubsystemWindows::GSocketSubsystemWindows()
{

}

GSocketSubsystemWindows::~GSocketSubsystemWindows()
{

}

bool GSocketSubsystemWindows::Init()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return false;
    return true;
}

void GSocketSubsystemWindows::Shutdown()
{
    WSACleanup();
}