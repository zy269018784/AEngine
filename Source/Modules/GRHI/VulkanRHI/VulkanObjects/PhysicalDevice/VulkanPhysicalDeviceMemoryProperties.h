#pragma once
#include "VulkanRHI/Vulkan.h"
#include <cstdint>

class VulkanPhysicalDevice;
class VulkanPhysicalDeviceMemoryProperties
{
public:
    VulkanPhysicalDeviceMemoryProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceMemoryProperties();
    void Print(int Tabs);
    std::uint32_t FindMemoryType(std::uint32_t MemoryTypeFilter, VkMemoryPropertyFlags InMemoryProperties);
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
    VkPhysicalDeviceMemoryProperties		MemoryProperties;
    VkPhysicalDeviceMemoryProperties2       MemoryProperties2;
};

