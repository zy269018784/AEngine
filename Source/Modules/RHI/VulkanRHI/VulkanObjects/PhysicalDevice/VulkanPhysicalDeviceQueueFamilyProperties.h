#pragma once
#include "VulkanRHI/Vulkan.h"
class VulkanPhysicalDevice;
class VulkanPhysicalDeviceQueueFamilyProperties
{
public:
    VulkanPhysicalDeviceQueueFamilyProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceQueueFamilyProperties();
    void Print(int Tabs);
    std::uint32_t GetQueueFamilyCount() const;
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
    /*
        物理设备上所有Queue Family的Properties
    */
    std::vector<VkQueueFamilyProperties>	QueueFamilyProperties;
};
