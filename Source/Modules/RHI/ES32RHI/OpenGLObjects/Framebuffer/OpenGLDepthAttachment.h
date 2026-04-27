#pragma once
#include "OpenGL.h"
#include "RHIObjects/RenderPass/RHIDepthAttachment.h"
class OpenGLDepthAttachment : public RHIDepthAttachment
{
public:
    OpenGLDepthAttachment(RHIDepthAttachmentType InType);
    ~OpenGLDepthAttachment();
};