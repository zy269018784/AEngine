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

void RHISwapChain::SetWidth(int InWidth)
{
    Width = InWidth;
}

void RHISwapChain::SetHeight(int InHeight)
{
    Height = InHeight;
}
#if 0
void RHISwapChain::Resize(int InWidth, int InHeight)
{
    Width = InWidth;
    Height = InHeight;
}
#endif

RHIPixelFormat RHISwapChain::GetRHIPixelFormat() const
{
    return Format;
}

void RHISwapChain::SetRHIPixelFormat(RHIPixelFormat InFormat)
{
    Format = InFormat;
}