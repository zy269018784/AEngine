#pragma once
#include "VulkanRenderTarget.h"
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "VulkanRHI/Vulkan.h"
/*
 *  Image View
 *  Render Pass
 *  Framebuffery
 */
class VulkanTexture;
class VulkanTextureRenderTarget : public VulkanRenderTarget
{
public:
    VulkanTextureRenderTarget(VulkanDevice *InDevice, VulkanTexture *InTexture);
  //  VulkanTextureRenderTarget(RHIPixelFormat InPixelFormat, VulkanDevice *InDevice);
    ~VulkanTextureRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
public:
    VulkanTexture *Texture;
};