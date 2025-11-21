#include "OpenGLShader.h"
#include <iostream>
GLenum ToOpenGLShaderType(RHIShader::Type Type)
{
	GLenum ShaderType;
	switch (Type)
	{
	case RHIShader::Vertex:
		ShaderType = GL_VERTEX_SHADER;
		break;
	case RHIShader::TessellationControl:
		break;
	case RHIShader::TessellationEvaluation:
		break;
	case RHIShader::Fragment:
		ShaderType = GL_FRAGMENT_SHADER;
		break;
	case RHIShader::Compute:
		break;
	case RHIShader::Geometry:
		break;
	default:
		break;
	}
	return ShaderType;
}

OpenGLShader::OpenGLShader(RHIShader::Type Type, std::uint32_t* Code, std::size_t CodeSize)
	: RHIShader(Type, Code, CodeSize)
{
	GLenum ShaderType = ToOpenGLShaderType(Type);
	Handle = glCreateShader(ShaderType);
	glShaderSource(Handle, 1, (const GLchar**)Code, nullptr);
	glCompileShader(Handle);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Handle, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

OpenGLShader::~OpenGLShader()
{
	glDeleteShader(Handle);
}