#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGL33Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGL33Texture.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

OpenGL33Framebuffer::OpenGL33Framebuffer(OpenGLDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight,
                                std::vector<RHIAttachment *> &InColorAttachments,
                                std::vector<RHIAttachment *> &InDepthAttachments)
            : OpenGLFramebuffer(InDevice, InWidth, InHeight, InColorAttachments, InDepthAttachments)
{

}

OpenGL33Framebuffer::~OpenGL33Framebuffer()
{

}





