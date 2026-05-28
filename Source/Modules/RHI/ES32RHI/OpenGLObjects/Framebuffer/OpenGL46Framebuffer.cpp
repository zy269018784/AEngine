#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGL46Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGL46Texture.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

OpenGL46Framebuffer::OpenGL46Framebuffer(OpenGLDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight,
                                std::vector<RHIAttachment *> &InColorAttachments,
                                std::vector<RHIAttachment *> &InDepthAttachments)
            : OpenGLFramebuffer(InDevice, InWidth, InHeight, InColorAttachments, InDepthAttachments)
{

}

OpenGL46Framebuffer::~OpenGL46Framebuffer()
{

}



