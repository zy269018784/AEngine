#pragma once
#include "RHIObjects/Core/RHICore.h"
#include <map>
class RHIPhysicalDevice
{
public:
    RHIPhysicalDevice();
    virtual ~RHIPhysicalDevice();
    bool IsVertexShaderSupported();
    bool IsFragmentShaderSupported();
    bool IsComputeShaderSupported();
    bool IsGeometryShaderSupported();
    bool IsTessellationControlShaderSupported();
    bool IsTessellationEvaluationShaderSupported();
    bool IsTexture1DSupported();
    bool IsTexture2DSupported();
    bool IsTexture3DSupported();
    bool IsTextureCubeMapSupported();
    bool IsTexture1DArraySupported();
    bool IsTexture2DArraySupported();
    bool IsTexture3DArraySupported();
    bool IsTextureCubeMapArraySupported();
    bool IsDepthBoundsTestSupported();
    bool IsMultiViewportSupported();
protected:
    virtual void InitFeatures() =0;
protected:
    std::map<std::uint32_t, bool> Features;
};

