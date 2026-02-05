#include "VulkanSwapChainRenderTarget.h"
#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include <iostream>

VulkanSwapChainRenderTarget::VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface)
    : Device(InDevice), Surface(InSurface)
{
    SwapChain = new VulkanSwapChain(Device, Surface);

    SwapChainImageFormat    = Surface->CurrentFormat.format;
    SwapChainClorSpace      = Surface->CurrentFormat.colorSpace;
    SwapChainExtent         = Surface->CurrentExtent;
    SwapChainPresentMode    = Surface->CurrentPresentMode;

    SwapChainImageViews = SwapChain->SwapChainImageViews;
#if 0
    /*
        创建Render Pass
    */
     RenderPass = new VulkanRenderPass(Device, SwapChainImageFormat);
     SwapChain->RenderPass = RenderPass;
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
        FrameBuffers[i] = new VulkanFrameBuffer(Device, RenderPass, { SwapChainExtent.width, SwapChainExtent.height }, Handle);
        //SwapChain->FrameBuffers[i] = FrameBuffers[i];
    }
#endif
}

VulkanSwapChainRenderTarget::~VulkanSwapChainRenderTarget()
{

}
