#pragma once
#include <OpenGL330.h>
#include <RHIObjects/RHIShader.h>

class OpenGLShader : public RHIShader
{
public:
	OpenGLShader(RHIShader::Type type, std::uint32_t* Code, std::size_t CodeSize);
	~OpenGLShader();
//private:
	GLint Handle;
};

GLenum ToOpenGLShaderType(RHIShader::Type Type);