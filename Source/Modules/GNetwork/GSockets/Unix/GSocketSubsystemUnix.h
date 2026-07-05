#pragma once
#include <GNetwork/GSockets/GSocketSubsystem.h>

class GEXPORT GSocketSubsystemUnix : public GSocketSubsystem
{
public:
    GSocketSubsystemUnix();
    virtual ~GSocketSubsystemUnix();
    virtual bool Init() override final;
    virtual void Shutdown()  override final;
};

