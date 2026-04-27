#pragma once
#include "Vulkan.h"
#include "RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHIObjects/FrameBuffer/RHIAttachment.h"
#include "RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHIObjects/FrameBuffer/RHIDepthAttachment.h"
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