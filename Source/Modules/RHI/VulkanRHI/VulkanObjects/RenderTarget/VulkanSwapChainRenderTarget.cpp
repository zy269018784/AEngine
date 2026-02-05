#include "VulkanSwapChainRenderTarget.h"
#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
VulkanSwapChainRenderTarget::VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface)
    : Device(InDevice), Surface(InSurface)
{
    SwapChain = new VulkanSwapChain(Device, Surface);
}

VulkanSwapChainRenderTarget::~VulkanSwapChainRenderTarget()
{

}
