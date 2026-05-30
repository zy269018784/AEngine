#pragma once
#include "RHI/RHIObjects/Framebuffer/RHIAttachment.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLFramebuffer.h"

class OpenGLDevice;
class OpenGL46Framebuffer : public OpenGLFramebuffer
{
public:
    OpenGL46Framebuffer() = delete;
    OpenGL46Framebuffer(OpenGLDevice *InDevice, std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIAttachment *> &InColorAttachments,
                      std::vector<RHIAttachment *> &InDepthAttachments);
    ~OpenGL46Framebuffer();
};