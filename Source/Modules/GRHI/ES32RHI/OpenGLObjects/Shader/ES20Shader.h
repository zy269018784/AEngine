#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

class ES20Shader : public OpenGLShader
{
public:
	ES20Shader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~ES20Shader();
};
