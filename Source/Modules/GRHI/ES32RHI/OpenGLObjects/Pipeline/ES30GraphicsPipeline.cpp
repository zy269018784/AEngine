#include "ES32RHI/OpenGLObjects/Pipeline/ES30GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"
#include <iostream>

ES30GraphicsPipeline::ES30GraphicsPipeline()
{
	glGenVertexArrays(1, &VAO);
	//UnbindVAO();
}

ES30GraphicsPipeline::~ES30GraphicsPipeline()
{
	glDeleteVertexArrays(1, &VAO);
}

int ES30GraphicsPipeline::BindVAO()
{
	//std::cout << "BindVAO " << VAO << std::endl;
	glBindVertexArray(VAO);
	return 0;
}

int ES30GraphicsPipeline::UnbindVAO()
{
	glBindVertexArray(0);
	return 0;
}

