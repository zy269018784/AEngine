#include "VulkanSwapChainRenderTarget.h"
#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Window/VulkanFrame.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include <iostream>

VulkanSwapChainRenderTarget::VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface)
    : Device(InDevice), Surface(InSurface)
{
    SwapChain = new VulkanSwapChain(Device, Surface);

    ImageFormat    = Surface->CurrentFormat.format;
    SwapChainClorSpace      = Surface->CurrentFormat.colorSpace;
    Resolution              = Surface->CurrentExtent;
    SwapChainPresentMode    = Surface->CurrentPresentMode;

    ImageViews = SwapChain->SwapChainImageViews;

    Frames.resize(SwapChain->GetImageCount());
    for (int i = 0; i < Frames.size(); i++)
        Frames[i] = new VulkanFrame(Device, true);
#if 1
    /*
        创建Render Pass
    */
     RenderPass = new VulkanRenderPass(Device, ImageFormat);
     //SwapChain->RenderPass = RenderPass;
#else
     RenderPass = SwapChain->RenderPass;
#endif

#if 1
    /*
        创建Frame Buffer
    */
    std::cout << "SwapChainImageViews.size() " << SwapChain->SwapChainImageViews.size()  << std::endl;
    FrameBuffers.resize(SwapChain->SwapChainImageViews.size());
    //SwapChain->FrameBuffers.resize(SwapChain->SwapChainImageViews.size());
    for (int i = 0; i < FrameBuffers.size(); i++)
    {
        auto Handle = SwapChain->SwapChainImageViews[i];
        FrameBuffers[i] = new VulkanFrameBuffer(Device, RenderPass, { Resolution.width, Resolution.height }, Handle);
        //SwapChain->FrameBuffers[i] = FrameBuffers[i];
    }
#endif

    GraphicsCommandBuffers.resize(SwapChain->GetImageCount());
    for (int i = 0; i < GraphicsCommandBuffers.size(); i++)
    {
        /*
            暂时用第0个Command Pool
        */
        GraphicsCommandBuffers[i] = Device->CreateCommandBuffer(Device->CommandPools[0]);
    }
}

VulkanSwapChainRenderTarget::~VulkanSwapChainRenderTarget()
{

}

void VulkanSwapChainRenderTarget::RHIBeginRenderPass()
{
    //VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    VkClearValue ClearColor[2];
    ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    ClearColor[1].depthStencil = {1.0f, 0};  // 深度清除为1.0（最远值

    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass			= RenderPass->GetHandle();
    RenderPassInfo.framebuffer			= FrameBuffers[CurrentImageIndex]->GetHandle();
    RenderPassInfo.renderArea.offset	= { 0, 0 };
    RenderPassInfo.renderArea.extent	= Resolution;
    RenderPassInfo.clearValueCount		= 2;
    RenderPassInfo.pClearValues			= ClearColor;

    GraphicsCommandBuffers[CurrentImageIndex]->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanSwapChainRenderTarget::RHIEndRenderPass()
{
    GraphicsCommandBuffers[CurrentImageIndex]->CmdEndRenderPass();
}