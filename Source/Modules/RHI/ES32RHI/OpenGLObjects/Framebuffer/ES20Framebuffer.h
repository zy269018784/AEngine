#pragma once
#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGLFramebuffer.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include <vector>

class OpenGLDevice;
class ES20Framebuffer : public OpenGLFramebuffer
{
public:
    ES20Framebuffer() = delete;
    ES20Framebuffer(OpenGLDevice *InDevice, std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIAttachment *> &InColorAttachments,
                      std::vector<RHIAttachment *> &InDepthAttachments);
    ~ES20Framebuffer();
};