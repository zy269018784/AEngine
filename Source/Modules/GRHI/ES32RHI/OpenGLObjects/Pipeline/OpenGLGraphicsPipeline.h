#pragma once
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLPipeline.h"

class OpenGLGraphicsPipeline : public RHIGraphicsPipeline
{
public:
	OpenGLGraphicsPipeline();
	virtual ~OpenGLGraphicsPipeline();
	virtual GLuint GetVAO() final;
	virtual int BindVAO() = 0;
	virtual int UnbindVAO() = 0;
public:
	virtual void Create() final override;
protected:
	GLuint VAO;
public:
	GLint Handle;
};