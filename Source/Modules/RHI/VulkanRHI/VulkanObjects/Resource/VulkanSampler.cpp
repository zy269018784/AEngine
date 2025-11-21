#include "VulkanObjects/Resource/VulkanSampler.h"
#include "VulkanObjects/Core/VulkanCore.h"
VulkanSampler::VulkanSampler()
{

}

VulkanSampler::VulkanSampler(VulkanDevice* InDevice, RHIFilter MinFilter,
	RHIFilter MagFilter,
	RHIAddressMode AddressModeU,
	RHIAddressMode AddressModeV,
	RHIAddressMode AddressModeW)
	: Device(InDevice)
{
	VkSamplerCreateInfo CreateInfo{ };
	CreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	CreateInfo.minFilter = ToVkFilter(MinFilter);
	CreateInfo.magFilter = ToVkFilter(MagFilter);
	CreateInfo.addressModeU = ToVkSamplerAddressMode(AddressModeU);
	CreateInfo.addressModeV = ToVkSamplerAddressMode(AddressModeV);
	CreateInfo.addressModeW = ToVkSamplerAddressMode(AddressModeW);
	CreateSampler(&CreateInfo, nullptr);
}

VulkanSampler::~VulkanSampler()
{
	DestroySampler(nullptr);
}

VkSampler VulkanSampler::GetHandle()
{
	return Handle;
}

