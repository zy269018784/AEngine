#include "OpenGLCommandBuffer.h"
#include <OpenGL330.h>

void OpenGLCommandBuffer::RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount, std::uint32_t FirstVertex, std::uint32_t FirstInstance)
{

}

void OpenGLCommandBuffer::RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount, std::int32_t FirstIndex, std::int32_t VertexOffset, std::int32_t FirstInstance)
{

}

void OpenGLCommandBuffer::RHISetScissor(const RHIScissor& scissor)
{

}

void OpenGLCommandBuffer::RHISetViewport(const RHIViewport& viewport)
{
	glViewport(viewport.Viewport()[0], viewport.Viewport()[1], viewport.Viewport()[2], viewport.Viewport()[3]);
}

void OpenGLCommandBuffer::RHIBeginRenderPass(RHIRenderPass* RenderPass)
{

}

void OpenGLCommandBuffer::RHIEndRenderPass(RHIRenderPass* RenderPass)
{

}

void OpenGLCommandBuffer::RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat IndexFormat)
{

}

void OpenGLCommandBuffer::RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline)
{

}

void OpenGLCommandBuffer::RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
	RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat IndexFormat)
{

}