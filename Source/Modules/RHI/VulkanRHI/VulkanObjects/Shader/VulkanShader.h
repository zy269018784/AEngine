#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "RHIObjects/Shader/RHIShader.h"

class VulkanShader : public RHIShader
{
public:
	VulkanShader(VulkanDevice *InDevice, RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~VulkanShader();
	VkShaderModule GetHandle();
private:
	/*
		Vulkan API Wrapper
	*/
	VkResult CreateShaderModule(const VkShaderModuleCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroyShaderModule(const VkAllocationCallbacks* Allocator);
private:
	VkShaderModule Handle;
	VulkanDevice* Device;
};