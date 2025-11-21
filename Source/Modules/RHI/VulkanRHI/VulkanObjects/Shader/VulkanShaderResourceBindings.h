#pragma once
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorPool.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorSetLayout.h"
#include <VulkanObjects/Descriptor/VulkanDescriptorSet.h>

class VulkanShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	VulkanShaderResourceBindings(VulkanDevice *Device);
	~VulkanShaderResourceBindings();
	virtual void Create() final override;
	VulkanDescriptorSet* GetDescriptorSet();
	VulkanDescriptorSetLayout* GetDescriptorSetLayout();

private:
	void CreateDescriptorPool();
	void CreateDescriptorSetLayout();
	void CreateDescriptorSets();
	void UpdateDescriptorSets();
public:
	void UpdateDescriptorSets(uint32_t						DescriptorWriteCount,
							  const VkWriteDescriptorSet*	DescriptorWrites,
							  uint32_t						DescriptorCopyCount,
							  const VkCopyDescriptorSet*	DescriptorCopies);
private:
	VulkanDescriptorPool*		DescriptorPool = nullptr;
	VulkanDescriptorSetLayout*	DescriptorSetLayout = nullptr;
	VulkanDescriptorSet*		DescriptorSet = nullptr;
	VulkanDevice* Device;
};
