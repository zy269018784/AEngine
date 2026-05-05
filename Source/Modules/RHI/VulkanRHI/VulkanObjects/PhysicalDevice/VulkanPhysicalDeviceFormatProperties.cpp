#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceFormatProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
VulkanPhysicalDeviceFormatProperties::VulkanPhysicalDeviceFormatProperties(VulkanPhysicalDevice *InPhysicalDevice)
{
    FormatProperties.resize(static_cast<size_t>(RHIPixelFormat::PF_MAX_));
    for (uint32_t PixelFormatIndex = 0; PixelFormatIndex < FormatProperties.size(); PixelFormatIndex++)
    {
        PhysicalDevice->GetPhysicalDeviceFormatProperties(ToVkFormat(static_cast<RHIPixelFormat>(PixelFormatIndex)),
                &FormatProperties[PixelFormatIndex]);
    }
}

VulkanPhysicalDeviceFormatProperties::~VulkanPhysicalDeviceFormatProperties()
{

}

void VulkanPhysicalDeviceFormatProperties::Print(int Tabs)
{

}