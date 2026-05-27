#include "RHI/RHIObjects/SwapChain/RHISwapChain.h"

RHISwapChain::RHISwapChain(RHIDevice *InDevice, RHISurface *InSurface)
    : Device(InDevice), Surface(InSurface)
{

}

RHISwapChain::~RHISwapChain() {

}

std::uint32_t RHISwapChain::GetWidth() const
{
    return Width;
}

std::uint32_t RHISwapChain::GetHeight() const
{
    return Height;
}