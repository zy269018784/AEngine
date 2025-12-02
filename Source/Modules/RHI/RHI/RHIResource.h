#pragma once

enum RHIResourceType
{
	RRT_None,
	RRT_VertexAttributeState,
	RRT_RasterizerState,
	RRT_BoundShaderState,
	RRT_ViewportState,
	RRT_DepthStencilState,
	RRT_DepthRangeState,
	RRT_BlendState,
	RRT_ScissorState,
	RRT_SamplerState,
	RRT_GraphicsPipelineState,
	RRT_ComputePipelineState,
	RRT_RayTracingPipelineState,

	RRT_VertexDeclaration,

	RRT_Shader,
	RRT_VertexShader,
	RRT_MeshShader,
	RRT_AmplificationShader,
	RRT_PixelShader,
	RRT_GeometryShader,
	RRT_RayTracingShader,
	RRT_ComputeShader,

	RRT_Texture,
	RRT_Texture2D,
	RRT_Texture2DArray,
	RRT_Texture3D,
	RRT_TextureCube,
	RRT_TextureCubeArray,
	RRT_TextureReference,

	RRT_Buffer,
	RRT_UniformBufferLayout,
	RRT_UniformBuffer,

	RRT_Num
};


class RHIResource
{
public:
	RHIResource()
		: ResourceType(RRT_None)
	{
	}

	RHIResource(RHIResourceType InResourceType)
		: ResourceType(InResourceType)
	{
	}

	virtual ~RHIResource()
	{
	}
private:
	const RHIResourceType ResourceType;
};