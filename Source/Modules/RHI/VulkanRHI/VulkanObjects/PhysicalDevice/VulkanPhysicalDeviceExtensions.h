#pragma once
#include "VulkanRHI/Vulkan.h"
#include <vector>

class VulkanPhysicalDevice;

class VulkanPhysicalDeviceExtensions
{
public:
    VulkanPhysicalDeviceExtensions(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceExtensions();
    void Print(int Tabs);
    bool CheckExtensionSupport(std::vector<const char*> RequiredExtensions);
private:
    VulkanPhysicalDevice *PhysicalDevice;
    std::vector<VkExtensionProperties>		Extensions;
};

