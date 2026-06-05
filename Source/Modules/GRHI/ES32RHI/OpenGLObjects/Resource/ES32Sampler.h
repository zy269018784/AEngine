#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/Resource/RHISampler.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
class ES32Sampler : public OpenGLSampler
{
public:
    ES32Sampler() = delete;
    ES32Sampler(OpenGLDevice* Device, RHIFilter MinFilter = RHIFilter::NEAREST,
        RHIFilter MagFilter = RHIFilter::NEAREST,
        RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
        RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
        RHIAddressMode AddressModeW = RHIAddressMode::REPEAT);
    ~ES32Sampler();
    virtual void BindTextureUnit(int Unit) override final;
};
