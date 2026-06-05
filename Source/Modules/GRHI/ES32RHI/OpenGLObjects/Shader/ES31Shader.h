#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

class ES31Shader : public OpenGLShader
{
public:
	ES31Shader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~ES31Shader();
};
