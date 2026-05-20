#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class ES32ShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	ES32ShaderResourceBindings(OpenGLDevice* Device);
	~ES32ShaderResourceBindings();
	virtual void Create() final override;
};
