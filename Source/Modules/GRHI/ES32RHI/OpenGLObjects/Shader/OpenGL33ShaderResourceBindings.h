#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
class OpenGLDevice;
class OpenGL33ShaderResourceBindings : public OpenGLShaderResourceBindings
{
public:
	OpenGL33ShaderResourceBindings(OpenGLDevice* Device);
	~OpenGL33ShaderResourceBindings();
	virtual void CreateUBO(int BindingPoint,  OpenGLBuffer *Buffer) override final;
	virtual void CreateSSBO(int BindingPoint, OpenGLBuffer *Buffer) override final;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) override final;
};
