#pragma once
#include "OpenGL.h"
#include "RHIObjects/RenderPass/RHIColorAttachment.h"

class OpenGLColorAttachment : public RHIColorAttachment
{
public:
    OpenGLColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    ~OpenGLColorAttachment();
};

