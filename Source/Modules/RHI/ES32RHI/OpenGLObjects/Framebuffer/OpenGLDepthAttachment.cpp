#include "OpenGLDepthAttachment.h"

OpenGLDepthAttachment::OpenGLDepthAttachment(RHIDepthAttachmentType InType)
    : RHIDepthAttachment(InType)
{

}

OpenGLDepthAttachment::~OpenGLDepthAttachment()
{

}


GLuint OpenGLDepthAttachment::GetHandle() const
{
    return Texture->GetHandle();
}
