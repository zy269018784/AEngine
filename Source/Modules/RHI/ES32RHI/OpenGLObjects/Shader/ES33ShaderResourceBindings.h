#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class ES33ShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	ES33ShaderResourceBindings(OpenGLDevice* Device);
	~ES33ShaderResourceBindings();
	virtual void Create() final override;
};
