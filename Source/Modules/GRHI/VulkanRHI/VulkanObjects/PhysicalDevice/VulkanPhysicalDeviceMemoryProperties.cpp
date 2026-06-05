#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceMemoryProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <iostream>

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
	std::cout << "\t\tMemory Properties " << std::endl;

	std::cout
		<< "\t\t\tMemory Type Count " << MemoryProperties.memoryTypeCount << " "
		<< std::endl;
	std::cout
		<< "\t\t\t\t" << "Memory Type Index"  << "\t" << "Heap Index " << "\t"
		<< "\t\t\t\t" << "Property Flags "  << "\n";
	for (uint32_t i = 0; i < MemoryProperties.memoryTypeCount; i++)
	{

		std::cout
			<< "\t\t\t\t" << "[" << i << "]"  << "\t\t" << MemoryProperties.memoryTypes[i].heapIndex << "\t"
			<< "\t\t\t\t" << " " << MemoryProperties.memoryTypes[i].propertyFlags << " ";


		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_HOST_CACHED_BIT" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_PROTECTED_BIT" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD)
		{
			std::cout << "VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD)
		{
			std::cout << "VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD" << "\t";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV)
		{
			std::cout << "VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV" << "\t";
		}

		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			//HostVisibleIndex = i;

			std::cout << "\t\t\t\tHostVisibleIndex = Memory Type Index " << i << " ";
		}

		std::cout << std::endl;
	}

	std::cout
		<< "\t\t\tMemory Heap Count " << MemoryProperties.memoryHeapCount << " "
		<< std::endl;
	for (uint32_t i = 0; i < MemoryProperties.memoryHeapCount; i++)
	{
		std::cout
			<< "\t\t\t\tSize " << MemoryProperties.memoryHeaps[i].size << " "
			<< "\t\t\t\tFlags " << MemoryProperties.memoryHeaps[i].flags << " "
			<< std::endl;
	}
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








