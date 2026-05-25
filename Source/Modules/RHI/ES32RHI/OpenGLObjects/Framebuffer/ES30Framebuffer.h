#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"
#include <vector>

class OpenGLDevice;
class OpenGLTexture;
class ES30Framebuffer
{
public:
    ES30Framebuffer();
    ES30Framebuffer(std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIColorAttachment *> &InColorAttachments,
                      std::vector<RHIDepthAttachment *> &InDepthAttachments);
    ~ES30Framebuffer();
    GLuint GetHandle() const;
 private:
    GLuint Handle;
    std::vector<OpenGLTexture *> ColorTextures;
    std::vector<OpenGLTexture *> DepthTextures;
};