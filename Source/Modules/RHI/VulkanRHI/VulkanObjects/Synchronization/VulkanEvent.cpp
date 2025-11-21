#include <VulkanObjects/Synchronization/VulkanEvent.h>
#include "VulkanObjects/Device/VulkanDevice.h"
#include <stdexcept>
#include <iostream>
VulkanEvent::VulkanEvent(VulkanDevice* InDevice)
	: Device(InDevice), Handle(VK_NULL_HANDLE)
{
	if (Device)
	{
		VkEventCreateInfo CreateInfo{};
		CreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
		CreateInfo.flags = VK_EVENT_CREATE_DEVICE_ONLY_BIT;
		if (Device->CreateEvent(&CreateInfo, nullptr, &Handle) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create fence object!");
		}
	}
}

VulkanEvent::~VulkanEvent()
{
	if (Device)
	{
		Device->DestroyEvent(Handle, nullptr);
	}
}

VkEvent VulkanEvent::GetHandle()
{
	return Handle;
}