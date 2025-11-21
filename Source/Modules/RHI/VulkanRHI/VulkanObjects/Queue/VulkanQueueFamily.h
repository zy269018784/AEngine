#pragma once
#include <cstdint>
#include "Vulkan.h"
class VulkanDevice;
class VulkanQueueFamily
{
public:
	VulkanQueueFamily(std::uint32_t Index, std::uint32_t Count);
	std::uint32_t GetHandle();
	std::uint32_t GetQueueCount();
	void GetDeviceQueue(VulkanDevice *Device, std::uint32_t QueueIndex, VkQueue* Queue);
	void SetGraphics();
	void SetCompute();
	void SetTransfer();
	bool SupportGraphics();
	bool SupportCompute();
	bool SupportTransfer();
private:
	/*
		QueueFamilyIndex
	*/
	std::uint32_t Handle;
	std::uint32_t QueueCount;
	std::uint8_t  QueueFlag;
};