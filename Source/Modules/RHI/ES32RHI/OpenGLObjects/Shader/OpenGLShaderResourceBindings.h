#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class OpenGLShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	OpenGLShaderResourceBindings(OpenGLDevice* Device);
	~OpenGLShaderResourceBindings();
	virtual void Create() final override;
};
