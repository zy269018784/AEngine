#pragma once
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Core/RHIViewport.h"
#include "RHIObjects/Core/RHIScissor.h"
#include "RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Pipeline/RHIGraphicsPipeline.h"
//#include <utility>



class RHICommandBuffer
{
public:
	using VertexInput = std::pair<RHIBuffer*, std::uint32_t>;
public:
	//// draw primitive
	//virtual void RHIDrawPrimitive(std::uint32_t BaseVertexIndex, std::uint32_t NumPrimitives, std::uint32_t NumInstances) = 0;
	//
	//// draw indexed primitive
	//virtual void RHIDrawIndexedPrimitive(RHIBuffer* IndexBufferRHI, std::int32_t BaseVertexIndex, std::uint32_t FirstInstance, std::uint32_t NumVertices, std::uint32_t StartIndex, std::uint32_t NumPrimitives, std::uint32_t NumInstances) = 0;
	//
	//// draw indexed primitive indirect
	//virtual void RHIDrawIndexedIndirect(RHIBuffer* IndexBufferRHI, RHIBuffer* ArgumentsBufferRHI, std::int32_t DrawArgumentsIndex, std::uint32_t NumInstances) = 0;
	/*
		Draw Commands
	*/
	virtual void RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount = 1, std::uint32_t FirstVertex = 0, std::uint32_t FirstInstance = 0) = 0;

	virtual void RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount = 1, std::int32_t FirstIndex = 0, std::int32_t VertexOffset = 0, std::int32_t FirstInstance = 0) = 0;

	/*
		RenderPass
	*/
	virtual void RHIBeginRenderPass(RHIRenderPass* RenderPass) = 0;

	virtual void RHIEndRenderPass(RHIRenderPass* RenderPass) = 0;

	/*
		EBO 没用到
	*/
	virtual void RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat RHIIndexFormat) = 0;

	/*
		GraphicsPipeline
	*/
	virtual void RHISetGraphicsPipeline(RHIGraphicsPipeline * GraphicsPipeline) = 0;

	/*
		VertexInput
	*/
	virtual void RHISetVertexInput(int startBinding, int bindingCount, const RHICommandBuffer::VertexInput* bindings,
		RHIBuffer* indexBuf, std::uint32_t indexOffset, RHIIndexFormat indexFormat) = 0;

	/*
		glDepthRange和glDepthRangef: RHIViewport::MinDepth和RHIViewport::MaxDepth
	*/
	virtual void RHISetViewport(const RHIViewport& viewport) = 0;

	/*
		Scissor Test
			Vulkan
			vkCmdSetScissor
	*/

	virtual void RHISetScissor(const RHIScissor& scissor) = 0;
	/*
		Stencil	Test
			Vulkan									OpenGL
			vkCmdSetStencilTestEnable				glEnable(GL_STENCIL_TEST)和glDisable(GL_STENCIL_TEST)
			vkCmdSetStencilTestEnableEXT			glEnable(GL_STENCIL_TEST)和glDisable(GL_STENCIL_TEST)
			vkCmdSetStencilOp						glStencilOp和glStencilOpSeparate
			vkCmdSetStencilOpEXT					glStencilOp和glStencilOpSeparate
			vkCmdSetStencilCompareMask				glStencilFunc和glStencilFuncSeparate
			vkCmdSetStencilWriteMask				glStencilMask和glStencilMaskSeparate
			vkCmdSetStencilReference				glStencilFunc和glStencilFuncSeparate													
	*/
	virtual void RHISetStencilTestEnable(RHIBool32 Enable) = 0;

	virtual void RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp, RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp) = 0;

	virtual void RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask) = 0;

	virtual void RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference) = 0;

	/*
		Depth Test
			Vulkan									OpenGL
			vkCmdSetDepthTestEnable					glEnable(GL_DEPTH_TEST)和glDisable(GL_DEPTH_TEST)
			vkCmdSetDepthTestEnableEXT				glEnable(GL_DEPTH_TEST)和glDisable(GL_DEPTH_TEST)
			vkCmdSetDepthCompareOp					glDepthFunc
			vkCmdSetDepthCompareOpEXT				glDepthFunc
			vkCmdSetDepthWriteEnable				glDepthMask
			vkCmdSetDepthWriteEnableEXT				glDepthMask
			vkCmdSetDepthBoundsTestEnable			glEnable(GL_DEPTH_BOUNDS_TEST_EXT)和glDisable(GL_DEPTH_BOUNDS_TEST_EXT)
			vkCmdSetDepthBoundsTestEnableEXT		glEnable(GL_DEPTH_BOUNDS_TEST_EXT)和glDisable(GL_DEPTH_BOUNDS_TEST_EXT)
			vkCmdSetDepthBounds						glDepthBoundsEXT
															
	*/
	virtual void RHISetDepthTestEnable(RHIBool32 Enable) = 0;

	virtual void RHISetDepthWriteEnable(RHIBool32 Enable) = 0;

	virtual void RHISetDepthCompareOp(RHICompareOp DepthCompareOp) = 0;

	virtual void RHISetDepthBoundsTestEnable(RHIBool32 Enable) = 0;

	virtual void RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds) = 0;

	/*
		Copy Commands
	*/
	virtual void RHICmdCopyBuffer(RHIBuffer *SrcBuffer, RHIBuffer *DstBuffer, std::uint32_t RegionCount, const RHIBufferCopy* Regions) = 0;
};

