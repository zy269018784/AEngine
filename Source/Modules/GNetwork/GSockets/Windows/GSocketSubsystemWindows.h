#pragma once
#include <GNetwork/GSockets/GSocketSubsystem.h>

class GEXPORT GSocketSubsystemWindows : public GSocketSubsystem
{
public:
    GSocketSubsystemWindows();
    virtual ~GSocketSubsystemWindows();
    virtual bool Init() override final;
    virtual void Shutdown()  override final;
};

