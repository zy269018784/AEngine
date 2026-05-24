#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

class ES21Shader : public OpenGLShader
{
public:
	ES21Shader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~ES21Shader();
};
