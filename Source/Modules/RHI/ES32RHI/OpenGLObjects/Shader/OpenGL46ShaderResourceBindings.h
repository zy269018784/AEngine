#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class OpenGL46ShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	OpenGL46ShaderResourceBindings(OpenGLDevice* Device);
	~OpenGL46ShaderResourceBindings();
	virtual void Create() final override;
};
