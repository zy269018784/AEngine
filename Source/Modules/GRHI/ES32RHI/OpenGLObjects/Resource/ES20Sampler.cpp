#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include "ES32RHI/OpenGLObjects/Resource/ES20Sampler.h"

ES20Sampler::ES20Sampler(OpenGLDevice* InDevice, RHIFilter InMinFilter, RHIFilter InMagFilter, RHIAddressMode InAddressModeU, RHIAddressMode InAddressModeV, RHIAddressMode InAddressModeW)
: OpenGLSampler(InDevice, InMinFilter, InMagFilter, InAddressModeU, InAddressModeV, InAddressModeW)
{
}


ES20Sampler::~ES20Sampler()
{

}

void ES20Sampler::BindTextureUnit(int Unit)
{

}