#include "VulkanRenderTarget.h"
#include "VulkanObjects/Device/VulkanDevice.h"
VulkanRenderTarget::VulkanRenderTarget(RHIPixelFormat InPixelFormat, VulkanDevice *InDevice)
    : RHIRenderTarget(InPixelFormat), Device(InDevice)
{

}

void VulkanRenderTarget::WaitDeviceIdle()
{
    Device->DeviceWaitIdle();
}