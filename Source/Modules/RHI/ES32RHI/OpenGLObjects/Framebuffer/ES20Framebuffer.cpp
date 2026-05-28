#include "ES32RHI/OpenGLObjects/Framebuffer/ES20Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/ES20Texture.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
ES20Framebuffer::ES20Framebuffer(OpenGLDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight,
                                std::vector<RHIAttachment *> &InColorAttachments,
                                std::vector<RHIAttachment *> &InDepthAttachments)
            : OpenGLFramebuffer(InDevice, InWidth, InHeight, InColorAttachments, InDepthAttachments)
{

}

ES20Framebuffer::~ES20Framebuffer()
{

}

