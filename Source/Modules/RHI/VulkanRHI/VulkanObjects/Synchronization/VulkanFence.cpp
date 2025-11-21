#include "VulkanObjects/Synchronization/VulkanFence.h"

#include <stdexcept>
#include <iostream>
VulkanFence::VulkanFence(VulkanDevice* InDevice)
{
	Device = InDevice;
	Handle = VK_NULL_HANDLE;
}

VulkanFence::~VulkanFence()
{
	DestroyFence(nullptr);
}

VkFence VulkanFence::GetHandle()
{
	return Handle;
}

/*
	创建Fence, 初始为unsignaled状态.
*/
VkResult VulkanFence::Create(bool Signaled)
{
	VkFenceCreateInfo CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	CreateInfo.flags = 0;
	if (Signaled)
		CreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	VkResult Result = CreateFence(&CreateInfo, nullptr);
	if (VK_SUCCESS != Result)
	{
		std::cerr << "Failed to create fence object!" << std::endl;
		//throw std::runtime_error("Failed to create fence object!");
	}
	return Result;
}

VkResult VulkanFence::Wait()
{
	VkResult Result = WaitForFences(1, &Handle, VK_TRUE, UINT64_MAX);
	return Result;
}

VkResult VulkanFence::Reset()
{
	VkResult Result = ResetFences(1, &Handle);
	return Result;
}