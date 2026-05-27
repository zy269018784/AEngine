#include "VulkanTextureRenderTarget.h"
#include "VulkanRHI/VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanRHI/VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanRHI/VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanRHI/VulkanObjects/FrameBuffer/VulkanAttachment.h"
#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanImageView.h"
#include <iostream>


VulkanTextureRenderTarget::VulkanTextureRenderTarget(VulkanDevice* InDevice, VulkanTexture* InTexture)
    : Texture(InTexture), RHITextureRenderTarget(InDevice, InTexture->GetX(), InTexture->GetY()), Device(InDevice)
{
    Resolution.width = InTexture->GetX();
    Resolution.height = InTexture->GetY();
#if 1
    // AMD Radeon RX580 2048SP
    RHIAttachmentType   DepthStencilType = RHIAttachmentType::DepthStencil_D32_S8;
    RHIAttachmentType	RHIDepthStencilType = RHIAttachmentType::DepthStencil_D32_S8;
    RHIPixelFormat      DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D32_S8;
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
    std::vector<RHIAttachment> ColorAttachments;
    ColorAttachments.emplace_back(RHIAttachment(RHIAttachmentType::Color1, InTexture));

    RHIAttachment DepthAttachment(DepthStencilType, nullptr);
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
        std::vector<RHIAttachment *> InColorAttachments;
        InColorAttachments.emplace_back(new VulkanAttachment(RHIAttachmentType::Color1, nullptr));

        std::vector<RHIAttachment *> InDepthAttachments;
        InDepthAttachments.emplace_back(new VulkanAttachment(DepthStencilType, nullptr));

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

void VulkanTextureRenderTarget::WaitDeviceIdle()
{
    Device->DeviceWaitIdle();
}


void VulkanTextureRenderTarget::Create(std::vector<RHITexture *> InColorAttachments,
                                       std::vector<RHITexture *> InDepthAttachments)
{

}

RHIAttachment *VulkanTextureRenderTarget::VulkanTextureRenderTarget::CreateAttachment(RHIAttachmentType Type, RHITexture *InTexture)
{
    return nullptr;
}

void VulkanTextureRenderTarget::CreateFramebuffer() {}
void VulkanTextureRenderTarget::CreateRenderPass() {}
void VulkanTextureRenderTarget::CreateCommandbuffer() {}