#pragma once
#include <cstdint>

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
};

