#include "VulkanTextureRenderTarget.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"

#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanObjects/RenderPass/VulkanAttachment.h"
#include "VulkanObjects/RenderPass/VulkanDepthAttachment.h"
#include "VulkanObjects/RenderPass/VulkanColorAttachment.h"
#include "VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanObjects/Core/VulkanCore.h"
#include <iostream>

#include "VulkanObjects/Texture/VulkanTexture.h"

VulkanTextureRenderTarget::VulkanTextureRenderTarget(VulkanDevice* InDevice, VulkanTexture* InTexture)
    : Texture(InTexture), VulkanRenderTarget(InTexture->GetFormat(), InDevice)
{
    Resolution.width = InTexture->GetX();
    Resolution.height = InTexture->GetY();
#if 1
    // AMD Radeon RX580 2048SP
    RHIDepthAttachmentType DepthStencilType = RHIDepthAttachmentType::DepthStencil_D32_S8;
    RHIAttachmentType	   RHIDepthStencilType = RHIAttachmentType::DepthStencil_D32_S8;
    RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D32_S8;
#else
    // 4060 support
    // AMD Radeon RX580 2048SP do not support
    RHIDepthAttachmentType DepthStencilType = RHIDepthAttachmentType::DepthStencil_D24_S8;
    RHIAttachmentType	   RHIDepthStencilType = RHIAttachmentType::DepthStencil_D24_S8;
    RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D24_S8;
#endif


    std::cout << "VulkanSwapChainRenderTarget ImageFormat PF_R8G8B8A8_UNORM"  << std::endl;

    //RHIAttachment Color1Attachment(RHIAttachmentType::Color1,  InTexture->GetFormat());
   // RHIAttachment DepthAttachment(DepthStencilType, DepthStencilPixelFormat);

    /*
        1. 创建Render Pass
    */
    std::vector<RHIColorAttachment> ColorAttachments;
    ColorAttachments.emplace_back(RHIColorAttachment(RHIAttachmentType::Color1, InTexture->GetFormat()));

    RHIDepthAttachment DepthAttachment(DepthStencilType);
    RenderPass = (RHIRenderPass *)new VulkanRenderPass(Device, ToVkFormat(InTexture->GetFormat()), ColorAttachments,DepthAttachment);


    ImageViews.push_back(InTexture->ImageView->GetHandle());
    /*
        2. 创建Frame Buffer
    */
    FrameBuffers.resize(3);
    for (int i = 0; i < FrameBuffers.size(); i++)
    {
        VulkanTexture *Tex = new VulkanTexture(InDevice,
                RHITextureType::Texture2D,
                DepthStencilPixelFormat,
                RHITextureUsageFlag::DepthStencilAttachment,
                1,
                InTexture->GetX(),
                InTexture->GetY(),
                1,
                1);
#if 0
        std::vector<VulkanAttachment> InVKAttachments;
        InVKAttachments.emplace_back(VulkanAttachment(RHIAttachmentType::Color1, InTexture->GetFormat(), ImageViews[0]));
        InVKAttachments.emplace_back(VulkanAttachment(DepthStencilType, DepthStencilPixelFormat, Tex->ImageView->GetHandle()));
#endif
        std::vector<RHIColorAttachment *> InColorAttachments;
        InColorAttachments.emplace_back(new VulkanColorAttachment(ImageViews[i],RHIAttachmentType::Color1, RHIPixelFormat::PF_R8G8B8A8_UNORM));

        std::vector<RHIDepthAttachment *> InDepthAttachments;
        InDepthAttachments.emplace_back(new VulkanDepthAttachment(ImageViews[i], DepthStencilType));

        FrameBuffers[i] = new VulkanFrameBuffer(Device, dynamic_cast<VulkanRenderPass *>(RenderPass), { InTexture->GetX(), InTexture->GetY() },
			InColorAttachments, InDepthAttachments);
    }

     /*
        3. 创建command buffer
     */
    GraphicsCommandBuffers.resize(3);
    for (int i = 0; i < GraphicsCommandBuffers.size(); i++)
    {
        /*
            暂时用第0个Command Pool
        */
        GraphicsCommandBuffers[i] = Device->CreateCommandBuffer(Device->CommandPools[0]);
    }
}
#if 0
VulkanTextureRenderTarget::VulkanTextureRenderTarget(RHIPixelFormat InPixelFormat, VulkanDevice *InDevice)
    : VulkanRenderTarget(InPixelFormat, InDevice)
{

}
#endif
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
    x = 0;
    y = 0;
    w = Resolution.width;
    h = Resolution.height;
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

void VulkanTextureRenderTarget::Resize(float Width, float Height)
{

}