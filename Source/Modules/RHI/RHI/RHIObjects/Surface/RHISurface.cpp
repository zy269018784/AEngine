#include "RHISurface.h"

RHISurface::RHISurface(std::uint32_t InWidth, std::uint32_t InHeight)
    : Width(InWidth), Height(InHeight)
{

}

RHISurface::~RHISurface() {

};

std::uint32_t RHISurface::GetWidth() const
{
    return Width;
}

std::uint32_t RHISurface::GetHeight() const
{
    return Height;
}

void RHISurface::SetWidth(std::uint32_t InWidth) {
    Width = InWidth;
}

void RHISurface::SetHeight(std::uint32_t InHeight) {
    Height = InHeight;
}

void RHISurface::SetRHIPixelFormat(RHIPixelFormat InFormat)
{
    Format = InFormat;
}

RHIPixelFormat RHISurface::GetRHIPixelFormat() const
{
    return Format;
}