#include "OpenGL46Shader.h"
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include <iostream>

OpenGL46Shader::OpenGL46Shader(RHIShaderType Type, std::uint32_t* Code, std::size_t CodeSize)
	: OpenGLShader(Type, Code, CodeSize)
{
	GLenum ShaderType = ToOpenGLShaderType(Type);

	Handle = glCreateShader(ShaderType);

	// 3. Load the SPIR-V binary into the shader objects
	glShaderBinary(1, &Handle, GL_SHADER_BINARY_FORMAT_SPIR_V, Code, CodeSize);

	// 4. Specialize the shaders (this is crucial!)
	// This tells the driver which entry point to use from the SPIR-V module.
	// For GLSL-originated SPIR-V, this is almost always "main".
	glSpecializeShader(Handle, "main", 0, nullptr, nullptr);

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


OpenGL46Shader::~OpenGL46Shader()
{
	glDeleteShader(Handle);
}
