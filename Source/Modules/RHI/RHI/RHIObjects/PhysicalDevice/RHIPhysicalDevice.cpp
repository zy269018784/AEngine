#include "RHIPhysicalDevice.h"

RHIPhysicalDevice::RHIPhysicalDevice()
{
    Features[static_cast<std::uint32_t>(RHIFeatures::VertexShader)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::FragmentShader)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::ComputeShader)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::GeometryShader)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::TessellationControlShader)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::TessellationEvaluationShader)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::Texture1D)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::Texture2D)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::Texture3D)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::TextureCubeMap)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::Texture1DArray)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::Texture2DArray)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::Texture3DArray)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::TextureCubeMapArray)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::DepthBoundsTest)] = true;
    Features[static_cast<std::uint32_t>(RHIFeatures::MultiViewport)] = true;
}

RHIPhysicalDevice::~RHIPhysicalDevice()
{

}

// Shader Features 查询函数实现
bool RHIPhysicalDevice::IsFragmentShaderSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::FragmentShader)];
}

bool RHIPhysicalDevice::IsComputeShaderSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::ComputeShader)];
}

bool RHIPhysicalDevice::IsGeometryShaderSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::GeometryShader)];
}

bool RHIPhysicalDevice::IsTessellationControlShaderSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::TessellationControlShader)];
}

bool RHIPhysicalDevice::IsTessellationEvaluationShaderSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::TessellationEvaluationShader)];
}

// Texture Features 查询函数实现
bool RHIPhysicalDevice::IsTexture1DSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::Texture1D)];
}

bool RHIPhysicalDevice::IsTexture2DSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::Texture2D)];
}

bool RHIPhysicalDevice::IsTexture3DSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::Texture3D)];
}

bool RHIPhysicalDevice::IsTextureCubeMapSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::TextureCubeMap)];
}

bool RHIPhysicalDevice::IsTexture1DArraySupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::Texture1DArray)];
}

bool RHIPhysicalDevice::IsTexture2DArraySupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::Texture2DArray)];
}

bool RHIPhysicalDevice::IsTexture3DArraySupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::Texture3DArray)];
}

bool RHIPhysicalDevice::IsTextureCubeMapArraySupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::TextureCubeMapArray)];
}

// Depth Features 查询函数实现
bool RHIPhysicalDevice::IsDepthBoundsTestSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::DepthBoundsTest)];
}

// Viewport Features 查询函数实现
bool RHIPhysicalDevice::IsMultiViewportSupported()
{
    return Features[static_cast<std::uint32_t>(RHIFeatures::MultiViewport)];
}