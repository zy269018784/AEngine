#pragma once
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"

class OpenGL46GraphicsPipeline : public OpenGLGraphicsPipeline
{
public:
	OpenGL46GraphicsPipeline();
	~OpenGL46GraphicsPipeline();
	virtual int BindVAO() final override;
	virtual int UnbindVAO() final override;
};