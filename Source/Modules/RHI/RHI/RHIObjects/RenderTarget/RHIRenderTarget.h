#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include <vector>
class RHIRenderPass;
class RHICommandBuffer;

class RHIRenderTarget
{
public:
    RHIRenderTarget(RHIPixelFormat InPixelFormat);
    virtual ~RHIRenderTarget();
    RHIRenderPass *GetRenderPass() const;
    RHICommandBuffer* CurrentGraphicsCommandBuffer() const;
    virtual void GetExtent(float &x, float &y, float &w, float &h) = 0;
    virtual void Resize(float Width, float Height) = 0;
    virtual void WaitDeviceIdle() = 0;
public:
    virtual void RHIBeginRenderPass() = 0;
    virtual void RHIEndRenderPass() = 0;
    virtual void RHIBeginFrame() = 0;
    virtual void RHIEndFrame() = 0;
public:
    RHIPixelFormat PixelFormat;
    RHIRenderPass *RenderPass;
    /*
        用于图像的command buffer
    */
    std::vector<RHICommandBuffer*>	    GraphicsCommandBuffers;		// SwapChainImages.size()

    std::uint32_t					    CurrentImageIndex = 0;      // [0, SwapChainImages.size() - 1]
};