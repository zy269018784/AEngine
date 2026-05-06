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
        std::cout << "linearTilingFeatures ";
        if (FormatProperties[PixelFormatIndex].linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
        {
            std::cout << "SAMPLED_IMAGE ";
        }
        if (FormatProperties[PixelFormatIndex].linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
        {
            std::cout << "STORAGE_IMAGE ";
        }
        std::cout << "optimalTilingFeatures ";
        if (FormatProperties[PixelFormatIndex].optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
        {
            std::cout << "SAMPLED_IMAGE ";
        }
        if (FormatProperties[PixelFormatIndex].optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
        {
            std::cout << "STORAGE_IMAGE ";
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