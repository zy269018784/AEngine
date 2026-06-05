#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

class ES32Shader : public OpenGLShader
{
public:
	ES32Shader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~ES32Shader();
};
