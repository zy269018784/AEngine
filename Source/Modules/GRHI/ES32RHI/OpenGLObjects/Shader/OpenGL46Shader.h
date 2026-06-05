#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

class OpenGL46Shader : public OpenGLShader
{
public:
	OpenGL46Shader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~OpenGL46Shader();
};
