#include "Vulkan.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorPool.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorSetLayout.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <iostream>
#include <cstring>
#include <array>
enum {
	VK_DESCRIPTOR_TYPE_BEGIN_RANGE = VK_DESCRIPTOR_TYPE_SAMPLER,
	VK_DESCRIPTOR_TYPE_END_RANGE = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
	VK_DESCRIPTOR_TYPE_RANGE_SIZE = (VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT - VK_DESCRIPTOR_TYPE_SAMPLER + 1),
};


VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice* InDevice, VulkanDescriptorSetLayout* Layout, std::uint32_t MaxSetsAllocations)
	: Device(InDevice), Handle(VK_NULL_HANDLE)
{
	MaxDescriptorSets = Layout->GetLayouts().size();

	std::vector<VkDescriptorPoolSize> Types;
	
	Types.resize(VK_DESCRIPTOR_TYPE_RANGE_SIZE);

	for (std::uint32_t TypeIndex = VK_DESCRIPTOR_TYPE_BEGIN_RANGE; TypeIndex <= VK_DESCRIPTOR_TYPE_END_RANGE; ++TypeIndex)
	{
		VkDescriptorType DescriptorType = (VkDescriptorType)TypeIndex;
		std::uint32_t NumTypesUsed = Layout->GetTypesUsed(DescriptorType);
		if (NumTypesUsed > 0)
		{
			VkDescriptorPoolSize* Type = &Types.data()[TypeIndex];
			std::memset(Type, 0x0, sizeof(VkDescriptorPoolSize));
			Type->type = DescriptorType;
			Type->descriptorCount = NumTypesUsed * MaxSetsAllocations;
		}
	}

	VkDescriptorPoolCreateInfo PoolInfo;
	std::memset(&PoolInfo, 0x0, sizeof (VkDescriptorPoolCreateInfo));
	PoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	PoolInfo.poolSizeCount = Types.size();
	PoolInfo.pPoolSizes = Types.data();
	PoolInfo.maxSets = MaxDescriptorSets;

	CreateDescriptorPool(&PoolInfo, nullptr);
}

/*
	std::vector<VkBuffer> UBOs;
	std::vector<VkBuffer> SSBOs;
	std::vector<std::pair<VkSampler, VkImageView>> CombinedImageSamplers;
	std::vector<VkSampler>   Samplers;
	std::vector<VkImageView> SampledImages;
*/
VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice* InDevice, RHIShaderResourceBindings* SRB)
	: Device(InDevice)
{
	std::vector<RHIShaderResourceBinding>& bindings = SRB->GetBindings();
	std::uint32_t BindingSize = bindings.size();
	std::vector<VkDescriptorPoolSize> PoolSizes;
	std::uint32_t UniformBufferCount = 0;
	std::uint32_t StorageBufferCount = 0;
	std::uint32_t SamplerCount = 0;
	std::uint32_t SampledImageCount = 0;
	std::uint32_t CombinedImageSamplerCount = 0;
	std::uint32_t StorageImageCount = 0;
	
	for (const auto& binding : bindings) 
	{
		switch (binding.d.type) {
		case RHIShaderResourceBinding::Type::UniformBuffer:
			UniformBufferCount++;
			break;		
		case RHIShaderResourceBinding::Type::StorageBuffer:
			StorageBufferCount++;
			break;
		case RHIShaderResourceBinding::Type::Sampler:
			SamplerCount++;
			break;
		case RHIShaderResourceBinding::Type::SampledImage:
			SampledImageCount++;
			break;
		case RHIShaderResourceBinding::Type::CombinedImageSampler:
			CombinedImageSamplerCount++;
			break;
		case RHIShaderResourceBinding::Type::StorageImage:
			StorageImageCount++;
			break;
		}//switch
	}
	std::cout << "UniformBufferCount "			<< UniformBufferCount			<< std::endl;
	std::cout << "StorageBufferCount "			<< StorageBufferCount			<< std::endl;
	std::cout << "SamplerCount "				<< SamplerCount					<< std::endl;
	std::cout << "SampledImageCount "			<< SampledImageCount			<< std::endl;
	std::cout << "CombinedImageSamplerCount "	<< CombinedImageSamplerCount	<< std::endl;
	std::cout << "StorageImageCount "		    << StorageImageCount			<< std::endl;

	/*
		UBO
	*/
	if (UniformBufferCount > 0) 
	{
		VkDescriptorPoolSize poolSize{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, UniformBufferCount };
		PoolSizes.push_back(poolSize);
	}
	/*
		SSBO
	*/
	if (StorageBufferCount > 0) 
	{
		VkDescriptorPoolSize poolSize{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, StorageBufferCount };
		PoolSizes.push_back(poolSize);
	}

	/*
		Sampler
	*/
	if (SamplerCount > 0) {
		VkDescriptorPoolSize poolSize{ VK_DESCRIPTOR_TYPE_SAMPLER, SamplerCount };
		PoolSizes.push_back(poolSize);
	}

	/*
		Sampled Image Sampler
	*/
	if (SampledImageCount > 0)
	{
		VkDescriptorPoolSize poolSize{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, SampledImageCount };
		PoolSizes.push_back(poolSize);
	}

	/*
		Combined Image Sampler
	*/
	if (CombinedImageSamplerCount > 0)
	{
		VkDescriptorPoolSize poolSize{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, CombinedImageSamplerCount };
		PoolSizes.push_back(poolSize);
	}

	for (int i = 0; i < PoolSizes.size(); i++)
	{
		std::cout << "PoolSizes[i].descriptorCount  " << PoolSizes[i].descriptorCount << std::endl;
	}

	VkDescriptorPoolCreateInfo CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	CreateInfo.poolSizeCount = static_cast<uint32_t>(PoolSizes.size());
	CreateInfo.pPoolSizes = PoolSizes.data();
	CreateInfo.maxSets = BindingSize;
	CreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	std::cout << "BindingSize " << BindingSize << std::endl;
	VkResult ret = CreateDescriptorPool(&CreateInfo, nullptr);
	if (ret != VK_SUCCESS)
	{
		std::cout << "CreateDescriptorPool failed " << ret << std::endl;
		return;
	}
	std::cout << "CreateDescriptorPool ok" << std::endl;
}

VulkanDescriptorPool::~VulkanDescriptorPool()
{
	DestroyDescriptorPool(nullptr);
}

VkDescriptorPool VulkanDescriptorPool::GetHandle()
{
	return Handle;
}
