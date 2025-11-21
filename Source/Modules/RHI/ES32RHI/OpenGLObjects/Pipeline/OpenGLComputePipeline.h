#pragma once
#include <OpenGLObjects/Pipeline/OpenGLPipeline.h>
#include "RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHIObjects/Shader/RHIShader.h"

class OpenGLComputePipeline : public RHIGraphicsPipeline, public OpenGLPipeline
{

};