#pragma once
#include <OpenGL330.h>
#include "RHIObjects/Shader/RHIShader.h"
#include  "RHIObjects/Core/RHICore.h"
class OpenGLShader : public RHIShader
{
public:
	OpenGLShader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~OpenGLShader();
//private:
	GLint Handle;
};

GLenum ToOpenGLShaderType(RHIShaderType Type);