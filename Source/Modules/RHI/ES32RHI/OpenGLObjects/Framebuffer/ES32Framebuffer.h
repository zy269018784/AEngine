#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"
#include <vector>

class OpenGLDevice;
class OpenGLTexture;
class ES32Framebuffer
{
public:
    ES32Framebuffer();
    ES32Framebuffer(std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIColorAttachment *> &InColorAttachments,
                      std::vector<RHIDepthAttachment *> &InDepthAttachments);
    ~ES32Framebuffer();
    GLuint GetHandle() const;
 private:
    GLuint Handle;
    std::vector<OpenGLTexture *> ColorTextures;
    std::vector<OpenGLTexture *> DepthTextures;
};