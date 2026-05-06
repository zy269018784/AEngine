#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceFormatProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
#include <iostream>
VulkanPhysicalDeviceFormatProperties::VulkanPhysicalDeviceFormatProperties(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    FormatProperties.resize(static_cast<size_t>(RHIPixelFormat::PF_MAX_));
    for (uint32_t PixelFormatIndex = 0; PixelFormatIndex < FormatProperties.size(); PixelFormatIndex++)
    {
        PhysicalDevice->GetPhysicalDeviceFormatProperties(ToVkFormat(static_cast<RHIPixelFormat>(PixelFormatIndex)),
                &FormatProperties[PixelFormatIndex]);
        std::cout << "PixelFormat " << PixelFormatIndex << " ";
        if (FormatProperties[PixelFormatIndex].linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
        {
            std::cout << "linearTilingFeatures SAMPLED_IMAGE ";
        }
        if (FormatProperties[PixelFormatIndex].optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
        {
            std::cout << "optimalTilingFeatures SAMPLED_IMAGE ";
        }
        std::cout << std::endl;
    }
}

VulkanPhysicalDeviceFormatProperties::~VulkanPhysicalDeviceFormatProperties()
{

}

void VulkanPhysicalDeviceFormatProperties::Print(int Tabs)
{

}