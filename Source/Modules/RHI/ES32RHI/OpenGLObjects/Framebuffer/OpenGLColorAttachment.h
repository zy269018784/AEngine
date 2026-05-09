#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
class OpenGLColorAttachment : public RHIColorAttachment
{
public:
    OpenGLColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    ~OpenGLColorAttachment();
    GLuint GetHandle() const;
private:
    OpenGLTexture *Texture;
};

