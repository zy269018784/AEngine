#include "OpenGL33Shader.h"
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include <iostream>

OpenGL33Shader::OpenGL33Shader(RHIShaderType Type, std::uint32_t* Code, std::size_t CodeSize)
	: OpenGLShader(Type, Code, CodeSize)
{
	GLenum ShaderType = ToOpenGLShaderType(Type);
	const GLchar* p = (const char*)Code;

	Handle = glCreateShader(ShaderType);
	glShaderSource(Handle, 1, &p, nullptr);
	glCompileShader(Handle);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Handle, 512, nullptr, infoLog);
		std::cout << "glCompileShader log: \n" << infoLog << std::endl;
	}
}

OpenGL33Shader::~OpenGL33Shader()
{
	glDeleteShader(Handle);
}

