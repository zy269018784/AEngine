#pragma once
#include "RHI/RHIObjects/Pipeline/RHIPipeline.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "RHI/RHIObjects/Shader/RHIShader.h"

class RHIRayTracingPipeline : public RHIPipeline
{
public:
	RHIRayTracingPipeline() = default;
	virtual ~RHIRayTracingPipeline() = default;
};