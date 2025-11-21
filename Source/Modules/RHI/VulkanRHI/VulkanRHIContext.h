#pragma once
#include <State/VulkanRasterizationState.h>
#include <State/VulkanDepthStencilState.h>    
#include <State/VulkanBlendState.h>
#include <State/VulkanVertexAttributeState.h>
#include <State/VulkanBoundShaderState.h>
#include <State/VulkanViewportState.h>	
#include <State/VulkanScissorState.h>

struct VulkanRHIState
{
	VulkanRasterizationState			RasterizerState;
	VulkanDepthStencilState	    	DepthStencilState;
	VulkanBlendState				BlendState;
	VulkanVertexAttributeState		VertexAttributeState;
	VulkanBoundShaderState			BoundShaderState;
	VulkanViewportState				ViewportState;
	VulkanScissorState				ScissorState;
};