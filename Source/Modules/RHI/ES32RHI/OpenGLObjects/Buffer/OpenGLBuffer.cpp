 #include "OpenGLObjects/Buffer/OpenGLBuffer.h"
#include <iostream>

OpenGLBuffer::OpenGLBuffer()
	: Handle(0),
	Type(0),
	bStreamDraw(false)
{

}


OpenGLBuffer::OpenGLBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
	: RHIBuffer(InType, InUsage, InSize),
	Handle(0),
	Type(InType),
	bStreamDraw(false)
{
	glGenBuffers(1, &Handle);
    std::cout << "OpenGLBuffer " << Handle << std::endl;
    switch (Type)
    {
    case VertexBuffer:
        Target = GL_ARRAY_BUFFER;
        break;
    case IndexBuffer:
        Target = GL_ELEMENT_ARRAY_BUFFER;
        break;
    case UniformBuffer:
        Target = GL_UNIFORM_BUFFER;
        break;
    case StorageBuffer:
        Target = GL_SHADER_STORAGE_BUFFER;
        /*
            330没有
            Target = GL_SHADER_STORAGE_BUFFER;
        */
        //std::cout << "OpenGL 330 does not support SSBO" << std::endl;
        break;
    case IndirectBuffer:
        Target = GL_ARRAY_BUFFER;
        break;
    case TransferSrcBuffer:
        Target = GL_COPY_READ_BUFFER;
        break;
    case TransferDstBuffer:
        Target = GL_COPY_WRITE_BUFFER;
        break;
    }
    glBindBuffer(Target, Handle);
	glBufferData(Target, InSize, InData, GetAccess());
}

OpenGLBuffer::~OpenGLBuffer(void)
{
	glDeleteBuffers(1, &Handle);
}

void OpenGLBuffer::Bind()
{
    GLenum Target;
    switch (Type)
    {
    case VertexBuffer:
        Target = GL_ARRAY_BUFFER;
        break;
    case IndexBuffer:
        Target = GL_ELEMENT_ARRAY_BUFFER;
        break;
    case UniformBuffer:
        Target = GL_UNIFORM_BUFFER;
        break;
    case StorageBuffer:
        /*
            330没有
            Target = GL_SHADER_STORAGE_BUFFER;
        */
        std::cout << "OpenGL 330 does not support SSBO" << std::endl;
        break;
    case IndirectBuffer:
        Target = GL_ARRAY_BUFFER;
        break;
    case TransferSrcBuffer:
        Target = GL_COPY_READ_BUFFER;
        break;
    case TransferDstBuffer:
        Target = GL_COPY_WRITE_BUFFER;
        break;
    }
	glBindBuffer(Target, Handle);
}

bool OpenGLBuffer::IsDynamic() const { return false; }

GLenum OpenGLBuffer::GetAccess() const
{
	return bStreamDraw ? GL_STREAM_DRAW : (IsDynamic() ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

GLuint OpenGLBuffer::GetHandle() const {
    return Handle;
}

 void OpenGLBuffer::Update(std::uint32_t InSize, const void* InData)
 {
     glBindBuffer(Target, Handle);
     glBufferData(Target, InSize, InData, GetAccess());
 }