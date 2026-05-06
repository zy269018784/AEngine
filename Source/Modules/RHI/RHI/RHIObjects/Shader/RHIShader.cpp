#include "RHI/RHIObjects/Shader/RHIShader.h"
#include "VulkanRHI/VulkanObjects/RenderPass/VulkanRenderPass.h"


RHIShader::RHIShader(RHIShaderType InType, std::uint32_t* InCode, size_t InSize)
	: Type(InType), Code(InCode), Size(InSize)
	
{

}

RHIShader::~RHIShader()
{

}

std::uint32_t* RHIShader::GetCode() const
{
	return Code;
}

size_t RHIShader::GetSize() const
{
	return Size;
}

RHIShaderType RHIShader::GetType() const
{
	return Type;
}
