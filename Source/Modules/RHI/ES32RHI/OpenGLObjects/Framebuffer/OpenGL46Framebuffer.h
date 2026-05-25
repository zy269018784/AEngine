#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLFramebuffer.h"
#include "RHI/RHIObjects/Device/RHIDevice.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
#include <vector>

class OpenGLDevice;
class OpenGLTexture;
class OpenGL46Framebuffer : public OpenGLFramebuffer
{
public:
    OpenGL46Framebuffer() = delete;
    OpenGL46Framebuffer(OpenGLDevice *InDevice, std::uint32_t Width, std::uint32_t Height,
                      std::vector<RHIColorAttachment *> &InColorAttachments,
                      std::vector<RHIDepthAttachment *> &InDepthAttachments);
    ~OpenGL46Framebuffer();
};