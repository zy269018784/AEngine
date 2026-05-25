#include "ES32RHI/OpenGLObjects/Pipeline/OpenGL46GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"
#include <iostream>

OpenGL46GraphicsPipeline::OpenGL46GraphicsPipeline()
	: OpenGLGraphicsPipeline()
{
	glGenVertexArrays(1, &VAO);
}

OpenGL46GraphicsPipeline::~OpenGL46GraphicsPipeline()
{
	glDeleteVertexArrays(1, &VAO);
}

int OpenGL46GraphicsPipeline::BindVAO()
{
	glBindVertexArray(VAO);
	return 0;
}

int OpenGL46GraphicsPipeline::UnbindVAO()
{
	glBindVertexArray(0);
	return 0;
}

