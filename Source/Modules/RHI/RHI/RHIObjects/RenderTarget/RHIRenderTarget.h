#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <vector>

class RHIRenderPass;
class RHICommandBuffer;
class RHIDevice;
class RHIEXPORT RHIRenderTarget
{
public:
    RHIRenderTarget() = default;
    RHIRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~RHIRenderTarget();
public:
    /*
     * RHIRenderTarget Interface
     */
    RHIRenderPass *GetRenderPass() const;
    RHICommandBuffer* CurrentGraphicsCommandBuffer() const;
public:
    /*
     * RHIRenderTarget (Virtual) Interface
     */
    virtual void RHIBeginRenderPass() = 0;
    virtual void RHIEndRenderPass() = 0;
    virtual void RHIBeginFrame() = 0;
    virtual void RHIEndFrame() = 0;
    virtual void GetExtent(float &x, float &y, float &w, float &h) = 0;
    virtual void Resize(float Width, float Height) = 0;
    virtual void WaitDeviceIdle() = 0;
    virtual void CreateFramebuffer() = 0;
    virtual void CreateRenderPass()  = 0;
    virtual void CreateCommandbuffer() = 0;
protected:
    /*
     * 逻辑设备
     */
    RHIDevice * Device = nullptr;
    /*
     * Render Pass
     */
    RHIRenderPass *RenderPass = nullptr;
    /*
     * 宽度
     */
    std::uint32_t Width = 0;
    /*
     * 高度
     */
    std::uint32_t Height = 0;

    /*
        用于图像的command buffer
    */
    std::vector<RHICommandBuffer*>	    GraphicsCommandBuffers;		// SwapChainImages.size()
    std::uint32_t					    CurrentImageIndex = 0;      // [0, SwapChainImages.size() - 1]
};