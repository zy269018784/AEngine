#pragma once
#include "VulkanRHI/Vulkan.h"
#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

#include <vector>
class VulkanDevice;

class VulkanRenderPass : public RHIRenderPass
{
public:
	VulkanRenderPass() = delete;
	VulkanRenderPass(RHIDevice* InDevice, std::vector<RHIAttachment> &InColorAttachments, RHIAttachment &InDepthAttachments);
	~VulkanRenderPass();
	VkRenderPass GetHandle();
private:
	VkRenderPass Handle;
};