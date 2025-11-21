#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorSetLayout.h"
#include "VulkanObjects/Shader/VulkanShaderResourceBindings.h"
#include <map>
#include <iostream>
#include <cstdint>

static VkShaderStageFlagBits ToVkShaderStageFlags(RHIShaderResourceBinding::StageFlags Flag)
{
	VkShaderStageFlagBits VkFlag;
	switch (Flag)
	{
	case RHIShaderResourceBinding::StageFlags::VertexStage:
		VkFlag = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationControlStage:
		VkFlag = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationEvaluationStage:
		VkFlag = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::FragmentStage:
		VkFlag = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::ComputeStage:
		VkFlag = VK_SHADER_STAGE_COMPUTE_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::GeometryStage:
		VkFlag = VK_SHADER_STAGE_GEOMETRY_BIT;
		break;
	default:
		break;
	}

	return VkFlag;
}


VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanDevice* InDevice) 
	: Device(InDevice), Handle(VK_NULL_HANDLE)
{

}

VkDescriptorType ToVulkanDescriptorType(RHIShaderResourceBinding::Type Type)
{
	VkDescriptorType DescriptorType;
	switch (Type)
	{
	case RHIShaderResourceBinding::Type::UniformBuffer:
		DescriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		break;
	case RHIShaderResourceBinding::Type::StorageBuffer:
		DescriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		break;
	case RHIShaderResourceBinding::Type::Sampler:
		DescriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
		break;
	case RHIShaderResourceBinding::Type::SampledImage:
		DescriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		break;	
	case RHIShaderResourceBinding::Type::CombinedImageSampler:
		DescriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		break;
	case RHIShaderResourceBinding::Type::StorageImage:
		DescriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		break;
	default:
		break;
	}
	return DescriptorType;
}

/*
	buggy fix
*/
VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanDevice* InDevice, RHIShaderResourceBindings* SRB)
	: Device(InDevice)
{
	std::vector<RHIShaderResourceBinding>& Bindings = SRB->GetBindings();
	std::uint32_t BindingSize = Bindings.size();

	std::vector<VkDescriptorSetLayoutBinding> DescriptorSetLayoutBindings;
	for (const auto& b : Bindings)
	{
		VkDescriptorSetLayoutBinding DescriptorSetLayoutBinding = {};
		DescriptorSetLayoutBinding.binding = b.d.binding;
		DescriptorSetLayoutBinding.descriptorType = ToVulkanDescriptorType(b.d.type);
		DescriptorSetLayoutBinding.descriptorCount = 1;
		DescriptorSetLayoutBinding.stageFlags = ToVkShaderStageFlags(b.d.stage);
		DescriptorSetLayoutBindings.emplace_back(DescriptorSetLayoutBinding);
	}

	VkDescriptorSetLayoutCreateInfo descSetLayoutInfo{};
	descSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descSetLayoutInfo.bindingCount = static_cast<uint32_t>(DescriptorSetLayoutBindings.size());
	descSetLayoutInfo.pBindings = DescriptorSetLayoutBindings.data();

	VkResult ret = CreateDescriptorSetLayout(&descSetLayoutInfo, nullptr);
	if (ret != VK_SUCCESS) 
	{
		std::cout << "CreateDescriptorSetLayout failed " << ret << std::endl;
		return;
	}
	std::cout << "CreateDescriptorSetLayout ok " << Handle << std::endl;
}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
{
	std::cout << "~VulkanDescriptorSetLayout() " << Handle << std::endl;
	DestroyDescriptorSetLayout(nullptr);
}

VkDescriptorSetLayout VulkanDescriptorSetLayout::GetHandle() const
{
	return Handle;
}

const std::vector<VulkanDescriptorSetLayoutBinding>& VulkanDescriptorSetLayout::GetLayouts() const
{
	return SetLayouts;
}

std::uint32_t VulkanDescriptorSetLayout::GetTypesUsed(VkDescriptorType Type) 
{
	if (LayoutTypes.find(Type) != LayoutTypes.end())
	{
		return LayoutTypes[Type];
	}
	else
	{
		return 0;
	}
}

VkResult VulkanDescriptorSetLayout::CreateDescriptorSetLayout(VkDescriptorSetLayoutCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateDescriptorSetLayout(CreateInfo, Allocator, &Handle);
}

void VulkanDescriptorSetLayout::DestroyDescriptorSetLayout(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyDescriptorSetLayout(Handle, Allocator);
}