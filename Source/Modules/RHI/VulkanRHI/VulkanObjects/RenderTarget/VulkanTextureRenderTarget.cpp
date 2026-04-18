#include "VulkanTextureRenderTarget.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include <iostream>

#include "VulkanObjects/Texture/VulkanTexture.h"

VulkanTextureRenderTarget::VulkanTextureRenderTarget(VulkanTexture *InTexture, VulkanDevice *InDevice)
    : Texture(InTexture), VulkanRenderTarget(InTexture->GetFormat(), InDevice)
{
    /*
        1. 创建Render Pass
    */
    std::vector<RHIAttachment> InAttachments;
    InAttachments.emplace_back(RHIAttachment(RHIAttachmentType::Color1, RHIPixelFormat::PF_R8G8B8A8_UNORM));
    RenderPass = (RHIRenderPass *)new VulkanRenderPass(Device, ImageFormat, InAttachments, {RHIAttachmentType::DepthStencil, RHIPixelFormat::PF_R8G8B8A8_UNORM});

}

VulkanTextureRenderTarget::~VulkanTextureRenderTarget()
{

}

void VulkanTextureRenderTarget::RHIBeginFrame()
{
    /*
        current command buffer
    */
    VulkanCommandBuffer* CommandBuffer = dynamic_cast<VulkanCommandBuffer*>(GraphicsCommandBuffers[FrameIndex]);
    /*
        reset command buffer
    */
    if (CommandBuffer->ResetCommandBuffer(0) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to reset command buffer!");
    }

    /*
        begin recording a command buffer,
    */
    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (CommandBuffer->BeginCommandBuffer(&BeginInfo) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
}

void VulkanTextureRenderTarget::RHIEndFrame()
{
    /*
        current frame's command buffer
    */
    VulkanCommandBuffer* CommandBuffer = dynamic_cast<VulkanCommandBuffer*>(GraphicsCommandBuffers[FrameIndex]);
    /*
        complete recording of a command buffer
    */
    if (CommandBuffer->EndCommandBuffer() != VK_SUCCESS)
    {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void VulkanTextureRenderTarget::GetExtent(float &x, float &y, float &w, float &h) {

}

void VulkanTextureRenderTarget::RHIBeginRenderPass()
{
    //VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    VkClearValue ClearColor[2];
    ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    ClearColor[1].depthStencil = {1.0f, 0};  // 深度清除为1.0（最远值

    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass			= dynamic_cast<VulkanRenderPass*>(RenderPass)->GetHandle();
    RenderPassInfo.framebuffer			= FrameBuffers[CurrentImageIndex]->GetHandle();
    RenderPassInfo.renderArea.offset	= { 0, 0 };
    RenderPassInfo.renderArea.extent	= Resolution;
    RenderPassInfo.clearValueCount		= 2;
    RenderPassInfo.pClearValues			= ClearColor;

    dynamic_cast<VulkanCommandBuffer*>(GraphicsCommandBuffers[CurrentImageIndex])->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanTextureRenderTarget::RHIEndRenderPass()
{
    dynamic_cast<VulkanCommandBuffer*>(GraphicsCommandBuffers[CurrentImageIndex])->CmdEndRenderPass();
}
