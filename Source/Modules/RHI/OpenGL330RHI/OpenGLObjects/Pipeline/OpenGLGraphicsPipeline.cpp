#include <OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h>
#include <OpenGL330RHI.h>
#include <OpenGLObjects/Shader/OpenGLShader.h>
#include <iostream>

OpenGLGraphicsPipeline::OpenGLGraphicsPipeline()
{
	//CreateVAO();
	//UnbindVAO();
}

OpenGLGraphicsPipeline::~OpenGLGraphicsPipeline()
{
	//DesotryVAO();
}

int OpenGLGraphicsPipeline::CreateVAO()
{
	glGenVertexArrays(1, &VAO);
	return 0;
}

int OpenGLGraphicsPipeline::DesotryVAO()
{
	glDeleteVertexArrays(1, &VAO);
	return 0;
}

int OpenGLGraphicsPipeline::BindVAO()
{
	glBindVertexArray(VAO);
	return 0;
}

int OpenGLGraphicsPipeline::UnbindVAO()
{
	glBindVertexArray(0);
	return 0;
}

GLuint OpenGLGraphicsPipeline::GetVAO()
{
	return VAO;
}

void OpenGLGraphicsPipeline::Create()
{
	Handle = glCreateProgram();
	for (int i = 0; i < Shaders.size(); i++)
	{
		glAttachShader(Handle, ((OpenGLShader *)Shaders[i])->Handle);
	}
	glLinkProgram(Handle);

	int success;
	char infoLog[512];
	glGetProgramiv(Handle, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Handle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	return;
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	/*
		Vertex Input
	*/
	/*
		1. Vertex Input Bindings
	*/
	for (int i = 0; i < VertexInputLayout_.Bindings.size(); i++)
	{
		VertexInputLayout_.Bindings[i].GetStride();
		VertexInputLayout_.Bindings[i].GetInstanceStepRate();
		int Location = i;
		GLsizei Stride	= VertexInputLayout_.Bindings[i].GetStride();
		GLenum Format	= ToOpenGLFormat(VertexInputLayout_.Attributes[0].GetFormat());
		void* Offset	= (void*)VertexInputLayout_.Attributes[0].GetOffset();
		glVertexAttribPointer(Location,
			3, 
			Format,
			GL_FALSE, 
			Stride,
			Offset);

		glEnableVertexAttribArray(i);
	}
	/*
		2. Vertex Input Attributes
	*/
	for (int i = 0; i < VertexInputLayout_.Attributes.size(); i++)
	{
		VertexInputLayout_.Attributes[i].GetBinding();
		VertexInputLayout_.Attributes[i].GetFormat();
		VertexInputLayout_.Attributes[i].GetLocation();
		VertexInputLayout_.Attributes[i].GetOffset();
	}

	/*
		
	*/
	GLenum PM = ToOpenGLPolygonMode(PolygonMode_);
	glPolygonMode(GL_FRONT_AND_BACK, PM);

	/*
		面剔除
	*/
	glEnable(GL_CULL_FACE);
	glCullFace(ToOpenGLCullMode(CullMode_));
	glFrontFace(ToOpenGLFrontFace(FrontFace_));
}



/*
	glIsEnabled with argument GL_CULL_FACE
	glGet with argument GL_CULL_FACE_MODE
*/
GLenum  OpenGLGraphicsPipeline::ToOpenGLPolygonMode(RHIGraphicsPipeline::PolygonMode PolygonMode)
{
	/*
		The initial value is GL_FILL
	*/
	GLenum Mode = GL_FILL;
	switch (PolygonMode)
	{
	case RHIGraphicsPipeline::PolygonMode::Fill:
		Mode = GL_FILL;
		break;
	case RHIGraphicsPipeline::PolygonMode::Line:
		Mode = GL_LINE;
		break;
	case RHIGraphicsPipeline::PolygonMode::Point:
		Mode = GL_POINT;
		break;
	default:
		break;
	}
	return Mode;
}

/*
	glGet with argument GL_POLYGON_MODE
*/
GLenum OpenGLGraphicsPipeline::ToOpenGLCullMode(RHIGraphicsPipeline::CullMode CullMode)
{
	/*
		The initial value is GL_BACK
	*/
	GLenum Mode = GL_BACK;
	switch (CullMode)
	{
	case RHIGraphicsPipeline::CullMode::Front:
		Mode = GL_FRONT;
		break;
	case RHIGraphicsPipeline::CullMode::Back:
		Mode = GL_BACK;
		break;
	case RHIGraphicsPipeline::CullMode::Front_Back:
		Mode = GL_FRONT_AND_BACK;
		break;
	default:
		break;
	}
	return Mode;
}

/*
	glGet with argument GL_FRONT_FACE
*/
GLenum OpenGLGraphicsPipeline::ToOpenGLFrontFace(RHIGraphicsPipeline::FrontFace FrontFace)
{
	/*
		The initial value is GL_CCW
	*/
	GLenum Mode = GL_CCW;
	switch (FrontFace)
	{
	case RHIGraphicsPipeline::FrontFace::CW:
		Mode = GL_CW;
		break;
	case RHIGraphicsPipeline::FrontFace::CCW:
		Mode = GL_CCW;
		break;
	default:
		break;
	}
	return Mode;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLCompareOp(RHIGraphicsPipeline::CompareOp CompareOp)
{
	/*
		The initial value is GL_LESS.
	*/
	GLenum Mode = GL_LESS;
	switch (CompareOp)
	{
	case RHIGraphicsPipeline::CompareOp::Never:
		Mode = GL_NEVER;
		break;
	case RHIGraphicsPipeline::CompareOp::Always:
		Mode = GL_ALWAYS;
		break;
	case RHIGraphicsPipeline::CompareOp::Equal:
		Mode = GL_EQUAL;
		break;
	case RHIGraphicsPipeline::CompareOp::NotEqual:
		Mode = GL_NOTEQUAL;
		break;
	case RHIGraphicsPipeline::CompareOp::Less:
		Mode = GL_LESS;
		break;
	case RHIGraphicsPipeline::CompareOp::LessOrEqual:
		Mode = GL_LEQUAL;
		break;
	case RHIGraphicsPipeline::CompareOp::Greater:
		Mode = GL_GREATER;
		break;
	case RHIGraphicsPipeline::CompareOp::GreaterOrEqual:
		Mode = GL_GEQUAL;
		break;
	default:
		break;
	}
	return Mode;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLStencilOp(RHIGraphicsPipeline::StencilOp StencilOp)
{
	/*
		The initial value is GL_KEEP
	*/
	GLenum Op = GL_KEEP;
	switch (StencilOp)
	{
	case RHIGraphicsPipeline::StencilOp::Keep:
		Op = GL_KEEP;
		break;
	case RHIGraphicsPipeline::StencilOp::Zero:
		Op = GL_ZERO;
		break;
	case RHIGraphicsPipeline::StencilOp::Replace:
		Op = GL_REPLACE;
		break;
	case RHIGraphicsPipeline::StencilOp::Incr:
		Op = GL_INCR;
		break;
	case RHIGraphicsPipeline::StencilOp::IncrWrap:
		Op = GL_INCR_WRAP;
		break;
	case RHIGraphicsPipeline::StencilOp::Decr:
		Op = GL_DECR;
		break;
	case RHIGraphicsPipeline::StencilOp::DecrWrap:
		Op = GL_DECR_WRAP;
		break;
	case RHIGraphicsPipeline::StencilOp::Invert:
		Op = GL_INVERT;
		break;
	default:
		break;
	}
	return Op;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLBlendOp(RHIGraphicsPipeline::BlendOp BlendOp)
{
	GLenum Op;
	switch (BlendOp)
	{
	case RHIGraphicsPipeline::BlendOp::Add:
		Op = GL_FUNC_ADD;
		break;
	case RHIGraphicsPipeline::BlendOp::Sub:
		Op = GL_FUNC_SUBTRACT;
		break;
	case RHIGraphicsPipeline::BlendOp::Min:
		Op = GL_MIN;
		break;
	case RHIGraphicsPipeline::BlendOp::Max:
		Op = GL_MAX;
		break;
	case RHIGraphicsPipeline::BlendOp::Reverse_Sub:
		Op = GL_FUNC_REVERSE_SUBTRACT;
		break;
	default:
		break;
	}
	return Op;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLBlendFactor(RHIGraphicsPipeline::BlendFactor BlendFactor)
{
	/*
		 The initial value is GL_ONE
	*/
	GLenum Fatcor = GL_ONE;
	switch (BlendFactor)
	{
	case RHIGraphicsPipeline::BlendFactor::Zero:
		Fatcor = GL_ONE;
		break;
	case RHIGraphicsPipeline::BlendFactor::One:
		Fatcor = GL_ONE;
		break;
	case RHIGraphicsPipeline::BlendFactor::SrcColor:
		Fatcor = GL_SRC_COLOR;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusSrcColor:
		Fatcor = GL_ONE_MINUS_SRC_COLOR;
		break;
	case RHIGraphicsPipeline::BlendFactor::DstColor:
		Fatcor = GL_DST_COLOR;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusDstColor:
		Fatcor = GL_ONE_MINUS_DST_COLOR;
		break;
	case RHIGraphicsPipeline::BlendFactor::SrcAlpha:
		Fatcor = GL_SRC_ALPHA;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusSrcAlpha:
		Fatcor = GL_ONE_MINUS_SRC_ALPHA;
		break;
	case RHIGraphicsPipeline::BlendFactor::DstAlpha:
		Fatcor = GL_DST_ALPHA;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusDstAlpha:
		Fatcor = GL_ONE_MINUS_DST_ALPHA;
		break;
	case RHIGraphicsPipeline::BlendFactor::ConstantColor:
		Fatcor = GL_CONSTANT_COLOR;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusConstantColor:
		Fatcor = GL_ONE_MINUS_CONSTANT_COLOR;
		break;
	case RHIGraphicsPipeline::BlendFactor::ConstantAlpha:
		Fatcor = GL_CONSTANT_ALPHA;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusConstantAlpha:
		Fatcor = GL_ONE_MINUS_CONSTANT_ALPHA;
		break;
	case RHIGraphicsPipeline::BlendFactor::SrcAlphaSaturate:
		std::cout << "OpenGL 3.3 does not support SrcAlphaSaturate" << std::endl;
		break;
	case RHIGraphicsPipeline::BlendFactor::Src1Color:
		std::cout << "OpenGL 3.3 does not support Src1Color" << std::endl;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusSrc1Color:
		std::cout << "OpenGL 3.3 does not support OneMinusSrc1Color" << std::endl;
		break;
	case RHIGraphicsPipeline::BlendFactor::Src1Alpha:
		std::cout << "OpenGL 3.3 does not support Src1Alpha" << std::endl;
		break;
	case RHIGraphicsPipeline::BlendFactor::OneMinusSrc1Alpha:
		std::cout << "OpenGL 3.3 does not support OneMinusSrc1Alpha" << std::endl;
		break;
	default:
		break;
	}
	return Fatcor;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLSampleCountFlagBits(int Count)
{
	GLenum Mode;

	return Mode;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLPrimitiveTopology(RHIGraphicsPipeline::Topology Topology)
{
	GLenum Mode;
	switch (Topology)
	{	
	case RHIGraphicsPipeline::Topology::Points:
		Mode = GL_POINTS;
		break;
	case RHIGraphicsPipeline::Topology::Lines:
		Mode = GL_LINES;
		break;
	case RHIGraphicsPipeline::Topology::LineStrip:
		Mode = GL_LINE_STRIP;
		break;
	case RHIGraphicsPipeline::Topology::Triangles:
		Mode = GL_TRIANGLES;
		break;
	case RHIGraphicsPipeline::Topology::TriangleStrip:
		Mode = GL_TRIANGLE_STRIP;
		break;
	case RHIGraphicsPipeline::Topology::TriangleFan:
		Mode = GL_TRIANGLE_FAN;
		break;
	case RHIGraphicsPipeline::Topology::LinesWithAdjacency:
		Mode = GL_LINES_ADJACENCY;
		break;
	case RHIGraphicsPipeline::Topology::LineStripWithAdjacency:
		Mode = GL_LINE_STRIP_ADJACENCY;
		break;
	case RHIGraphicsPipeline::Topology::TrianglesWithAdjacency:
		Mode = GL_TRIANGLES_ADJACENCY;
		break;
	case RHIGraphicsPipeline::Topology::TriangleStripWithAdjacency:
		Mode = GL_TRIANGLE_STRIP_ADJACENCY;
		break;
	case RHIGraphicsPipeline::Topology::Patches:
		std::cout << "OpenGL 3.3 does not support Patches" << std::endl;
		break;
	default:
		break;
	}
	return Mode;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLShaderStageFlagBits(RHIShader::Type Type)
{
	GLenum Mode;

	return Mode;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLVertexInputRate(std::uint32_t StepRate)
{
	GLenum Mode;

	return Mode;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLShaderStageFlagBits(RHIShaderResourceBinding::StageFlags Flag)
{
	GLenum Mode;
	switch (Flag)
	{
	case RHIShaderResourceBinding::StageFlags::VertexStage:
		Mode = GL_VERTEX_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationControlStage:
		std::cout << "OpenGL 3.3 does not support TessellationControlStage" << std::endl;
		//Mode = GL_TESS_CONTROL_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationEvaluationStage:
		std::cout << "OpenGL 3.3 does not support TessellationEvaluationStage" << std::endl;
		//Mode = GL_TESS_EVALUATION_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::FragmentStage:
		Mode = GL_FRAGMENT_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::ComputeStage:
		std::cout << "OpenGL 3.3 does not support ComputeStage" << std::endl;
		//Mode = GL_COMPUTE_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::GeometryStage:
		Mode = GL_GEOMETRY_SHADER;
		break;
	default:
		break;
	}
	return Mode;
}

GLenum OpenGLGraphicsPipeline::ToOpenGLLogicOp(RHIGraphicsPipeline::LogicOp LogicOp)
{
	/*
		The initial value is GL_COPY
	*/
	GLenum Op = GL_COPY;
	switch (LogicOp)
	{
	case RHIGraphicsPipeline::LogicOp::CLEAR:
		Op = GL_CLEAR;
		break;
	case RHIGraphicsPipeline::LogicOp::SET:
		Op = GL_SET;
		break;
	case RHIGraphicsPipeline::LogicOp::COPY:
		Op = GL_COPY;
		break;
	case RHIGraphicsPipeline::LogicOp::COPY_INVERTED:
		Op = GL_COPY_INVERTED;
		break;
	case RHIGraphicsPipeline::LogicOp::NOOP:
		Op = GL_NOOP;
		break;
	case RHIGraphicsPipeline::LogicOp::INVERT:
		Op = GL_INVERT;
		break;
	case RHIGraphicsPipeline::LogicOp::AND:
		Op = GL_AND;
		break;
	case RHIGraphicsPipeline::LogicOp::NAND:
		Op = GL_NAND;
		break;
	case RHIGraphicsPipeline::LogicOp::OR:
		Op = GL_OR;
		break;
	case RHIGraphicsPipeline::LogicOp::NOR:
		Op = GL_NOR;
		break;
	case RHIGraphicsPipeline::LogicOp::XOR:
		Op = GL_XOR;
		break;
	case RHIGraphicsPipeline::LogicOp::EQUIV:
		Op = GL_EQUIV;
		break;
	case RHIGraphicsPipeline::LogicOp::AND_REVERSE:
		Op = GL_AND_REVERSE;
		break;
	case RHIGraphicsPipeline::LogicOp::AND_INVERTED:
		Op = GL_AND_INVERTED;
		break;
	case RHIGraphicsPipeline::LogicOp::OR_REVERSE:
		Op = GL_OR_REVERSE;
		break;
	case RHIGraphicsPipeline::LogicOp::OR_INVERTED:
		Op = GL_OR_INVERTED;
		break;
	default:
		break;
	}
	return Op;
}