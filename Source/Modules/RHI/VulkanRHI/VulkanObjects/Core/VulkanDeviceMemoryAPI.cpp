#include "VulkanObjects/Memory/VulkanDeviceMemory.h"


VkResult VulkanDeviceMemory::AllocateMemory(const VkMemoryAllocateInfo* AllocateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->AllocateMemory(AllocateInfo, Allocator, &Handle);
}

void VulkanDeviceMemory::FreeMemory()
{
	Device->FreeMemory(Handle, nullptr);
}

VkResult VulkanDeviceMemory::MapMemory(VkDeviceSize Offset, VkDeviceSize Size, VkMemoryMapFlags Flags, void** Data)
{
	return Device->MapMemory(Handle, Offset, Size, Flags, Data);
}

void VulkanDeviceMemory::UnmapMemory()
{
	Device->UnmapMemory(Handle);
}









