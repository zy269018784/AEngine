#pragma once
#include "VulkanRHI/Vulkan.h"

#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include <vector>
#include <map>
#include <cstdint>

class VulkanDevice;
class VulkanDescriptorSetLayoutBinding
{
public:
	std::vector<VkDescriptorSetLayoutBinding> LayoutBindings;
};

class VulkanDescriptorSetLayout
{

public:
	VulkanDescriptorSetLayout(VulkanDevice* InDevice = nullptr);
	VulkanDescriptorSetLayout(VulkanDevice* InDevice, RHIShaderResourceBindings* SRB);
	~VulkanDescriptorSetLayout();
public:
	VkDescriptorSetLayout GetHandle() const; 
	const std::vector<VulkanDescriptorSetLayoutBinding>& GetLayouts() const;
	std::uint32_t GetTypesUsed(VkDescriptorType Type);

private:
	VkResult CreateDescriptorSetLayout(VkDescriptorSetLayoutCreateInfo* CreateInfo, const VkAllocationCallbacks* pAllocator);
	void DestroyDescriptorSetLayout(const VkAllocationCallbacks* Allocator);
private:
	VkDescriptorSetLayout Handle;
	VulkanDevice* Device;
	std::vector<VulkanDescriptorSetLayoutBinding> SetLayouts;
	std::map<VkDescriptorType, std::uint32_t> LayoutTypes;
	std::vector<VkDescriptorSetLayout> LayoutHandles;
};