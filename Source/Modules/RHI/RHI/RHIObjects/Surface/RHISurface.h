#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <cstdint>

#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceFormatProperties.h"

class RHIEXPORT RHISurface
{
public:
    RHISurface() = default;
    RHISurface(std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~RHISurface();
public:
    void SetWidth(std::uint32_t InWidth);
    void SetHeight(std::uint32_t InHeight);
    std::uint32_t GetWidth() const;
    std::uint32_t GetHeight() const;
    void SetRHIPixelFormat(RHIPixelFormat InFormat);
    RHIPixelFormat GetRHIPixelFormat() const;
protected:
    std::uint32_t Width = 0;
    std::uint32_t Height = 0;
    RHIPixelFormat Format;
};


