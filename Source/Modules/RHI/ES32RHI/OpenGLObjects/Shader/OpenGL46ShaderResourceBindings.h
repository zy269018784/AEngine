#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
class OpenGLDevice;
class OpenGLTexture;
class OpenGLSampler;
class OpenGL46ShaderResourceBindings : public OpenGLShaderResourceBindings
{
public:
	OpenGL46ShaderResourceBindings(OpenGLDevice* Device);
	~OpenGL46ShaderResourceBindings();
	virtual void CreateUBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateSSBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) override final;
};
