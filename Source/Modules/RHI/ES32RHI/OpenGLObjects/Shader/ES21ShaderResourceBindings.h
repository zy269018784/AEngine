#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class ES21ShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	ES21ShaderResourceBindings(OpenGLDevice* Device);
	~ES21ShaderResourceBindings();
	virtual void Create() final override;
};
