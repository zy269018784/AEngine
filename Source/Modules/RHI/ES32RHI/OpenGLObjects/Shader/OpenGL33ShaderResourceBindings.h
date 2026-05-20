#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class OpenGL33ShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	OpenGL33ShaderResourceBindings(OpenGLDevice* Device);
	~OpenGL33ShaderResourceBindings();
	virtual void Create() final override;
};
