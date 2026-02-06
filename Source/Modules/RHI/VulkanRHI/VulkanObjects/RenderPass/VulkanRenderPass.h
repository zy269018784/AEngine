#pragma once
#include "Vulkan.h"
#include "RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHIObjects/RenderPass/RHIAttachment.h"
#include <vector>
class VulkanDevice;
class VulkanRenderPass : public RHIRenderPass
{
public:
	VulkanRenderPass();
	VulkanRenderPass(VulkanDevice* InDevice, VkFormat InFormat, std::vector<RHIAttachment> InAttachments);
	~VulkanRenderPass();
	VkRenderPass GetHandle();
private:
	VkRenderPass Handle;
	VulkanDevice* Device = nullptr;
};