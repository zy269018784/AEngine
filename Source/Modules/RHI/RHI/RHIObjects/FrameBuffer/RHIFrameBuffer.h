#pragma once
#include "RHI/RHIExport.h"
class RHIEXPORT RHIFrameBuffer
{
public:
    virtual void Bind() const = 0;
};
