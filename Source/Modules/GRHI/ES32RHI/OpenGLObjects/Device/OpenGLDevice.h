#pragma once
#include "RHI/RHIObjects/Device/RHIDevice.h"
class OpenGLDevice : public RHIDevice
{
public:
    OpenGLDevice();
    virtual ~OpenGLDevice();
};