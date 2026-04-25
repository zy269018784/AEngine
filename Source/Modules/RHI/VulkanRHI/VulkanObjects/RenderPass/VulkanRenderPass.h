#pragma once
#include "Vulkan.h"
#include "RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHIObjects/RenderPass/RHIAttachment.h"
#include "RHIObjects/RenderPass/RHIColorAttachment.h"
#include "RHIObjects/RenderPass/RHIDepthAttachment.h"
#include <vector>
class VulkanDevice;

class VulkanRenderPass : public RHIRenderPass
{
public:
	VulkanRenderPass();
	VulkanRenderPass(VulkanDevice* InDevice, VkFormat InFormat, std::vector<RHIColorAttachment> &InColorAttachments, RHIDepthAttachment &InDepthAttachments);
	~VulkanRenderPass();
	VkRenderPass GetHandle();
private:
	VkRenderPass Handle;
	VulkanDevice* Device = nullptr;
};