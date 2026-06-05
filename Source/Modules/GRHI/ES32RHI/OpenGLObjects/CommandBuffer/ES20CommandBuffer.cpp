#include "ES32RHI/OpenGLObjects/CommandBuffer/ES20CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/Buffer/OpenGLBuffer.h"
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include <iostream>

#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"

void ES20CommandBuffer::RHISetPrimitiveTopology(RHITopology Topology)
{

}

void ES20CommandBuffer::RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount, std::uint32_t FirstVertex, std::uint32_t FirstInstance)
{	
	GLenum RHITopology =    ToOpenGLPrimitiveTopology(GraphicsPipeline->GetTopology());

	GLenum RHIPolygonMode = ToOpenGLPolygonMode(GraphicsPipeline->GetPolygonMode());

	GLenum RHIFrontFace =   ToOpenGLFrontFace(GraphicsPipeline->GetFrontFace());

	GLenum RHICullMode =    ToOpenGLCullMode(GraphicsPipeline->GetCullMode());

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearDepthf(1.0f);
	/*
		ES 2.1 不支持
		多边形模式:
			填充
			点
			线
	*/
	//glPolygonMode(GL_FRONT_AND_BACK, RHIPolygonMode);
	/*
		定义正面:
			顺时针
			逆时针
	*/
	glFrontFace(RHIFrontFace);
	/*
		剔除正面
		剔除反面
		剔除两面
	*/
	glCullFace(RHICullMode);
	/*
		打开面剔除
	*/
	if (RHICullMode::CullModeNone == GraphicsPipeline->GetCullMode())
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	// ES 2.1 不支持实例化绘制
	//glDrawArraysInstanced(GL_TRIANGLES, FirstVertex, VertexCount, InstanceCount);
	if (InstanceCount > 0)
		glDrawArrays(GL_TRIANGLES, FirstVertex, VertexCount);
}

void ES20CommandBuffer::RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount, std::int32_t FirstIndex, std::int32_t VertexOffset, std::int32_t FirstInstance)
{
	GLenum RHITopology = ToOpenGLPrimitiveTopology(GraphicsPipeline->GetTopology());

	GLenum RHIPolygonMode = ToOpenGLPolygonMode(GraphicsPipeline->GetPolygonMode());

	GLenum RHIFrontFace = ToOpenGLFrontFace(GraphicsPipeline->GetFrontFace());

	GLenum RHICullMode = ToOpenGLCullMode(GraphicsPipeline->GetCullMode());

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearDepthf(1.0f);
	/*
		ES 2.1 不支持
		多边形模式:
			填充
			点
			线
	*/
	glPolygonMode(GL_FRONT_AND_BACK, RHIPolygonMode);
	/*
		定义正面:
			顺时针
			逆时针
	*/
	glFrontFace(RHIFrontFace);
	/*
		剔除正面
		剔除反面
		剔除两面
	*/
	glCullFace(RHICullMode);
	/*
		打开面剔除
	*/
	if (RHICullMode::CullModeNone == GraphicsPipeline->GetCullMode())
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	// ES 2.1 不支持实例化绘制
	//glDrawElementsInstanced(RHITopology, IndexCount, IndexType1, (const void*)(VertexOffset), InstanceCount);
	if (InstanceCount > 0)
		glDrawElements(RHITopology, IndexCount, IndexType1, (const void*)(VertexOffset));
}

void ES20CommandBuffer::RHISetScissor(const RHIScissor& scissor)
{
	glScissor(scissor.X(), scissor.Y(), scissor.Width(), scissor.Height());
}

void ES20CommandBuffer::RHISetStencilTestEnable(RHIBool32 Enable)
{

}

void ES20CommandBuffer::RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp, RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp)
{

}

void ES20CommandBuffer::RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask)
{

}

void ES20CommandBuffer::RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference)
{

}

void ES20CommandBuffer::RHISetDepthTestEnable(RHIBool32 Enable)
{
	if (Enable)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void ES20CommandBuffer::RHISetDepthWriteEnable(RHIBool32 Enable)
{
	if (Enable)
		glDepthMask(GL_TRUE);
	else
		glDepthMask(GL_FALSE);
}

void ES20CommandBuffer::RHISetDepthCompareOp(RHICompareOp DepthCompareOp)
{
	GLenum Op = ToOpenGLCompareOp(DepthCompareOp);
	glDepthFunc(Op);
}

void ES20CommandBuffer::RHISetDepthBoundsTestEnable(RHIBool32 Enable)
{
	//std::cout << "need extension" << std::endl;
}

void ES20CommandBuffer::RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds)
{
	//std::cout << "need extension" << std::endl;
}

void ES20CommandBuffer::RHISetViewport(const RHIViewport& viewport)
{
	glViewport(viewport.X(), viewport.Y(), viewport.Width(), viewport.Height());
	glDepthRangef(viewport.MinDepth(), viewport.MaxDepth());	

	//glViewport(viewport.Viewport()[0], viewport.Viewport()[1], viewport.Viewport()[2], viewport.Viewport()[3]);
}

void ES20CommandBuffer::RHIBeginRenderPass(RHIRenderPass* RenderPass)
{

}

void ES20CommandBuffer::RHIEndRenderPass(RHIRenderPass* RenderPass)
{

}

void ES20CommandBuffer::RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat RHIIndexFormat)
{

}

void ES20CommandBuffer::RHISetGraphicsPipeline(RHIGraphicsPipeline* InGraphicsPipeline)
{
	if (InGraphicsPipeline)
	{
		GraphicsPipeline = InGraphicsPipeline;
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(((OpenGLGraphicsPipeline*)GraphicsPipeline)->Handle);


		OpenGLGraphicsPipeline* OpenGLPipeline = (OpenGLGraphicsPipeline*)InGraphicsPipeline;
		if (OpenGLPipeline->ShaderResourceBindings)
		{
			auto Bindings = OpenGLPipeline->ShaderResourceBindings->GetBindings();
			for (int i = 0; i < Bindings.size(); i++)
			{
				/*
					绑定点
				*/
				GLuint BindingPoint = Bindings[i].d.binding;
				/*
					着色器
				*/
				//Bindings[i].d.stage;
				/*
					资源类型
				*/
				if (RHIShaderResourceBinding::Type::StorageBuffer == Bindings[i].d.type)
				{
					GLuint Buffer = ((OpenGLBuffer*)Bindings[i].d.u.sbuf.buf)->GetHandle();
					GLintptr Offset = Bindings[i].d.u.sbuf.offset;
					GLsizeiptr Size = Bindings[i].d.u.sbuf.maybeSize;

					glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindingPoint, Buffer);
					/*
						To Do: 暂时只支持整个Buffer
					*/
					//glBindBufferRange(GL_SHADER_STORAGE_BUFFER, BindingPoint, SSBO, Offset, Size);
				}

				if (RHIShaderResourceBinding::Type::UniformBuffer == Bindings[i].d.type)
				{
					GLuint Buffer = ((OpenGLBuffer*)Bindings[i].d.u.sbuf.buf)->GetHandle();
					GLintptr Offset = Bindings[i].d.u.sbuf.offset;
					GLsizeiptr Size = Bindings[i].d.u.sbuf.maybeSize;

					glBindBufferBase(GL_UNIFORM_BUFFER, BindingPoint, Buffer);
					/*
						To Do: 暂时只支持整个Buffer
					*/
					//glBindBufferRange(GL_SHADER_STORAGE_BUFFER, BindingPoint, SSBO, Offset, Size);
				}
			}
		}
	}
	else
	{
		glUseProgram(0);
	}
}
/*
glGenVertexArrays						3.0		ES 3.0
glCreateVertexArrays					4.5
glDeleteVertexArrays					3.0		ES 3.0

glBindVertexArray						3.0		ES 3.0
glIsVertexArray							3.0		ES 3.0
glVertexArrayElementBuffer

glVertexAttribPointer					2.0		ES 2.0
glVertexAttribIPointer					3.0		ES 3.0
glVertexAttribLPointer					4.1

glVertexAttribFormat					4.3		ES 3.1
glVertexAttribIFormat					4.3		ES 3.1
glVertexAttribLFormat					4.3
glVertexArrayAttribFormat				4.5
glVertexArrayAttribIFormat				4.5
glVertexArrayAttribLFormat				4.5


glBindVertexBuffer						4.3		ES 3.1
glBindVertexBuffers						4.4	
glVertexArrayVertexBuffer				4.5
glVertexArrayVertexBuffers				4.5

glVertexAttribBinding					4.3		ES 3.1
glVertexArrayAttribBinding              4.5


glEnableVertexAttribArray				2.0		ES 2.0
glEnableVertexArrayAttrib				4.5
glDisableVertexAttribArray				2.0		ES 2.0
glDisableVertexArrayAttrib				4.5

glVertexBindingDivisor
glVertexArrayBindingDivisor
glVertexAttribDivisor
*/
void ES20CommandBuffer::RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
	RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat InIndexFormat)
{
	IndexType1 = ToOpenGLIndexType(InIndexFormat);
	/*
		绑定VAO
	*/
	((OpenGLGraphicsPipeline*)GraphicsPipeline)->BindVAO();
	OpenGLBuffer* RHIVBO = (OpenGLBuffer*)(Bindings->first);
	glBindBuffer(GL_ARRAY_BUFFER, RHIVBO->GetHandle());
	if (RHIEBO)
	{	
		OpenGLBuffer* OpenGLEBO = (OpenGLBuffer*)(RHIEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGLEBO->GetHandle());
	}

	auto VertexInputLayout = GraphicsPipeline->GetVertexInputLayout();
	for (int i = 0; i < VertexInputLayout.Attributes.size(); i++)
	{
		RHIVertexInputAttribute& Att = VertexInputLayout.Attributes[i];
		int Location = Att.GetLocation();
		int BindingIndex = Att.GetBinding();

		GLsizei Stride = 0;
		if (BindingIndex < VertexInputLayout.Bindings.size())
			Stride = VertexInputLayout.Bindings[BindingIndex].GetStride();

		int Size = 0;
		if (RHIVertexInputAttribute::Format::Float4 == Att.GetFormat())
		{
			Size = 4;
		}
		if (RHIVertexInputAttribute::Format::Float3 == Att.GetFormat())
		{
			Size = 3;
		}
		else if (RHIVertexInputAttribute::Format::Float2 == Att.GetFormat())
		{
			Size = 2;
		}
		std::uint32_t Offset = Att.GetOffset();


		glVertexAttribPointer(Location, Size, GL_FLOAT, GL_FALSE, Stride, (void*)Offset);

		glEnableVertexAttribArray(Location);
	}
}

/*
	Copy Commands
*/
void ES20CommandBuffer::RHICmdCopyBuffer(RHIBuffer* SrcBuffer, RHIBuffer* DstBuffer, std::uint32_t RegionCount, const RHIBufferCopy* Regions)
{

}