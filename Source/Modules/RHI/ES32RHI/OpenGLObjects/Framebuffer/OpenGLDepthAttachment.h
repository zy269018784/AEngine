#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
class OpenGLDepthAttachment : public RHIDepthAttachment
{
public:
    OpenGLDepthAttachment(RHIDepthAttachmentType InType);
    ~OpenGLDepthAttachment();
    GLuint GetHandle() const;
private:
    OpenGLTexture *Texture;
};