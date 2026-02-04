#pragma once
#include "RHIObjects/Core/RHICore.h"
#include <map>
class RHIPhysicalDevice
{
public:
    RHIPhysicalDevice();
    virtual ~RHIPhysicalDevice();

    bool IsVertexShaderSupported() const;
    bool IsFragmentShaderSupported() const;
    bool IsComputeShaderSupported() const;
    bool IsGeometryShaderSupported() const;
    bool IsTessellationControlShaderSupported() const;
    bool IsTessellationEvaluationShaderSupported() const;

    bool IsTexture1DSupported() const;
    bool IsTexture2DSupported() const;
    bool IsTexture3DSupported() const;
    bool IsTextureCubeMapSupported() const;
    bool IsTexture1DArraySupported() const;
    bool IsTexture2DArraySupported() const;
    bool IsTexture3DArraySupported() const;
    bool IsTextureCubeMapArraySupported() const;

    bool IsDepthBoundsTestSupported() const;

    bool IsMultiViewportSupported() const;
protected:
    std::map<std::uint32_t, bool> Features;
};

