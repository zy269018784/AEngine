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
class VulkanTextureRenderTarget : public VulkanRenderTarget, public RHITextureRenderTarget
{
public:
    VulkanTextureRenderTarget(VulkanTexture *InTexture = nullptr);
    ~VulkanTextureRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
public:
    VulkanTexture *Texture;
};