#pragma once
#include "ES32.h"
#include "RHIObjects/FrameBuffer/RHIDepthAttachment.h"
#include "OpenGLObjects/Texture/OpenGLTexture.h"
class OpenGLDepthAttachment : public RHIDepthAttachment
{
public:
    OpenGLDepthAttachment(RHIDepthAttachmentType InType);
    ~OpenGLDepthAttachment();
    GLuint GetHandle() const;
private:
    OpenGLTexture *Texture;
};