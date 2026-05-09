#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"
#include <vector>
class OpenGLFramebuffer
{
public:
    OpenGLFramebuffer();
    OpenGLFramebuffer(std::vector<RHIColorAttachment *> &InColorAttachments, std::vector<RHIDepthAttachment *> &InDepthAttachments);
    ~OpenGLFramebuffer();
    GLuint GetHandle() const;
 private:
    GLuint Handle;
};