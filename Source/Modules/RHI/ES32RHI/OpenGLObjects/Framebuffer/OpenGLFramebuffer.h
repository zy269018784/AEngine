#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include "RHI/RHIObjects/Device/RHIDevice.h"
#include <vector>

class OpenGLTexture;
class OpenGLFramebuffer : public RHIFrameBuffer
{
public:
    OpenGLFramebuffer() = delete;
    OpenGLFramebuffer(RHIDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight,
                                std::vector<RHIAttachment *> &InColorAttachments,
                                std::vector<RHIAttachment *> &InDepthAttachments);
    ~OpenGLFramebuffer();
    GLuint GetHandle() const;
public:
    virtual void Bind() const override final;
    void Create();
 protected:
    GLuint Handle;
    std::vector<RHIAttachment *> ColorAttachments;
    std::vector<RHIAttachment *> DepthAttachments;
    RHIDevice * Device;
    std::uint32_t Width;
    std::uint32_t Height;
};