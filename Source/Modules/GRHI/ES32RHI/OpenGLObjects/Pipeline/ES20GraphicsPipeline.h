#pragma once
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"

class ES20GraphicsPipeline : public OpenGLGraphicsPipeline
{
public:
	ES20GraphicsPipeline();
	~ES20GraphicsPipeline();
	virtual int BindVAO() final override;
	virtual int UnbindVAO() final override;
};