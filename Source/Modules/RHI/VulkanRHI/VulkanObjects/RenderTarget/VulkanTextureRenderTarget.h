#pragma once
#include "VulkanRenderTarget.h"
#include "RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "Vulkan.h"
/*
 *  Image View
 *  Render Pass
 *  Framebuffery
 */
class VulkanTexture;
class VulkanTextureRenderTarget : public VulkanRenderTarget
{
public:
    VulkanTextureRenderTarget(VulkanTexture *InTexture, VulkanDevice *InDevice);
    ~VulkanTextureRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
public:
    VulkanTexture *Texture;
};