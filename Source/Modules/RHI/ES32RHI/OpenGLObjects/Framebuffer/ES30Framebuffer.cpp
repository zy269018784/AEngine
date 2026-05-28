#include "ES32RHI/OpenGLObjects/Framebuffer/ES30Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/ES30Texture.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"


ES30Framebuffer::ES30Framebuffer(OpenGLDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight,
                                std::vector<RHIAttachment *> &InColorAttachments,
                                std::vector<RHIAttachment *> &InDepthAttachments)
            : OpenGLFramebuffer(InDevice, InWidth, InHeight, InColorAttachments, InDepthAttachments)
{

}

ES30Framebuffer::~ES30Framebuffer()
{

}



