#include "VulkanRHI/VulkanObjects/Shader/VulkanShader.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
VulkanShader::VulkanShader(VulkanDevice* InDevice, RHIShaderType Type, std::uint32_t* CodePtr1, size_t CodeSize1)
	:  Device(InDevice), RHIShader(Type, CodePtr1, CodeSize1)
{
	VkShaderModuleCreateInfo CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.codeSize = GetSize();
	CreateInfo.pCode = GetCode();
	CreateShaderModule(&CreateInfo, nullptr);
}

VulkanShader::~VulkanShader()
{
	DestroyShaderModule(nullptr);
}

VkShaderModule VulkanShader::GetHandle()
{
	return Handle;
}
