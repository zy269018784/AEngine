#include "ES32RHI/OpenGLObjects/Pipeline/ES31GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"
#include <iostream>

ES31GraphicsPipeline::ES31GraphicsPipeline()
{
	glGenVertexArrays(1, &VAO);
	//UnbindVAO();
}

ES31GraphicsPipeline::~ES31GraphicsPipeline()
{
	glDeleteVertexArrays(1, &VAO);
}

int ES31GraphicsPipeline::BindVAO()
{
	//std::cout << "BindVAO " << VAO << std::endl;
	glBindVertexArray(VAO);
	return 0;
}

int ES31GraphicsPipeline::UnbindVAO()
{
	glBindVertexArray(0);
	return 0;
}
