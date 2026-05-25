#pragma once
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"

class ES30GraphicsPipeline : public OpenGLGraphicsPipeline
{
public:
	ES30GraphicsPipeline();
	~ES30GraphicsPipeline();
	virtual int BindVAO() final override;
	virtual int UnbindVAO() final override;
};