#pragma once
#include "RHIObjects/CommandBuffer/RHICommandBuffer.h"
#include <cstdint>
class OpenGLCommandBuffer : public RHICommandBuffer
{
public:
	OpenGLCommandBuffer() = default;
public:
	/*
		RHI API
	*/
	// draw primitive
	virtual void RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount = 1, std::uint32_t FirstVertex = 0, std::uint32_t FirstInstance = 0)  final override;
	// draw indexed primitive
	virtual void RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount = 1, std::int32_t FirstIndex = 0, std::int32_t VertexOffset = 0, std::int32_t FirstInstance = 0) final override;

	virtual void RHISetScissor(const RHIScissor& scissor) final override;

	virtual void RHISetViewport(const RHIViewport& viewport) final override;

	virtual void RHIBeginRenderPass(RHIRenderPass* RenderPass) final override;

	virtual void RHIEndRenderPass(RHIRenderPass* RenderPass) final override;

	virtual void RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat IndexFormat) final override;

	virtual void RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline) final override;

	virtual void RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
		RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat IndexFormat) final override;

};