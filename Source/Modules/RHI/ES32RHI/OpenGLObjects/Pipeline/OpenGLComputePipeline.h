#pragma once
#include "RHI/RHIObjects/Pipeline/RHIComputePipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLPipeline.h"

class OpenGLComputePipeline : public RHIComputePipeline, public OpenGLPipeline
{

};