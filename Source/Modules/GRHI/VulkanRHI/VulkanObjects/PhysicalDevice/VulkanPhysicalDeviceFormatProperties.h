#pragma once
#include "VulkanRHI/Vulkan.h"
#include <vector>

class VulkanPhysicalDevice;

class VulkanPhysicalDeviceFormatProperties
{
public:
    VulkanPhysicalDeviceFormatProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceFormatProperties();
    void Print(int Tabs);
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
    std::vector<VkFormatProperties>	FormatProperties;
};

