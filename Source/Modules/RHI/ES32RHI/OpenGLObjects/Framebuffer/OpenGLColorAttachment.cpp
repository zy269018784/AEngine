#include "OpenGLColorAttachment.h"

OpenGLColorAttachment::OpenGLColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat)
    : RHIColorAttachment(InType, InPixelFormat)
{

}

OpenGLColorAttachment::~OpenGLColorAttachment()
{

}

GLuint OpenGLColorAttachment::GetHandle() const
{
    return Texture->GetHandle();
}





