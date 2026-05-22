#pragma once
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"

class OpenGLTexture;
class OpenGLSampler;
class OpenGLDevice;
class OpenGLShaderResourceBindings : public RHIShaderResourceBindings
{
public:
	OpenGLShaderResourceBindings(OpenGLDevice* Device);
	~OpenGLShaderResourceBindings();
	virtual void Create() final override;
	virtual void CreateUBO(int BindingPoint, GLuint Handle) = 0;
	virtual void CreateSSBO(int BindingPoint, GLuint Handle) = 0;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) = 0;
protected:
	int MaxUBOBindings  = 0;
	int MaxSSBOBindings = 0;
	int MaxTextureUnits = 0;
};
