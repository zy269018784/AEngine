#include "VulkanSwapChainRenderTarget.h"
#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Window/VulkanFrame.h"
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
