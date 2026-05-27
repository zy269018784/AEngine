#include "RHI/RHIObjects/SwapChain/RHISwapChain.h"

#include "RHI/RHIObjects/Surface/RHISurface.h"

RHISwapChain::RHISwapChain(RHIDevice *InDevice, RHISurface *InSurface)
    : Device(InDevice), Surface(InSurface), Width(InSurface->GetWidth()), Height(InSurface->GetHeight())
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