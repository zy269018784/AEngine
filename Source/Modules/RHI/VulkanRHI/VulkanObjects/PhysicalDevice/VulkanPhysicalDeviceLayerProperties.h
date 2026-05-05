#pragma once
#include "VulkanRHI/Vulkan.h"
#include <vector>

class VulkanPhysicalDevice;

class VulkanPhysicalDeviceLayerProperties
{
public:
    VulkanPhysicalDeviceLayerProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceLayerProperties();
    void Print(int Tabs);
public:
    VulkanPhysicalDevice *PhysicalDevice;
    std::vector<VkLayerProperties>			LayerProperties;
};

