#pragma once
#include <OpenGLObjects/Pipeline/OpenGLPipeline.h>
#include <RHIObjects/RHIGraphicsPipeline.h>
#include <RHIObjects/RHIShader.h>

class OpenGLGraphicsPipeline : public RHIGraphicsPipeline, public OpenGLPipeline
{
public:
	OpenGLGraphicsPipeline();
	~OpenGLGraphicsPipeline();
	GLuint GetVAO();
	int CreateVAO();
	int DesotryVAO();
	int BindVAO();
	int UnbindVAO();
public:
	virtual void Create() final override;
private:
	/*
		Polygon Mode
			glPolygonMode 
	*/
	GLenum ToOpenGLPolygonMode(RHIGraphicsPipeline::PolygonMode PolygonMode);
	/*
		Cull Mode
			Facet culling is initially disabled
			glEnable(GL_CULL_FACE)
			glDisable(GL_CULL_FACE)
			glCullFace
			glFrontFace
	*/
	GLenum ToOpenGLCullMode(RHIGraphicsPipeline::CullMode CullMode);
	GLenum ToOpenGLFrontFace(RHIGraphicsPipeline::FrontFace FrontFace);
	/*
		Depth Test
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_DEPTH_TEST);
			glDepthMask
			glDepthFunc
	*/
	GLenum ToOpenGLCompareOp(RHIGraphicsPipeline::CompareOp CompareOp);
	/*
		Stencil Test
			glStencilMask
			glStencilFunc
			glStencilOp
	*/
	GLenum ToOpenGLStencilOp(RHIGraphicsPipeline::StencilOp StencilOp);

	/*
		Blending
			glBlendColor 
			glBlendFunc
			glBlendEquation
	*/
	GLenum ToOpenGLBlendOp(RHIGraphicsPipeline::BlendOp BlendOp);
	GLenum ToOpenGLBlendFactor(RHIGraphicsPipeline::BlendFactor BlendFactor);
	/*
		Primitives 
			glDrawArrays
	*/
	GLenum ToOpenGLPrimitiveTopology(RHIGraphicsPipeline::Topology Topology);
	/*
		Shade Stage
	*/
	GLenum ToOpenGLShaderStageFlagBits(RHIShader::Type Type);
	GLenum ToOpenGLShaderStageFlagBits(RHIShaderResourceBinding::StageFlags);
	/*
		Logical Operations
			glEnable(GL_COLOR_LOGIC_OP);
			glDisable(GL_COLOR_LOGIC_OP);
			glLogicOp
	*/
	GLenum ToOpenGLLogicOp(RHILogicOp LogicOp);

	GLenum ToOpenGLVertexInputRate(std::uint32_t StepRate);
	GLenum ToOpenGLSampleCountFlagBits(int Count);
private:
	GLuint VAO;
};