#pragma once
#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLFramebuffer.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include <vector>

class OpenGLDevice;
class ES31Framebuffer : public OpenGLFramebuffer
{
public:
    ES31Framebuffer() = delete;
    ES31Framebuffer(OpenGLDevice *InDevice, std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIAttachment *> &InColorAttachments,
                      std::vector<RHIAttachment *> &InDepthAttachments);
    ~ES31Framebuffer();
public:
    virtual OpenGLTexture *CreateTexture(RHIDevice *InDevice, RHIPixelFormat Format, std::uint32_t Width, std::uint32_t Height) override final;
};