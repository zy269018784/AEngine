#pragma once
#include "Vulkan.h"
#include "RHIObjects/Resource/RHISampler.h"
#include "VulkanObjects/Device/VulkanDevice.h"
class VulkanSampler : public RHISampler
{
public:
	VulkanSampler();
	VulkanSampler(VulkanDevice* Device, RHIFilter MinFilter = RHIFilter::NEAREST,
				  RHIFilter MagFilter = RHIFilter::NEAREST,
				  RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
				  RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
				  RHIAddressMode AddressModeW = RHIAddressMode::REPEAT);
	~VulkanSampler();
	 VkSampler GetHandle();

	VkSampler Handle;
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult CreateSampler(const VkSamplerCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void  DestroySampler(const VkAllocationCallbacks* Allocator);
private:
	VulkanDevice* Device;
};

