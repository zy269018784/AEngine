#include "ES32RHI/OpenGLObjects/Pipeline/ES32GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"
#include <iostream>

ES32GraphicsPipeline::ES32GraphicsPipeline()
{
	glGenVertexArrays(1, &VAO);
	//UnbindVAO();
}

ES32GraphicsPipeline::~ES32GraphicsPipeline()
{
	glDeleteVertexArrays(1, &VAO);
}

int ES32GraphicsPipeline::BindVAO()
{
	//std::cout << "BindVAO " << VAO << std::endl;
	glBindVertexArray(VAO);
	return 0;
}

int ES32GraphicsPipeline::UnbindVAO()
{
	glBindVertexArray(0);
	return 0;
}
