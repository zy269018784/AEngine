#include <OpenGL330RHI.h>
#include <OpenGLObjects/Buffer/OpenGLBuffer.h>
#include <OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h>
#include <OpenGLObjects/Window/OpenGLWindow.h>
#include <iostream>
OpenGL330RHI::OpenGL330RHI()
{
	//if (!gladLoadGL()) 
	//{
	//	std::cout << "gladLoadGL failed" << std::endl;
	//	return;
	//}
}

OpenGL330RHI::~OpenGL330RHI()
{

}

void OpenGL330RHI::RHIUseGPU(std::uint32_t GPUIndex)
{

}



RHIBuffer* OpenGL330RHI::RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize){ return nullptr; }

RHIBuffer* OpenGL330RHI::RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
{ 
	OpenGLBuffer* Buffer = new OpenGLBuffer(InType, InUsage, InSize, InData);
	return Buffer;
}

RHIGraphicsPipeline* OpenGL330RHI::RHICreateGraphicsPipeline()
{ 
	OpenGLGraphicsPipeline* Pipeline = new OpenGLGraphicsPipeline();
	return Pipeline;
}

RHIGraphicsPipeline* OpenGL330RHI::RHICreateGraphicsPipeline(RHIWindow* Window)
{ 
	OpenGLGraphicsPipeline* Pipeline = new OpenGLGraphicsPipeline();
	return Pipeline;
}

RHIShader* OpenGL330RHI::RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize){ return nullptr; }

RHITexture* OpenGL330RHI::RHICreateTexture1D(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX){ return nullptr; }

RHITexture* OpenGL330RHI::RHICreateTexture1DArray(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize){ return nullptr; }

RHITexture* OpenGL330RHI::RHICreateTexture2D(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY){ return nullptr; }


RHITexture* OpenGL330RHI::RHICreateTexture2DArray(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize){ return nullptr; }

RHITexture* OpenGL330RHI::RHICreateTexture3D(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ){ return nullptr; }

RHITexture* OpenGL330RHI::RHICreateTextureCube(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t Size){ return nullptr; }



RHITexture* OpenGL330RHI::RHICreateTextureCubeArray(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize){ return nullptr; }

void OpenGL330RHI::RHIUpdateTexture(RHITexture* Texture, const void* InData, std::uint32_t InSize){  }

RHISampler* OpenGL330RHI::RHICreateSampler(RHIFilter MinFilter,
	RHIFilter MagFilter,
	RHIAddressMode AddressModeU,
	RHIAddressMode AddressModeV,
	RHIAddressMode AddressModeW){ return nullptr; }

RHIShaderResourceBindings* OpenGL330RHI::RHICreateShaderResourceBindings(){ return nullptr; }

GLenum ToOpenGLFormat(RHIVertexInputAttribute::Format Format)
{
	GLenum OpenGLFormat = GL_INT;
	switch (Format)
	{
	case RHIVertexInputAttribute::Float4:
	case RHIVertexInputAttribute::Float3:
	case RHIVertexInputAttribute::Float2:
	case RHIVertexInputAttribute::Float:
		OpenGLFormat = GL_FLOAT;
		break;
	case RHIVertexInputAttribute::UNormByte4:
		break;
	case RHIVertexInputAttribute::UNormByte2:
		break;
	case RHIVertexInputAttribute::UNormByte:
		break;
	case RHIVertexInputAttribute::UInt4:
		break;
	case RHIVertexInputAttribute::UInt3:
		break;
	case RHIVertexInputAttribute::UInt2:
		break;
	case RHIVertexInputAttribute::UInt:
		break;
	case RHIVertexInputAttribute::SInt4:
		break;
	case RHIVertexInputAttribute::SInt3:
		break;
	case RHIVertexInputAttribute::SInt2:
		break;
	case RHIVertexInputAttribute::SInt:
		break;
	case RHIVertexInputAttribute::Half4:
		break;
	case RHIVertexInputAttribute::Half3:
		break;
	case RHIVertexInputAttribute::Half2:
		break;
	case RHIVertexInputAttribute::Half:
		break;
	default:
		break;
	}
	return OpenGLFormat;
}