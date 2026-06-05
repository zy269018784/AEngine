#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include <vector>
#include <cstdint>

class RHIRenderPass;
class RHICommandBuffer;
class RHIDevice;
class RHISwapChain;
class RHIEXPORT RHISwapChainRenderTarget : public RHIRenderTarget
{
public:
    RHISwapChainRenderTarget() = default;
    RHISwapChainRenderTarget(RHIDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight, RHIPixelFormat InPixelFormat);
    virtual ~RHISwapChainRenderTarget();
public:
    void Create();
protected:
    RHIPixelFormat PixelFormat;
    RHISwapChain   *SwapChain;
};