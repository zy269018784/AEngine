#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

class ES30Shader : public OpenGLShader
{
public:
	ES30Shader(RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~ES30Shader();
};
