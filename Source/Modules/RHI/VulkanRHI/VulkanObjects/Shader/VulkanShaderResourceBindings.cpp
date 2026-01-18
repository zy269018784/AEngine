#include "VulkanObjects/Shader/VulkanShaderResourceBindings.h"
#include "VulkanObjects/Resource/VulkanBuffer.h"
#include "VulkanObjects/Resource/VulkanSampler.h"
#include "VulkanObjects/Resource/VulkanImage.h"
#include <VulkanObjects/Resource/VulkanImageView.h>
#include <VulkanObjects/Texture/VulkanTexture.h>
#include <cstring>
#include <map>
#include <iostream>

VulkanShaderResourceBindings::VulkanShaderResourceBindings(VulkanDevice* InDevice)
	: RHIShaderResourceBindings(), Device(InDevice), DescriptorPool(nullptr), DescriptorSetLayout(nullptr), DescriptorSet(nullptr)
{

}

VulkanShaderResourceBindings::~VulkanShaderResourceBindings()
{
	delete DescriptorSetLayout;
	delete DescriptorSet;
	delete DescriptorPool;
}

void VulkanShaderResourceBindings::Create()
{
	/*
		创建描述符池
	*/
	CreateDescriptorPool();

	/*
		创建描述符集合布局
	*/
	CreateDescriptorSetLayout();

	/*
		创建描述符集合
	*/
	CreateDescriptorSets();
	
	/*
		更新描述符集合
	*/
	UpdateDescriptorSets();
}

VulkanDescriptorSet* VulkanShaderResourceBindings::GetDescriptorSet()
{
	return DescriptorSet;
}

VulkanDescriptorSetLayout* VulkanShaderResourceBindings::GetDescriptorSetLayout()
{
	return DescriptorSetLayout;
}

void VulkanShaderResourceBindings::CreateDescriptorPool()
{
	DescriptorPool = new VulkanDescriptorPool(Device, this);
}

void VulkanShaderResourceBindings::CreateDescriptorSetLayout()
{
	DescriptorSetLayout = new VulkanDescriptorSetLayout(Device, this);
}

void VulkanShaderResourceBindings::CreateDescriptorSets()
{
	DescriptorSet = new VulkanDescriptorSet(Device, DescriptorPool, DescriptorSetLayout);
}

/*
	支持
	VK_DESCRIPTOR_TYPE_SAMPLER
	VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE3
	VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
	VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
	VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
	VK_DESCRIPTOR_TYPE_STORAGE_IMAGE
*/
void VulkanShaderResourceBindings::UpdateDescriptorSets()
{
	std::vector<VkWriteDescriptorSet> WriteDescriptorSets;
	/*
		UBO
	*/
	std::vector<VkDescriptorBufferInfo> UBODescriptorBufferInfos;

	/*
		SSBO
	*/
	std::vector<VkDescriptorBufferInfo> SSBODescriptorBufferInfos;

	/*
		Samplers
	*/
	std::vector<VkDescriptorImageInfo> SamplersDescriptorImageInfos;

	/*
		Sampled Images
	*/
	std::vector<VkDescriptorImageInfo> SampledImagesDescriptorImageInfos;

	/*
		Combined Image Samplers
	*/
	std::vector<VkDescriptorImageInfo> CombinedImageSamplersDescriptorImageInfos;

	/*
		Storage Images
	*/
	std::vector<VkDescriptorImageInfo> StorageImageDescriptorImageInfos;

	for (int i = 0; i < Bindings.size(); i++)
	{
		const RHIShaderResourceBinding::Type  BindingType = Bindings[i].d.type;
		int Binding = Bindings[i].d.binding;
		if (BindingType == RHIShaderResourceBinding::Type::UniformBuffer)
		{
			VkBuffer Handle = ((VulkanBuffer*)Bindings[i].d.u.ubuf.buf)->GetHandle();

			VkDescriptorBufferInfo dbi;
			dbi.buffer = Handle;
			dbi.offset = 0;
			dbi.range = VK_WHOLE_SIZE;
			UBODescriptorBufferInfos.push_back(dbi);

			VkWriteDescriptorSet WriteDescriptorSet{};
			WriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSet.dstBinding = Binding;
			WriteDescriptorSet.dstSet = DescriptorSet->GetHandle();
			WriteDescriptorSet.descriptorCount = 1;
			WriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			WriteDescriptorSet.pBufferInfo = &UBODescriptorBufferInfos.back();
			WriteDescriptorSets.push_back(WriteDescriptorSet);
		}
		else if (BindingType == RHIShaderResourceBinding::Type::DynamicUniformBuffer)
		{

		}
		else if (BindingType == RHIShaderResourceBinding::Type::UniformTexelBuffer)
		{

		}
		else if (BindingType == RHIShaderResourceBinding::Type::StorageBuffer)
		{
			VkBuffer Handle = ((VulkanBuffer*)Bindings[i].d.u.ubuf.buf)->GetHandle();

			VkDescriptorBufferInfo dbi;
			dbi.buffer = Handle;
			dbi.offset = 0;
			dbi.range = VK_WHOLE_SIZE;
			SSBODescriptorBufferInfos.push_back(dbi);

			VkWriteDescriptorSet WriteDescriptorSet{};
			WriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSet.dstBinding = Binding;
			WriteDescriptorSet.dstSet = DescriptorSet->GetHandle();
			WriteDescriptorSet.descriptorCount = 1;
			WriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			WriteDescriptorSet.pBufferInfo = &SSBODescriptorBufferInfos.back();
			WriteDescriptorSets.push_back(WriteDescriptorSet);
		}
		else if (BindingType == RHIShaderResourceBinding::Type::DynamicStorageBuffer)
		{

		}
		else if (BindingType == RHIShaderResourceBinding::Type::StorageTexelBuffer)
		{

		}
		else if (BindingType == RHIShaderResourceBinding::Type::Sampler)
		{
			VkSampler Handle = ((VulkanSampler*)Bindings[i].d.u.stex.texSamplers->sampler)->GetHandle();

			VkDescriptorImageInfo DescriptorImageInfo;
			DescriptorImageInfo.sampler			= Handle;
			DescriptorImageInfo.imageLayout		= VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			SamplersDescriptorImageInfos.push_back(DescriptorImageInfo);

			VkWriteDescriptorSet WriteDescriptorSet{};
			WriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSet.dstBinding = Binding;
			WriteDescriptorSet.dstSet = DescriptorSet->GetHandle();
			WriteDescriptorSet.descriptorCount = 1;
			WriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
			WriteDescriptorSet.pImageInfo = &SamplersDescriptorImageInfos.back();
			WriteDescriptorSets.push_back(WriteDescriptorSet);
		}
		else if (BindingType == RHIShaderResourceBinding::Type::SampledImage)
		{
			/*
				https://docs.vulkan.org/samples/latest/samples/api/separate_image_sampler/README.html
			*/
			VkImageView Handle = ((VulkanImageView*)Bindings[i].d.u.stex.texSamplers->tex)->GetHandle();

			VkDescriptorImageInfo DescriptorImageInfo;
			DescriptorImageInfo.imageView	= Handle;
			DescriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			SampledImagesDescriptorImageInfos.push_back(DescriptorImageInfo);

			VkWriteDescriptorSet WriteDescriptorSet{};
			WriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSet.dstBinding = Binding;
			WriteDescriptorSet.dstSet = DescriptorSet->GetHandle();
			WriteDescriptorSet.descriptorCount = 1;
			WriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			WriteDescriptorSet.pImageInfo = &SampledImagesDescriptorImageInfos.back();
			WriteDescriptorSets.push_back(WriteDescriptorSet);
		}
		else if (BindingType == RHIShaderResourceBinding::Type::CombinedImageSampler)
		{
			VkSampler   Sampler   = ((VulkanSampler*)Bindings[i].d.u.stex.texSamplers->sampler)->GetHandle();
			VkImageView ImageView = ((VulkanTexture*)Bindings[i].d.u.stex.texSamplers->tex)->ImageView->GetHandle();

			VkDescriptorImageInfo DescriptorImageInfo;
			DescriptorImageInfo.sampler		= Sampler;
			DescriptorImageInfo.imageView	= ImageView;
			DescriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			CombinedImageSamplersDescriptorImageInfos.push_back(DescriptorImageInfo);

			VkWriteDescriptorSet WriteDescriptorSet{};
			WriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSet.dstBinding = Binding;
			WriteDescriptorSet.dstSet = DescriptorSet->GetHandle();
			WriteDescriptorSet.descriptorCount = 1;
			WriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			WriteDescriptorSet.pImageInfo = &CombinedImageSamplersDescriptorImageInfos.back();
			WriteDescriptorSets.push_back(WriteDescriptorSet);

			//std::cout << "CombinedImageSampler binding " << Binding << std::endl;
		}
		else if (BindingType == RHIShaderResourceBinding::Type::StorageImage)
		{
			VkImageView Handle = ((VulkanImageView*)Bindings[i].d.u.stex.texSamplers->tex)->GetHandle();

			VkDescriptorImageInfo DescriptorImageInfo;
			DescriptorImageInfo.imageView	= Handle;
			DescriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			StorageImageDescriptorImageInfos.push_back(DescriptorImageInfo);

			VkWriteDescriptorSet WriteDescriptorSet{};
			WriteDescriptorSet.sType			= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSet.dstBinding = Binding;
			WriteDescriptorSet.dstSet			= DescriptorSet->GetHandle();
			WriteDescriptorSet.descriptorCount	= 1;
			WriteDescriptorSet.descriptorType	= VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			WriteDescriptorSet.pImageInfo		= &StorageImageDescriptorImageInfos.back();
			WriteDescriptorSets.push_back(WriteDescriptorSet);
		}
	}

	UpdateDescriptorSets(WriteDescriptorSets.size(), WriteDescriptorSets.data(), 0, nullptr);

	std::cout << "UpdateDescriptorSets ok" << std::endl;
}

void VulkanShaderResourceBindings::UpdateDescriptorSets(uint32_t                    DescriptorWriteCount,
													    const VkWriteDescriptorSet* DescriptorWrites,
													    uint32_t                    DescriptorCopyCount,
													    const VkCopyDescriptorSet*  DescriptorCopies)
{
	Device->UpdateDescriptorSets(DescriptorWriteCount, DescriptorWrites, DescriptorCopyCount, DescriptorCopies);
}