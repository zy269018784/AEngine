#pragma once
#include "RHI/RHIExport.h"
#include <vector>

class RHIShader;
class RHIShaderResourceBindings;
class RHIEXPORT RHIPipeline
{
public:
	//enum RHIPipelineType
	//{
	//	GraphicsPipeline = 0x1 << 1,
	//	ComputePipeline = 0x1 << 2,
	//};
	RHIPipeline() = default;
	virtual ~RHIPipeline() = default;
	/*
		Shader
	*/
	void SetShaderStages(std::initializer_list<RHIShader*> list);

	void SetShaderResourceBindings(RHIShaderResourceBindings* srb);
public:
	virtual void Create() = 0;
protected:
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

