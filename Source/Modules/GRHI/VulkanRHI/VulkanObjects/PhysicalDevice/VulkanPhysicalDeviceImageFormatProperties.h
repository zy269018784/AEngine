#pragma once
#include "VulkanRHI/Vulkan.h"
class VulkanPhysicalDevice;

class VulkanPhysicalDeviceImageFormatProperties
{
public:
    VulkanPhysicalDeviceImageFormatProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceImageFormatProperties();
    void Print(int Tabs);
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
};

