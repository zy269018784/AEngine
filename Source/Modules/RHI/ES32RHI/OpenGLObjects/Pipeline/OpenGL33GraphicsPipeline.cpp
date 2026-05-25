#include "ES32RHI/OpenGLObjects/Pipeline/OpenGL33GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"
#include <iostream>

OpenGL33GraphicsPipeline::OpenGL33GraphicsPipeline()
{
	glGenVertexArrays(1, &VAO);
	//UnbindVAO();
}

OpenGL33GraphicsPipeline::~OpenGL33GraphicsPipeline()
{
	glDeleteVertexArrays(1, &VAO);
}

int OpenGL33GraphicsPipeline::BindVAO()
{
	//std::cout << "BindVAO " << VAO << std::endl;
	glBindVertexArray(VAO);
	return 0;
}

int OpenGL33GraphicsPipeline::UnbindVAO()
{
	glBindVertexArray(0);
	return 0;
}

