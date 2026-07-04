#include "GSocketSubsystem.h"

#include "Windows/GSocketSubsystemWindows.h"
#include "Windows/GSocketWindows.h"
#if OS_IS_WINDOWS
#include <GNetwork/GSockets/GSocket.h>
#include <GNetwork/GSockets/GSocketSubsystem.h>
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
}

GSocket* GSocketSubsystem::CreateGSocket(GSocketType InSocketType, GSocketProtocolFamily InSocketProtocol)
{
#if OS_IS_WINDOWS
    return new GSocketWindows(InSocketType, InSocketProtocol);
#endif
}
