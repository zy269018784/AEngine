#include "RHIObjects/Shader/RHIShader.h"

RHIShader::RHIShader()
{

}

RHIShader::RHIShader(RHIShaderType Type, std::uint32_t* Code, size_t Size)
	: Type_(Type), CodePtr(Code), CodeSize(Size)
	
{

}

RHIShader::~RHIShader()
{

}
