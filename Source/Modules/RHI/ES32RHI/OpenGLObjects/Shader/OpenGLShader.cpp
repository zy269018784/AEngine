#include "OpenGLShader.h"
#include "OpenGLObjects/Core/OpenGLCore.h"
#include <iostream>
//GLenum ToOpenGLShaderType(RHIShaderType Type)
//{
//	GLenum ShaderType;
//	switch (Type)
//	{
//	case RHIShaderType::Vertex:
//		ShaderType = GL_VERTEX_SHADER;
//		break;
//	case RHIShaderType::TessellationControl:
//		ShaderType = GL_TESS_CONTROL_SHADER;
//		break;
//	case RHIShaderType::TessellationEvaluation:
//		ShaderType = GL_TESS_EVALUATION_SHADER;
//		break;
//	case RHIShaderType::Fragment:
//		ShaderType = GL_FRAGMENT_SHADER;
//		break;
//	case RHIShaderType::Compute:
//		ShaderType = GL_COMPUTE_SHADER;
//		break;
//	case RHIShaderType::Geometry:
//		ShaderType = GL_GEOMETRY_SHADER;
//		break;
//	default:
//		break;
//	}
//	return ShaderType;
//}
#if 0
OpenGLShader::OpenGLShader(RHIShaderType Type, std::uint32_t* Code, std::size_t CodeSize)
	: RHIShader(Type, Code, CodeSize)
{
	GLenum ShaderType = ToOpenGLShaderType(Type);


	const GLchar* p = (const char*)Code;
	//std::cout << "p "  << p << std::endl;
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
#else
OpenGLShader::OpenGLShader(RHIShaderType Type, std::uint32_t* Code, std::size_t CodeSize)
	: RHIShader(Type, Code, CodeSize)
{
	GLenum ShaderType = ToOpenGLShaderType(Type);


	const GLchar* p = (const char*)Code;
	//std::cout << "p "  << p << std::endl;
	Handle = glCreateShader(ShaderType);

	//glShaderSource(Handle, 1, &p, nullptr);
	//glCompileShader(Handle);

	// 3. Load the SPIR-V binary into the shader objects
	glShaderBinary(1, &Handle, GL_SHADER_BINARY_FORMAT_SPIR_V,
		Code, CodeSize);

	// 4. Specialize the shaders (this is crucial!)
	// This tells the driver which entry point to use from the SPIR-V module.
	// For GLSL-originated SPIR-V, this is almost always "main".
	glSpecializeShader(Handle, "main", 0, nullptr, nullptr);

	std::cout << "glShaderBinary " << CodeSize << std::endl;

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
#endif
OpenGLShader::~OpenGLShader()
{
	glDeleteShader(Handle);
}

GLuint OpenGLShader::GetHandle() const {
	return  Handle;
}