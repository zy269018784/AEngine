#pragma once
#include <VulkanRHI/Vulkan.h>
#include <RHI/RHIObjects/RenderPass/RHIRenderPass.h>
#include <RHI/RHIObjects/RenderPass/RHISubPass.h>
#include <RHI/RHIObjects/FrameBuffer/RHIAttachment.h>
#include <vector>

class VulkanDevice;

class VulkanRenderPass : public RHIRenderPass
{
public:
	VulkanRenderPass() = delete;
	VulkanRenderPass(RHIDevice* InDevice,
		std::vector<RHIAttachment *> InColorAttachments, std::vector<RHIAttachment *> InDepthAttachments,
		std::vector<RHISubPass *> InSubPass);
	~VulkanRenderPass();
	VkRenderPass GetHandle();
	virtual void Create() override final;
private:
	void Create1_0();
	void Create1_2();
private:
	VkRenderPass Handle;
};