#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/Resource/RHISampler.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class ES31Sampler : public RHISampler
{
public:
    ES31Sampler() = delete;
    ES31Sampler(OpenGLDevice* Device, RHIFilter MinFilter = RHIFilter::NEAREST,
        RHIFilter MagFilter = RHIFilter::NEAREST,
        RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
        RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
        RHIAddressMode AddressModeW = RHIAddressMode::REPEAT);
    ~ES31Sampler();
    GLuint GetHandle();
    void BindTextureUnit(int Unit);
private:
    OpenGLDevice* Device;
    GLuint Handle;
};
