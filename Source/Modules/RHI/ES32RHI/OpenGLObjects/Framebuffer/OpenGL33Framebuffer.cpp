#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGL33Framebuffer.h"
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

OpenGLTexture *OpenGL33Framebuffer::CreateTexture(RHIDevice *Device, RHIPixelFormat Format, std::uint32_t Width, std::uint32_t Height)
{
    return new OpenGL33Texture(Device, RHITextureType::Texture2D, Format, 1, 1, Width, Height, 1, nullptr);
}





