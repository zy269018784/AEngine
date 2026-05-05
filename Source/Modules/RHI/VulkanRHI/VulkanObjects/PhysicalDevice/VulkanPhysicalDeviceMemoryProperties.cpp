#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceMemoryProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"

VulkanPhysicalDeviceMemoryProperties::VulkanPhysicalDeviceMemoryProperties(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    PhysicalDevice->GetPhysicalDeviceMemoryProperties(&MemoryProperties);
}

VulkanPhysicalDeviceMemoryProperties::~VulkanPhysicalDeviceMemoryProperties()
{

}

void VulkanPhysicalDeviceMemoryProperties::Print(int Tabs)
{

}

std::uint32_t VulkanPhysicalDeviceMemoryProperties::FindMemoryType(std::uint32_t MemoryTypeFilter, VkMemoryPropertyFlags InMemoryProperties)
{
    std::uint32_t MemoryTypeIndex = -1;
    for (MemoryTypeIndex = 0; MemoryTypeIndex < MemoryProperties.memoryTypeCount; MemoryTypeIndex++)
    {
        if ((MemoryTypeFilter & (1 << MemoryTypeIndex)) && ((MemoryProperties.memoryTypes[MemoryTypeIndex].propertyFlags & InMemoryProperties) == InMemoryProperties))
        {
            break;
        }
    }
    return MemoryTypeIndex;
}








