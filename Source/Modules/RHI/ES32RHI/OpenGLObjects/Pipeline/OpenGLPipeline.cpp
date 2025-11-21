#include "OpenGLObjects/Pipeline/OpenGLPipeline.h"


OpenGLPipeline::OpenGLPipeline()
{
	Handle = glCreateProgram();
}

OpenGLPipeline::~OpenGLPipeline()
{
	glDeleteProgram(Handle);
}