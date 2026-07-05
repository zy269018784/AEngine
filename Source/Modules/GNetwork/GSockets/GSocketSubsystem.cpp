#include "GSocketSubsystem.h"
#include <GNetwork/GSockets/GSocket.h>
#include <GNetwork/GSockets/GSocketSubsystem.h>

#if OS_IS_WINDOWS
    #include <GNetwork/GSockets/Windows/GSocketSubsystemWindows.h>
    #include <GNetwork/GSockets/Windows/GSocketWindows.h>
#endif

#if OS_IS_LINUX
    #include <GNetwork/GSockets/Unix/GSocketSubsystemUnix.h>
    #include <GNetwork/GSockets/Unix/GSocketUnix.h>
#endif

GSocketSubsystem::GSocketSubsystem()
{

}

GSocketSubsystem::~GSocketSubsystem()
{

}

GSocketSubsystem* GSocketSubsystem::CreateGSocketSubsystem()
{
#if OS_IS_WINDOWS
    return new GSocketSubsystemWindows();
#endif

#if OS_IS_LINUX
    return new GSocketSubsystemUnix();
#endif
}

GSocket* GSocketSubsystem::CreateGSocket(GSocketType InSocketType, GSocketProtocolFamily InSocketProtocol)
{
#if OS_IS_WINDOWS
    return new GSocketWindows(InSocketType, InSocketProtocol);
#endif

#if OS_IS_LINUX
    return new GSocketUnix(InSocketType, InSocketProtocol);
#endif
}
