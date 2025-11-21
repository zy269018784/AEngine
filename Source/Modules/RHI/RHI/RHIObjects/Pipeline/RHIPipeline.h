#pragma once
#include "RHIObjects/Shader/RHIShader.h"
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
#include <vector>

class RHIPipeline
{
public:
	enum RHIPipelineType
	{
		GraphicsPipeline = 0x1 << 1,
		ComputePipeline = 0x1 << 2,
	};
	RHIPipeline() = default;
	virtual ~RHIPipeline() = default;
	/*
		Shader
	*/
	void SetShaderStages(std::initializer_list<RHIShader*> list);

	void SetShaderResourceBindings(RHIShaderResourceBindings* srb);
public:
	virtual void Create() = 0;

public:
	/*
		Shader
	*/
	std::vector<RHIShader*>				Shaders;
	/*
		Shader	Resource	Bindings
	*/
	RHIShaderResourceBindings* ShaderResourceBindings = nullptr;
};

