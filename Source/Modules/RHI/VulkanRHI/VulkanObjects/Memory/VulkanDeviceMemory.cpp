#include "VulkanObjects/Memory/VulkanDeviceMemory.h"
#include <iostream>
VulkanDeviceMemory::VulkanDeviceMemory(VulkanDevice* InDevice)
	: Device(InDevice)
{

}

VulkanDeviceMemory::~VulkanDeviceMemory()
{
	Device->FreeMemory(Handle, nullptr);
}

VkDeviceMemory VulkanDeviceMemory::GetHandle()
{
	return Handle;
}




