#pragma once
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"

class ES31GraphicsPipeline : public OpenGLGraphicsPipeline
{
public:
	ES31GraphicsPipeline();
	~ES31GraphicsPipeline();
	virtual int BindVAO() final override;
	virtual int UnbindVAO() final override;
};