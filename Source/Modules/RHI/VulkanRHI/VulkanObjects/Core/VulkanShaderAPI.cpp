#include "VulkanObjects/Shader/VulkanShader.h"

VkResult VulkanShader::CreateShaderModule(const VkShaderModuleCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateShaderModule(CreateInfo, Allocator, &Handle);
}

void VulkanShader::DestroyShaderModule(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyShaderModule(Handle, Allocator);
}