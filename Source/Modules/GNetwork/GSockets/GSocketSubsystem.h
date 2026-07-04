#pragma once
#include <GCore/GExport.h>
#include <GSockets/GSocket.h>
class GEXPORT GSocketSubsystem
{
public:
    GSocketSubsystem();
    virtual ~GSocketSubsystem();
public:
    static GSocketSubsystem* CreateGSocketSubsystem();
    static GSocket* CreateGSocket(GSocketType InSocketType, GSocketProtocolFamily InSocketProtocol);
public:
    virtual bool Init() = 0;
    virtual void Shutdown() = 0;
};

