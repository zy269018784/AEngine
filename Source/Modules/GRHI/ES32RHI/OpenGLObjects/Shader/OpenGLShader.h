#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Shader/RHIShader.h"

class OpenGLShader : public RHIShader
{
public:
	OpenGLShader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	virtual ~OpenGLShader();
	GLuint  GetHandle() const;
protected:
	GLuint  Handle;
};
