#if 0
#include "VulkanRenderTarget.h"
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects//FrameBuffer/VulkanFrameBuffer.h"

VulkanRenderTarget::VulkanRenderTarget(RHIPixelFormat InPixelFormat, VulkanDevice *InDevice)
    : RHIRenderTarget(InPixelFormat), Device(InDevice) {
}


VulkanRenderTarget::~VulkanRenderTarget()
{
   // for (int i = 0; i < ImageViews.size(); i++)
   //     delete ImageViews[i];

    for (int i = 0; i < FrameBuffers.size(); i++)
        delete FrameBuffers[i];
}

void VulkanRenderTarget::WaitDeviceIdle()
{
    Device->DeviceWaitIdle();
}
#endif