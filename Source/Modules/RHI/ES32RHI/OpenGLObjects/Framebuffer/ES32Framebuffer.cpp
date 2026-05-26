#include "ES32RHI/OpenGLObjects/Framebuffer/ES32Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/ES32Texture.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

ES32Framebuffer::ES32Framebuffer(OpenGLDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight,
                      std::vector<RHIAttachment *> &InColorAttachments,
                      std::vector<RHIAttachment *> &InDepthAttachments)
: OpenGLFramebuffer(InDevice, InWidth, InHeight, InColorAttachments, InDepthAttachments)
{

}

ES32Framebuffer::~ES32Framebuffer()
{

}

OpenGLTexture *ES32Framebuffer::CreateTexture(RHIDevice *Device, RHIPixelFormat Format, std::uint32_t Width, std::uint32_t Height)
{
    return new ES32Texture(Device, RHITextureType::Texture2D, Format, 1, 1, Width, Height, 1, nullptr);
}




