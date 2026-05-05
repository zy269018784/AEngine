#pragma once
#include "VulkanRHI/Vulkan.h"
class VulkanPhysicalDevice;

class VulkanPhysicalDeviceDisplayProperties
{
public:
    VulkanPhysicalDeviceDisplayProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceDisplayProperties();
    void Print(int Tabs);
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
};


