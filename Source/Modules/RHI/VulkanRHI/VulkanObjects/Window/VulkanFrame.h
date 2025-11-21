#pragma once
#include "VulkanObjects/Synchronization/VulkanFence.h"
#include "VulkanObjects/Synchronization/VulkanSemaphore.h"
class VulkanDevice;
class VulkanFrame
{
public:
	VulkanFrame(VulkanDevice *InDevice, bool InSignaled = false);
	~VulkanFrame();

public:
	VulkanFence*		ImageFence = nullptr;
	VulkanSemaphore*	ImageAvailableSemaphore = nullptr;
	VulkanSemaphore*	ImageDrawFinishedSemaphore = nullptr;
private:
	VulkanDevice*		Device = nullptr;
};