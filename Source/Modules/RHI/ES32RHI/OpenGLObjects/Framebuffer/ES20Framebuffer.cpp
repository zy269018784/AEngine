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

OpenGLTexture *ES20Framebuffer::CreateTexture(RHIDevice *Device, RHIPixelFormat Format, std::uint32_t Width, std::uint32_t Height)
{
    return new ES20Texture(Device, RHITextureType::Texture2D, Format, 1, 1, Width, Height, 1, nullptr);
}


