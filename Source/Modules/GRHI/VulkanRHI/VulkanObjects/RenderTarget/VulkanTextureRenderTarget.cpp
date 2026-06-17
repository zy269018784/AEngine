#include "VulkanTextureRenderTarget.h"
#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanFrameBuffer.h"
#include "VulkanRHI/VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanRHI/VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanAttachment.h"
#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanImageView.h"
#include <iostream>


VulkanTextureRenderTarget::VulkanTextureRenderTarget(VulkanDevice* InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : RHITextureRenderTarget(InDevice, InWidth, InHeight), Device(InDevice)
{


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
    w = Width;
    h = Height;
}

void VulkanTextureRenderTarget::RHIBeginRenderPass()
{
    //VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    VkClearValue ClearColor[4];
    ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}}; // 颜色1
    ClearColor[1].color = {{0.0f, 0.0f, 0.0f, 1.0f}}; // 颜色2 (如有)
    ClearColor[2].depthStencil = {1.0f, 0}; // 深度范围 [0,1]，模板随意
    ClearColor[3].depthStencil = {1.0f, 0}; // 第四个附件的清除值（根据实际需求）

    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass			= dynamic_cast<VulkanRenderPass*>(RenderPass)->GetHandle();
  //  RenderPassInfo.framebuffer			= FrameBuffers[CurrentImageIndex]->GetHandle();
    RenderPassInfo.framebuffer			= dynamic_cast<VulkanFrameBuffer *>(FrameBuffers[0])->GetHandle();
    RenderPassInfo.renderArea.offset	= { 0, 0 };
    RenderPassInfo.renderArea.extent	= { Width, Height};
    RenderPassInfo.clearValueCount		= 4;
    RenderPassInfo.pClearValues			= ClearColor;
    dynamic_cast<VulkanCommandBuffer*>(GraphicsCommandBuffers[CurrentImageIndex])->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanTextureRenderTarget::RHIEndRenderPass()
{
    dynamic_cast<VulkanCommandBuffer*>(GraphicsCommandBuffers[CurrentImageIndex])->CmdEndRenderPass();
}

void VulkanTextureRenderTarget::RHIBeginRenderPass2()
{

}

void VulkanTextureRenderTarget::RHIEndRenderPass2()
{

}

void VulkanTextureRenderTarget::Resize(float Width, float Height)
{

}

void VulkanTextureRenderTarget::WaitDeviceIdle()
{
    Device->DeviceWaitIdle();
}


void VulkanTextureRenderTarget::Create(std::vector<RHITexture *> InColorTextures,
                                       std::vector<RHITexture *> InDepthTextures)
{
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

    CreateRenderPass();


    if (InColorTextures.size() > 16)
    {
        std::cout << "greater than 16" << std::endl;
    }
    RHIAttachmentType Type;

    ColorAttachments.resize(InColorTextures.size());
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {
        Type = ToRHIAttachmentType(Index);
        ColorAttachments[Index] = new VulkanAttachment(Type, InColorTextures[Index],
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_LOAD, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_LOAD, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE);
    }

    DepthStencilAttachments.resize(InDepthTextures.size());
    for (std::uint32_t Index = 0; Index < DepthStencilAttachments.size(); ++Index)
    {
        switch (InDepthTextures[Index]->GetFormat())
        {
            case RHIPixelFormat::PF_DepthOnly_D16:
                Type = RHIAttachmentType::DepthOnly_D16;
                break;
            case RHIPixelFormat::PF_DepthOnly_D32:
                Type = RHIAttachmentType::DepthOnly_D32;
                break;
            case RHIPixelFormat::PF_DepthStencil_D24_S8:
                Type = RHIAttachmentType::DepthStencil_D24_S8;
                break;
            case RHIPixelFormat::PF_DepthStencil_D32_S8:
                Type = RHIAttachmentType::DepthStencil_D32_S8;
                break;
            default:
                Type = RHIAttachmentType::DepthStencil_D32_S8;
                break;
        }
        DepthStencilAttachments[Index] = new VulkanAttachment(Type, InDepthTextures[Index],
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_LOAD, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_LOAD, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE);
    }



    RHIAttachment DepthAttachment(DepthStencilType, nullptr,
        RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE);
    std::cout << "VulkanTextureRenderTarget " << ColorAttachments.size() << " " << DepthStencilAttachments.size() << std::endl;
    RenderPass = new VulkanRenderPass(Device, ColorAttachments,DepthStencilAttachments);
    RenderPass->Create();
    CreateFramebuffer();
    CreateCommandbuffer();
}

void VulkanTextureRenderTarget::CreateFramebuffer()
{
    //RHIPixelFormat SwapChainRHIPixelFormat = SwapChain->GetRHIPixelFormat();
#if 1
    // AMD Radeon RX580 2048SP
    RHIAttachmentType DepthStencilType = RHIAttachmentType::DepthStencil_D32_S8;
    RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D32_S8;
#else
    // 4060 support
    // AMD Radeon RX580 2048SP do not support
    RHIDepthAttachmentType DepthStencilType = RHIDepthAttachmentType::DepthStencil_D24_S8;
    RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D24_S8;
#endif

    DepthStencilPixelFormat = DepthStencilAttachments[0]->GetTexture()->GetFormat();
    /*
        3. 创建Frame Buffer
    */
    FrameBuffers.resize(1);
    FrameBuffers[0] = new VulkanFrameBuffer(dynamic_cast<VulkanDevice *>(Device), dynamic_cast<VulkanRenderPass *>(RenderPass),
                             { Width, Height }, ColorAttachments, DepthStencilAttachments);
#if 0
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {
        std::cout << "CreateFramebuffer 3" << std::endl;
        VulkanTexture * VT = dynamic_cast<VulkanTexture *>(ColorAttachments[Index]->GetTexture());
        std::cout << "CreateFramebuffer 4" << std::endl;
        std::vector<RHIAttachment *> InColorAttachments;
        InColorAttachments.emplace_back(new VulkanAttachment(RHIAttachmentType::Color1, VT->GetFormat(), VT->GetImageView()));
        std::cout << "CreateFramebuffer 5" << std::endl;
        VulkanTexture *DepthTex = new VulkanTexture(dynamic_cast<VulkanDevice *>(Device),
                  RHITextureType::Texture2D,
                  DepthStencilPixelFormat,
                  RHITextureUsageFlag::DepthStencilAttachment,
                  1,
                  Width,
                  Height,
                  1,
                  1);
        std::cout << "CreateFramebuffer 6" << std::endl;
        std::vector<RHIAttachment *> InDepthAttachments;
        InDepthAttachments.emplace_back(new VulkanAttachment(DepthStencilType, DepthStencilPixelFormat, DepthTex->ImageView->GetHandle()));

        std::cout << "CreateFramebuffer 7 " << InColorAttachments.size() << std::endl;
        FrameBuffers[Index] = new VulkanFrameBuffer(dynamic_cast<VulkanDevice *>(Device), dynamic_cast<VulkanRenderPass *>(RenderPass),
                                { Width, Height },
                                                InColorAttachments, InDepthAttachments);
        std::cout << "CreateFramebuffer 8" << std::endl;
    }
#endif
}


void VulkanTextureRenderTarget::CreateRenderPass()
{

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


}

void VulkanTextureRenderTarget::CreateCommandbuffer()
{
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