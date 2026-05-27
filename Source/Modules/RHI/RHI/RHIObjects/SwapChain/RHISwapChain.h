#pragma once
#include <cstdint>
#include "RHI/RHIObjects/Core/RHICore.h"
class RHISurface;
class RHIDevice;
class RHISwapChain
{
public:
    RHISwapChain() = default;
    RHISwapChain(RHIDevice *InDevice, RHISurface *InSurface);
    virtual ~RHISwapChain();
    std::uint32_t GetWidth() const;
    std::uint32_t GetHeight() const;
    void SetWidth(int InWidth);
    void SetHeight(int InHeight);
    RHIPixelFormat GetRHIPixelFormat() const;
    void SetRHIPixelFormat(RHIPixelFormat InFormat);
    void SetRHIPresentMode(RHIPresentMode InMode);
    RHIPresentMode GetRHIPresentMode() const;
    void SetRHIColorSpace(RHIColorSpace InColorSpace);
    RHIColorSpace GetRHIColorSpace() const;
#if 0
    void Resize(int InWidth, int InHeight);
#endif
protected:
    /*
        Surface
    */
    RHISurface *Surface = nullptr;
    /*
        设备
    */
    RHIDevice *Device = nullptr;

    std::uint32_t Width = 0;

    std::uint32_t Height = 0;

    RHIPixelFormat Format;
    RHIPresentMode PresentMode;
    RHIColorSpace ColorSpace;
};

