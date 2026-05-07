#pragma once
#include <ES32.h>
#include "RHI/RHIObjects/Pipeline/RHIPipeline.h"
class OpenGLPipeline
{
public:
	OpenGLPipeline();
	virtual ~OpenGLPipeline();
public:
	GLint Handle;
};