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

OpenGLTexture *OpenGL46Framebuffer::CreateTexture(RHIDevice *Device, RHIPixelFormat Format, std::uint32_t Width, std::uint32_t Height)
{
    return new OpenGL46Texture(Device, RHITextureType::Texture2D, Format, 1, 1, Width, Height, 1, nullptr);
}




