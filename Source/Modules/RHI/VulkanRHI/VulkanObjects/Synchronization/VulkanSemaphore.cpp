#include "VulkanObjects/Synchronization/VulkanSemaphore.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <stdexcept>
#include <iostream>
VulkanSemaphore::VulkanSemaphore(VulkanDevice* InDevice) 
	: Device(InDevice), Handle(VK_NULL_HANDLE)
{ 

}
 
VulkanSemaphore::~VulkanSemaphore()
{ 
	DestroySemaphore(nullptr);
}

VkSemaphore VulkanSemaphore::GetHandle()
{
	return Handle;
}

void VulkanSemaphore::Create(bool Signaled)
{
	VkSemaphoreCreateInfo CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO; 
	if (Signaled)
		CreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	if (CreateSemaphore(&CreateInfo, nullptr) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Semaphore objects!");
	}

	std::cout << "VulkanSemaphore::Create " << Handle << std::endl;
}