#include "ES32RHI/OpenGLObjects/Framebuffer/ES31Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/ES31Texture.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

ES31Framebuffer::ES31Framebuffer(OpenGLDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight,
                                std::vector<RHIAttachment *> &InColorAttachments,
                                std::vector<RHIAttachment *> &InDepthAttachments)
            : OpenGLFramebuffer(InDevice, InWidth, InHeight, InColorAttachments, InDepthAttachments)
{

}

ES31Framebuffer::~ES31Framebuffer()
{

}





