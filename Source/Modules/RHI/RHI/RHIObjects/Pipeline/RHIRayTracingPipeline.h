#pragma once
#include "RHIObjects/Pipeline/RHIPipeline.h"
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "RHIObjects/Shader/RHIShader.h"

class RHIRayTracingPipeline : public RHIPipeline
{
public:
	RHIRayTracingPipeline() = default;
	virtual ~RHIRayTracingPipeline() = default;
};