#pragma once
#include "VulkanRHI/Vulkan.h"
#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"
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