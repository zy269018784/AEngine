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

OpenGLTexture *ES30Framebuffer::CreateTexture(RHIDevice *Device, RHIPixelFormat Format, std::uint32_t Width, std::uint32_t Height)
{
    return new ES30Texture(Device, RHITextureType::Texture2D, Format, 1, 1, Width, Height, 1, nullptr);
}





