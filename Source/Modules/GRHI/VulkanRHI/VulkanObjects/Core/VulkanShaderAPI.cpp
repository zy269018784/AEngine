#include "VulkanRHI/VulkanObjects/Shader/VulkanShader.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"

VkResult VulkanShader::CreateShaderModule(const VkShaderModuleCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateShaderModule(CreateInfo, Allocator, &Handle);
}

void VulkanShader::DestroyShaderModule(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyShaderModule(Handle, Allocator);
}