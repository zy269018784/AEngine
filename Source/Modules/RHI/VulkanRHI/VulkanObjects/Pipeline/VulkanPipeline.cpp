#include <VulkanObjects/Pipeline/VulkanPipeline.h>
#include <iostream>
VulkanPipeline::VulkanPipeline()
	: Device(nullptr), Handle(VK_NULL_HANDLE)
{

}

VulkanPipeline::VulkanPipeline(VulkanDevice* Device)
	: Device(Device), Handle(VK_NULL_HANDLE)
{
	//DescriptorPool = new VulkanDescriptorPool(Device);
}

VulkanPipeline::VulkanPipeline(VulkanDevice* Device, VkPipeline Handle)
	: Device(Device), Handle(Handle)
{

}

VulkanPipeline::~VulkanPipeline()
{
	std::cout << "~VulkanPipeline() " << Handle << std::endl;
	Device->DestroyPipeline(Handle, nullptr);
	Device->DestroyPipelineLayout(PipelineLayout, nullptr);
	//Device->DestroyDescriptorSetLayout(DescriptorSetLayout, nullptr);
}

VkPipeline VulkanPipeline::GetHandle()
{
	return Handle;
}

VkPipelineLayout VulkanPipeline::GetPipelineLayout()
{
	return PipelineLayout;
}

//VkDescriptorSetLayout VulkanPipeline::GetDescriptorSetLayout()
//{
//	return DescriptorSetLayout;
//}

VkPipelineBindPoint VulkanPipeline::GetPipelineBindPoint()
{
	return BindPoint;
}

//VulkanDescriptorPool* VulkanPipeline::GetDescriptorPool()
//{
//	return DescriptorPool;
//}