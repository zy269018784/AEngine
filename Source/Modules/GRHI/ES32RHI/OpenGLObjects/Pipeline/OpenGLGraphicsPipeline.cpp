#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"
#include <iostream>

OpenGLGraphicsPipeline::OpenGLGraphicsPipeline()
{
	//glGenVertexArrays(1, &VAO);
}

OpenGLGraphicsPipeline::~OpenGLGraphicsPipeline()
{
	//glDeleteVertexArrays(1, &VAO);
}


GLuint OpenGLGraphicsPipeline::GetVAO()
{
	return VAO;
}

void OpenGLGraphicsPipeline::Create()
{
	Handle = glCreateProgram();
	for (int i = 0; i < Shaders.size(); i++)
	{
		glAttachShader(Handle, ((OpenGLShader *)Shaders[i])->GetHandle());
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

