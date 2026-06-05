#pragma once
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"

class ES32GraphicsPipeline : public OpenGLGraphicsPipeline
{
public:
	ES32GraphicsPipeline();
	~ES32GraphicsPipeline();
	virtual int BindVAO() final override;
	virtual int UnbindVAO() final override;
};