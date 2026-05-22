#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/Resource/RHISampler.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class ES20Sampler : public RHISampler
{
public:
    ES20Sampler() = delete;
    ES20Sampler(OpenGLDevice* Device, RHIFilter MinFilter = RHIFilter::NEAREST,
        RHIFilter MagFilter = RHIFilter::NEAREST,
        RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
        RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
        RHIAddressMode AddressModeW = RHIAddressMode::REPEAT);
    ~ES20Sampler();
    GLuint GetHandle();
    void BindTextureUnit(int Unit);
private:
    OpenGLDevice* Device;
    GLuint Handle;
};
