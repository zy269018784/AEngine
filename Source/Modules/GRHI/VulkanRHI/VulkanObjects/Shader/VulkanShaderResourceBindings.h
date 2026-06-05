#pragma once
#include "VulkanRHI/Vulkan.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"

class VulkanDescriptorPool;
class VulkanDescriptorSetLayout;
class VulkanDescriptorSet;
class VulkanDevice;

class VulkanShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	VulkanShaderResourceBindings(VulkanDevice *Device);
	~VulkanShaderResourceBindings();
	virtual void Create() final override;
	virtual void Bind() final override;
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
