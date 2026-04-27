#pragma once
#include "ES32.h"
#include "RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHIObjects/Texture/RHITexture.h"
#include "OpenGLObjects/Texture/OpenGLTexture.h"
class OpenGLColorAttachment : public RHIColorAttachment
{
public:
    OpenGLColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    ~OpenGLColorAttachment();
    GLuint GetHandle() const;
private:
    OpenGLTexture *Texture;
};

