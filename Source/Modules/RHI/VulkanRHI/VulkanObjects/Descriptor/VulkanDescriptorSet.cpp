#include <VulkanObjects/Descriptor/VulkanDescriptorSet.h>
#include <iostream>
VulkanDescriptorSet::VulkanDescriptorSet(VulkanDevice* Device, VulkanDescriptorPool* InDescriptorPool, VulkanDescriptorSetLayout* DescriptorSetLayout)
    : Device(Device), DescriptorPool(InDescriptorPool)
{
    VkDescriptorSetLayout SetLayouts = DescriptorSetLayout->GetHandle();

    VkDescriptorSetAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    AllocateInfo.descriptorPool = DescriptorPool->GetHandle();
    AllocateInfo.descriptorSetCount = 1;
    AllocateInfo.pNext = nullptr;
    AllocateInfo.pSetLayouts = &SetLayouts;
    VkResult ret = AllocateDescriptorSets(&AllocateInfo);
    std::cout << "AllocateDescriptorSets " << ret << std::endl;
}

VulkanDescriptorSet::~VulkanDescriptorSet()
{
   FreeDescriptorSets();
}

VkDescriptorSet VulkanDescriptorSet::GetHandle()
{
	return Handle;
}

VkResult VulkanDescriptorSet::AllocateDescriptorSets(const VkDescriptorSetAllocateInfo* AllocateInfo)
{
    return DescriptorPool->AllocateDescriptorSets(AllocateInfo, &Handle);
}

VkResult VulkanDescriptorSet::FreeDescriptorSets()
{
    return DescriptorPool->FreeDescriptorSets(1, &Handle);
}
