#include "RHIPipeline.h"

void RHIPipeline::SetShaderResourceBindings(RHIShaderResourceBindings* srb)
{
	ShaderResourceBindings = srb;
}

void RHIPipeline::SetShaderStages(std::initializer_list<RHIShader*> list)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
		Shaders.push_back(*iter);
}

