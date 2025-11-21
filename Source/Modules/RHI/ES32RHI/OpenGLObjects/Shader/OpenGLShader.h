#pragma once
#include <ES32.h>
#include "RHIObjects/Shader/RHIShader.h"

class OpenGLShader : public RHIShader
{
public:
	OpenGLShader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~OpenGLShader();
//private:
	GLuint  Handle;
};
