#pragma once
#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLFramebuffer.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include <vector>

class OpenGLDevice;
class OpenGL33Framebuffer : public OpenGLFramebuffer
{
public:
    OpenGL33Framebuffer() = delete;
    OpenGL33Framebuffer(OpenGLDevice *InDevice, std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIAttachment *> &InColorAttachments,
                      std::vector<RHIAttachment *> &InDepthAttachments);
    ~OpenGL33Framebuffer();
public:
    virtual OpenGLTexture *CreateTexture(RHIDevice *InDevice, RHIPixelFormat Format, std::uint32_t Width, std::uint32_t Height) override final;
};