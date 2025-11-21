#include "OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"
#include "OpenGLObjects/Shader/OpenGLShader.h"
#include "ES32Translate.h"
#include <iostream>

OpenGLGraphicsPipeline::OpenGLGraphicsPipeline()
{
	glGenVertexArrays(1, &VAO);
	//UnbindVAO();
}

OpenGLGraphicsPipeline::~OpenGLGraphicsPipeline()
{
	glDeleteVertexArrays(1, &VAO);
}

int OpenGLGraphicsPipeline::BindVAO()
{
	//std::cout << "BindVAO " << VAO << std::endl;
	glBindVertexArray(VAO);
	return 0;
}

int OpenGLGraphicsPipeline::UnbindVAO()
{
	glBindVertexArray(0);
	return 0;
}

GLuint OpenGLGraphicsPipeline::GetVAO()
{
	return VAO;
}

void OpenGLGraphicsPipeline::Create()
{
	//Handle = glCreateProgram();
	for (int i = 0; i < Shaders.size(); i++)
	{
		glAttachShader(Handle, ((OpenGLShader *)Shaders[i])->Handle);
	}
	glLinkProgram(Handle);

	int success;
	char infoLog[512];
	glGetProgramiv(Handle, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Handle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

