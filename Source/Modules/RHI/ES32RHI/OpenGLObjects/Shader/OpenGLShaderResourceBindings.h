#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"

class OpenGLTexture;
class OpenGLSampler;
class OpenGLDevice;
class OpenGLBuffer;
class OpenGLShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	OpenGLShaderResourceBindings(OpenGLDevice* Device);
	~OpenGLShaderResourceBindings();
public:
	virtual void Create() final override;
	virtual void Bind() final override;
public:
	virtual void CreateUBO(int BindingPoint,  OpenGLBuffer *Buffer) = 0;
	virtual void CreateSSBO(int BindingPoint, OpenGLBuffer *Buffer) = 0;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) = 0;
protected:
	int MaxUBOBindings  = 0;
	int MaxSSBOBindings = 0;
	int MaxTextureUnits = 0;
};
