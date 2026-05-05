#pragma once
#include "VulkanRHI/Vulkan.h"
#include <cstdint>
#include <vector>

class VulkanPhysicalDevice;
class VulkanQueueFamily;
class VulkanPhysicalDeviceQueueFamilyProperties
{
public:
    VulkanPhysicalDeviceQueueFamilyProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceQueueFamilyProperties();
    void Print(int Tabs);
    std::uint32_t GetQueueFamilyCount() const;
    std::vector<VulkanQueueFamily *> CreateQueueFamilies() const;
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
    /*
        物理设备上所有Queue Family的Properties
    */
    std::vector<VkQueueFamilyProperties>	QueueFamilyProperties;
};
