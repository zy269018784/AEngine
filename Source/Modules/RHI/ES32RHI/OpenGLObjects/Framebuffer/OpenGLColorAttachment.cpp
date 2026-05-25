#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGLColorAttachment.h"

OpenGLColorAttachment::OpenGLColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat)
    : RHIColorAttachment(InType, InPixelFormat)
{

}

OpenGLColorAttachment::~OpenGLColorAttachment()
{

}
#if 0
GLuint OpenGLColorAttachment::GetHandle() const
{
    return Texture->GetHandle();
}
#endif




