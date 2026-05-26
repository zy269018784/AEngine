#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include <vector>



class RHIRenderPass;
class RHICommandBuffer;
class RHIFrameBuffer;

class RHIEXPORT RHITextureRenderTarget : public RHIRenderTarget
{
public:
    RHITextureRenderTarget() = default;
    RHITextureRenderTarget(RHIPixelFormat InPixelFormat);
    virtual ~RHITextureRenderTarget();
    virtual RHIRenderPass *GetRenderPass() const override final;
    virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() const override final;
public:
    RHIPixelFormat PixelFormat;
    RHIRenderPass *RenderPass;
    RHIFrameBuffer *Framebuffer;
    /*
        用于图像的command buffer
    */
    std::vector<RHICommandBuffer*>	    GraphicsCommandBuffers;		// SwapChainImages.size()

    std::uint32_t					    CurrentImageIndex = 0;      // [0, SwapChainImages.size() - 1]
};