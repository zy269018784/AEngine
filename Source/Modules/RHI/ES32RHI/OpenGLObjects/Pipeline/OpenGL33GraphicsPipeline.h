#pragma once
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"

class OpenGL33GraphicsPipeline : public OpenGLGraphicsPipeline
{
public:
	OpenGL33GraphicsPipeline();
	~OpenGL33GraphicsPipeline();
	virtual int BindVAO() final override;
	virtual int UnbindVAO() final override;
};