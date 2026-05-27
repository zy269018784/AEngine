#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/Device/RHIDevice.h"
#include "RHI/RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include <vector>

class RHIRenderPass;
class RHICommandBuffer;
class RHIFrameBuffer;
class RHIAttachment;
class RHITexture;


class RHIEXPORT RHITextureRenderTarget : public RHIRenderTarget
{
public:
    RHITextureRenderTarget() = default;
    RHITextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~RHITextureRenderTarget();
public:
    /*
     * Texture Render Target Interface
     */
    virtual void Create(std::vector<RHITexture *> InColorAttachments,
                        std::vector<RHITexture *> InDepthAttachments) = 0;
    virtual RHIAttachment *CreateAttachment(RHIAttachmentType Type, RHITexture *InTexture) = 0;
protected:
    RHIPixelFormat PixelFormat;
    /*
     * 帧缓冲
     */
    RHIFrameBuffer *Framebuffer = nullptr;
    /*
     * 颜色附件
     */
    std::vector<RHIAttachment *> ColorAttachments;
    /*
     * 深度模板附件
     */
    std::vector<RHIAttachment *> DepthStencilAttachments;
};