#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Pipeline/RHIPipeline.h"

class RHIEXPORT RHIRayTracingPipeline : public RHIPipeline
{
public:
	RHIRayTracingPipeline() = default;
	virtual ~RHIRayTracingPipeline() = default;
};