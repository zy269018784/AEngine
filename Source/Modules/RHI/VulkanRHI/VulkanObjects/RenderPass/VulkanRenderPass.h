#pragma once
#include "Vulkan.h"
#include "RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHIObjects/RenderPass/RHIAttachment.h"
#include <vector>
class VulkanDevice;
/*
 *	todo:
 *		DepthAttachment.format                  = VK_FORMAT_D24_UNORM_S8_UINT;
 *
 */
class VulkanRenderPass : public RHIRenderPass
{
public:
	VulkanRenderPass();
	VulkanRenderPass(VulkanDevice* InDevice, VkFormat InFormat, std::vector<RHIAttachment> &InColorAttachments, RHIAttachment &InDepthAttachments);
	~VulkanRenderPass();
	VkRenderPass GetHandle();
private:
	VkRenderPass Handle;
	VulkanDevice* Device = nullptr;
};