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
    VulkanTextureRenderTarget();
    ~VulkanTextureRenderTarget();
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
};