#pragma once
#include "RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "OpenGLObjects/Pipeline/OpenGLPipeline.h"

class OpenGLGraphicsPipeline : public RHIGraphicsPipeline, public OpenGLPipeline
{
public:
	OpenGLGraphicsPipeline();
	~OpenGLGraphicsPipeline();
	GLuint GetVAO();
	int BindVAO();
	int UnbindVAO();
public:
	virtual void Create() final override;
private:
	GLuint VAO;
};