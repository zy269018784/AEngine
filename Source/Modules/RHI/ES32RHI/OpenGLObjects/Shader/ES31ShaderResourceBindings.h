#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class ES31ShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	ES31ShaderResourceBindings(OpenGLDevice* Device);
	~ES31ShaderResourceBindings();
	virtual void Create() final override;
};
