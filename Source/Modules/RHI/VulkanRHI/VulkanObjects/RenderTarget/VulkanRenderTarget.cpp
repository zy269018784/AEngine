#include "VulkanRenderTarget.h"

VulkanRenderTarget::VulkanRenderTarget(RHIPixelFormat InPixelFormat, VulkanDevice *InDevice)
    : RHIRenderTarget(InPixelFormat), Device(InDevice)
{

}
