#pragma once
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "OpenGLObjects/Device/OpenGLDevice.h"
class OpenGLShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	OpenGLShaderResourceBindings(OpenGLDevice* Device);
	~OpenGLShaderResourceBindings();
	virtual void Create() final override;
};
