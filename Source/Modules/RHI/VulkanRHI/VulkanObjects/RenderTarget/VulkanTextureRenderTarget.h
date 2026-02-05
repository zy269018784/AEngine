#pragma once
#include "VulkanRenderTarget.h"
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
    VulkanTextureRenderTarget(VulkanTexture *InTexture = nullptr);
    ~VulkanTextureRenderTarget();
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
public:
    VulkanTexture *Texture;
};