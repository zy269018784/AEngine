#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class ES30ShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	ES30ShaderResourceBindings(OpenGLDevice* Device);
	~ES30ShaderResourceBindings();
	virtual void Create() final override;
};
