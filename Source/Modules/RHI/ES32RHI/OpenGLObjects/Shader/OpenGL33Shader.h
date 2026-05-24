#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

class OpenGL33Shader : public OpenGLShader
{
public:
	OpenGL33Shader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~OpenGL33Shader();
};
