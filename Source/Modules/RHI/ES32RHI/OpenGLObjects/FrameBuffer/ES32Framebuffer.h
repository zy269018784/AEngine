#pragma once
#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLFramebuffer.h"
#include "RHI/RHIObjects/Framebuffer/RHIAttachment.h"
#include <vector>

class OpenGLDevice;
class ES32Framebuffer : public OpenGLFramebuffer
{
public:
    ES32Framebuffer() = delete;
    ES32Framebuffer(OpenGLDevice *InDevice, std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIAttachment *> &InColorAttachments,
                      std::vector<RHIAttachment *> &InDepthAttachments);
    ~ES32Framebuffer();
};