#pragma once
#ifndef GLAD_OPENGL_3_2
#define GLAD_OPENGL_3_2

#include <glad/include/glad/glad.h>

#endif // !GLAD

/*
*	Chapter. OpenGL Versions
*	1. Version Table
*		OpenGL							ES
*		OpenGL 1.0						1.0	
*		OpenGL 1.1						1.1
*		OpenGL 1.2						2.0
*		OpenGL 1.3						3.0
*		OpenGL 1.4						3.1
*		OpenGL 1.5						3.2
*		OpenGL 2.0						3.3
*		OpenGL 2.1
*		OpenGL 3.0
*		OpenGL 3.1
*		OpenGL 3.2
*		OpenGL 3.3
*		OpenGL 4.0
*		OpenGL 4.1
*		OpenGL 4.2
*		OpenGL 4.3
*		OpenGL 4.4
*		OpenGL 4.5
*		OpenGL 4.6
*	2. OpenGL Update Table
*								Update
*		OpenGL 1.0				Basic texture mapping.
*		OpenGL 1.1				Vertex arrays, Texture objects.
*		OpenGL 1.2				3D textures.
*		OpenGL 1.3				Compressed textures, Cube map textures, Multisampling.
*		OpenGL 1.4				Multiple draw arrays.
*		OpenGL 1.5				VBO.
*		OpenGL 2.0				GLSL 1.1, Non-power-of-two textures.
*		OpenGL 2.1				GLSL 1.2, PBO.
*		OpenGL 3.0				FBO, Conditional rendering, Texture arrays.
*		OpenGL 3.1				UBO, TBO, Instanced rendering, Primitive restart.
*		OpenGL 3.2				Geometry shader, Multisampled textures.
*		OpenGL 3.3				Texture swizzle.
*		OpenGL 4.0				Tessellation shader.
*		OpenGL 4.1
*		OpenGL 4.2
*		OpenGL 4.3				Compute shader.
*		OpenGL 4.4
*		OpenGL 4.5
*		OpenGL 4.6				SPIR-V support.
*	3. ES Update Table
*								Update
*		1.0						Fixed-function pipeline.
*		1.1						Draw texture.
*		2.0						Vertex shader, Fragment shader, Non-power-of-two textures.
*		3.0						UBO, 3D textures, Sampler objects, Sync objects and fences, Texture compression (ETC2/EAC), Multiple render targets (up to 4), Transform feedback
*		3.1						Compute shader.
*		3.2						Geometry shader, Tessellation shader.
*		3.3
*   4. OpenGL和ES对应版本
*		OpenGL			ES			描述
*		1.x				1.x			Fixed-function pipeline.
*		2.0				2.0			Vertex shader, Fragment shader.
*		3.0~3.1			3.0			Multiple render targets.
*		3.2~4.3			3.1			Compute shader.
*		4.x				3.2			Geometry shader, Tessellation shader.
*/

/*
*	Chapter. Buffer Objects
*	1. API Table
*												OpenGL							ES
*		glGenTextures							2.0								2.0
*   2. SSBO
*   3. UBO
*   4. TBO
*/

/*
*	Chapter. VAO
*/

/*
*	Chapter. Pipeline
*	1. API Table
* 												OpenGL							OpenGL ES
*		glCreateShader							2.0								2.0
*		glShaderSource							2.0								2.0
*		glCompileShader							2.0								2.0
*		glReleaseShaderCompiler					2.0								2.0
*		glDeleteShader							2.0								2.0
*		glIsShader								2.0								2.0
*		glShaderBinary							2.0								2.0
*		glSpecializeShader						4.6 							Not Support
*		glCreateProgram							2.0								2.0
*		glDeleteProgram							2.0								2.0
*		glAttachShader							2.0								2.0
*		glDetachShader							2.0								2.0
*		glLinkProgram							2.0								2.0
*		glUseProgram							2.0								2.0
*		glIsProgram								2.0								2.0
*		glCreateShaderProgramv					4.1 							Not Support
*		glProgramParameteri						4.0								3.1
*		glGenProgramPipelines					4.1								3.1
*		glDeleteProgramPipelines				4.1								3.1
*		glCreateProgramPipelines				4.5								Not Support
*		glBindProgramPipeline					4.1								3.1
*		glUseProgramStages						4.1								3.1
*		glIsProgramPipeline						4.1								3.1
*		glActiveShaderProgram					4.1								3.1
*		glGetProgramBinary						4.1								3.0
*		glProgramBinary							4.1								3.0
*		glGetShaderiv							2.0								2.0
*		glGetProgramiv							2.0								2.0
*		glGetProgramPipelineiv					4.1								3.1
*		glGetAttachedShaders					2.0								2.0
*		glGetShaderInfoLog						2.0								2.0
*		glGetProgramInfoLog						2.0								2.0
*		glGetProgramPipelineInfoLog				4.1								3.1
*		glGetShaderSource						2.0								2.0
*		glGetShaderPrecisionFormat				4.1								2.0
*		glGetUniformfv							2.0								2.0
*		glGetUniformdv							2.0								Not Support
*		glGetUniformiv							2.0								2.0
*		glGetUniformuiv							3.0								3.0
*		glGetnUniformfv							4.5								Not Support
*		glGetnUniformdv							4.5								Not Support
*		glGetnUniformiv							4.5								Not Support
*		glGetnUniformuiv						4.5								Not Support
*		glShaderBinary							4.1								2.0
*		glSpecializeShader
*		glProgramBinary
*	2. Pipeline Type
*		2.1 Graphics Pipeline
* 		2.2 Compute Pipeline
*   3. Shader Type
*		3.1 Vertex Shader
* 		3.2 Fragment Shader
* 		3.3 Compute Shader
* 		3.4 Geometry Shader
*   	3.5 Tessellation Control Shader
* 		3.6 Tessellation Evaluation Shader
*	4. Program Object
*	5. Program Pipeline Objects
*/

/*	
*	Chapter. Texture
*	1. API Table
*												OpenGL							ES
*		glGenTextures							2.0								2.0
*		glDeleteTextures						2.0								2.0
*		glBindTexture							2.0								2.0
*		glActiveTexture							2.0								2.0
*		glTexImage1D							2.0								Not Supported
*		glTexImage2D							2.0								2.0
*		glTexImage3D							2.0								3.0
*		glTexSubImage1D							2.0								Not Supported
*		glTextureSubImage1D						4.5								Not Supported
*		glTexSubImage2D							2.0								2.0			
*		glTextureSubImage2D						4.5								Not Supported
*		glTexSubImage3D							2.0								3.0
*		glTextureSubImage3D						4.5								Not Supported
*		glTexImage2DMultisample					2.0								Not Supported
*		glTexImage3DMultisample					3.2								Not Supported
*		glTexStorage1D							4.2								Not Supported
*		glTextureStorage1D						4.5								Not Supported
*		glTexStorage2D							4.2								3.0
*		glTextureStorage2D						4.5								Not Supported
*		glTexStorage3D							4.2								3.0
*		glTextureStorage3D						4.5								Not Supported
*		glTexStorage2DMultisample				4.3								3.1
*		glTextureStorage2DMultisample			4.5								Not Supported
*		glTexStorage3DMultisample				4.3								3.2
*		glTextureStorage3DMultisample			4.5								Not Supported
*		glTexBuffer								3.1								3.2
*		glTextureBuffer							4.5								Not Supported
*		glTexBufferRange						4.3								3.2
*		glTextureBufferRange					4.5								Not Supported
*		glTexParameterf							2.0								2.0
*		glTextureParameterf						4.5								Not Supported
*		glTexParameteri							2.0								2.0	
*		glTextureParameteri						4.5								Not Supported
*		glTexParameterfv						2.0								2.0
*		glTextureParameterfv					4.5								Not Supported
*		glTexParameteriv						2.0								2.0
*		glTextureParameteriv					4.5								Not Supported
*		glTexParameterIiv						3.0								3.2
*		glTextureParameterIiv					4.5								Not Supported
*		glTexParameterIuiv						3.0								3.2
*		glTextureParameterIuiv					4.5								Not Supported
*		glTextureBarrier						4.5								Not Supported
*		glTextureView							4.3								Not Supported
*		glGenerateMipmap						3.0								2.0
*		glGenerateTextureMipmap					4.5								Not Supported
*		glCopyTexImage1D						2.0								Not Supported
*		glCopyTexImage2D						2.0								2.0
*		glCopyTexSubImage1D						2.0								Not Supported
*		glCopyTextureSubImage1D					4.5								Not Supported
*		glCopyTexSubImage2D						2.0								2.0
*		glCopyTextureSubImage2D					4.5								Not Supported
*		glCopyTexSubImage3D						2.0								3.0
*		glCopyTextureSubImage3D					4.5								Not Supported
*		glCompressedTexImage1D					2.0								Not Supported
*		glCompressedTexImage2D					2.0								2.0
*		glCompressedTexImage3D					2.0								3.0
*		glCompressedTexSubImage1D				2.0								Not Supported
*		glCompressedTextureSubImage1D			4.5								Not Supported
*		glCompressedTexSubImage2D				2.0								2.0
*		glCompressedTextureSubImage2D			4.5								Not Supported
*		glCompressedTexSubImage3D				2.0								3.0
*		glCompressedTextureSubImage3D			4.5								Not Supported
*		glCopyImageSubData						4.3								3.2
*		glBindTextureUnit						4.5								Not Supported
*		glGenSamplers
*		glDeleteSamplers
*		glBindSampler
*		glSamplerParameterf
*		glSamplerParameteri
*		glSamplerParameterfv
*		glSamplerParameteriv
*		glSamplerParameterIiv
*		glSamplerParameterIuiv
* 	2. API Usage
*		2.1
*        
*        void glTexImage2D(GLenum target,
* 	                      GLint level,
* 	                      GLint internalformat,
* 	                      GLsizei width,
* 	                      GLsizei height,
* 	                      GLint border,
* 	                      GLenum format,
* 	                      GLenum type,
* 	                      const void * data);
*
*        void glTexStorage2D(GLenum target,
* 	                        GLsizei levels,
* 	                        GLenum internalformat,
* 	                        GLsizei width,
* 	                        GLsizei height);
*
*		void glTexSubImage2D(GLenum target,
* 	                             GLint level,
* 	                             GLint xoffset,
* 	                             GLint yoffset,
* 	                             GLsizei width,
* 	                             GLsizei height,
* 	                             GLenum format,
* 	                             GLenum type,
* 	                             const void * pixels);
*	3. Sample Objects
*   4. glsl
*		4.1 1D Texture
*			uniform sampler1D texSampler;
*			float u
*			vec4 outColor = texture(texSampler, u);
*		4.2 1D Texture Array
*			uniform sampler1DArray  texArraySampler;
* 			float layer;
*			vec2 UV = vec2(u, layer);
*			vec4 outColor = texture(texArraySampler, UV);
*		4.3 2D Texture
*			uniform sampler2D texSampler;
*			vec4 outColor = texture(texSampler, vec2(u, v));
*		4.4 2D Texture Array
*			uniform sampler2DArray  texArraySampler;
*			float layer;
*			vec3 UVW = vec3(uv, layer);
*			vec4 outColor = texture(texArraySampler, UVW);
*		4.5 3D Texture
*			uniform sampler3D texSampler;
*			vec3 UVW = vec3(u, v, w);
*			vec4 vec4 color = texture(texSampler, UVW);
*		4.6 CubeMap
*			uniform samplerCube cubemap
*			vec3 dir;
*			vec3 UVW = normalize(dir);
*			vec4 outColor = texture(cubemap, UVW);
*		4.7 CubeMap Array
*			uniform samplerCubeArray cubemapArray;
*			float layer;
*			vec3 dir;
*			vec3 UVW = normalize(dir);
*			vec4 UVWZ = vec4(UVW, layer);
*			vec4 outColor = texture(cubemapArray, vec4(normalize(inTexCoord), 0));
*/

/*
*	Chapter. Depth Test
*	1. API Table
*												OpenGL							ES
*		glDepthMask								1.0								1.0
*		glDepthFunc								1.0								1.0
*		glDepthBoundsEXT						EXT_depth_bounds_test			Not Support
* 		glEnable(GL_DEPTH_TEST) 				1.0								1.0
*		glDisable(GL_DEPTH_TEST)				1.0								1.0
*		glEnable(GL_DEPTH_BOUNDS_TEST_EXT)		EXT_depth_bounds_test			Not Support
*		glDisable(GL_DEPTH_BOUNDS_TEST_EXT) 	EXT_depth_bounds_test			Not Support
*/

/*
*	Chapter. Stencil Test
* 	1. API Table
* 												OpenGL							ES
*		glDepthMask								2.0								2.0
*		glDepthFunc								2.0								2.0
*		glDepthBoundsEXT						EXT_depth_bounds_test			Not Support
* 		glEnable(GL_DEPTH_TEST)					1.0								1.0
*		glDisable(GL_DEPTH_TEST)				1.0								1.0
*		glEnable(GL_DEPTH_BOUNDS_TEST_EXT)		EXT_depth_bounds_test			Not Support
*		glDisable(GL_DEPTH_BOUNDS_TEST_EXT) 	EXT_depth_bounds_test			Not Support
*/

/*
*	Chapter. Scissor Test
*/

/*
*	Chapter. Viewport
 * 	1. API Table
* 												OpenGL							ES
*	glViewport									2.0								2.0
*	glDepthRange								2.0								Not Support
*	glDepthRangef								4.1								2.0
*	glDepthRangeArray
*	glDepthRangeArrayv
*	glDepthRangeIndexed
*/

/*
*	Chapter. Logical Operation
*/

/*
*	Chapter. Multisampling
*/


/*
*	Chapter. FrameBuffer
*	1. API Table
*												OpenGL							ES
*		glGenFramebuffers						3.0								2.0
*		glDeleteFramebuffers					3.0								2.0
*		glBindFramebuffer						3.0								2.0
*		glIsFramebuffer
*		glFramebufferParameteri
* 		glNamedFramebufferParameteri
*		glGetFramebufferParameteriv
* 		glGetNamedFramebufferParameteriv
*		glFramebufferTexture					3.2
*		glNamedFramebufferTexture				3.2
*		glFramebufferTexture1D					3.0
*		glFramebufferTexture2D					3.0								2.0
*		glFramebufferTexture3D					3.0
*		glDrawBuffer							1.0								Not Support
*		glNamedFramebufferDrawBuffer			4.5 							Not Support
*		glDrawBuffers							2.0								3.0
*		glNamedFramebufferDrawBuffers			4.5 							Not Support
*		glReadBuffer							1.0								3.0
*		glNamedFramebufferReadBuffer			4.5 							Not Support
*		glInvalidateFramebuffer					4.3								3.0
*		glInvalidateNamedFramebufferData		4.5 							Not Support
*		glInvalidateSubFramebuffer				4.3								3.0
*		glInvalidateNamedFramebufferSubData		4.5 							Not Support
*		glGenRenderbuffers						3.0								2.0
*		glFramebufferRenderbuffer				3.0								2.0
*		glNamedFramebufferRenderbuffer	
*		glFramebufferTextureLayer				3.0								3.0
*		glNamedFramebufferTextureLayer
*		glClearBufferfi
*		glClearBufferfv
*		glClearBufferiv
*		glClearBufferuiv
*		glClearNamedFramebufferfi
*		glClearNamedFramebufferfv
*		glClearNamedFramebufferiv
*		glClearNamedFramebufferuiv
*		glColorMask
*		glColorMaski
*	2. Framebuffer Object
*		glGenFramebuffers	
* 		glDeleteFramebuffers
* 		glBindFramebuffer	
*		glIsFramebuffer
*	2. Framebuffer Object Parameters
*		glFramebufferParameteri
*		glNamedFramebufferParameteri
*	2. Framebuffer Object Queries
*		glGetFramebufferParameteriv
*		glGetNamedFramebufferParameteriv
*	2. Renderbuffer Objects
*		glCreateRenderbuffers
*		glGenRenderbuffers
*		glDeleteRenderbuffers
*		glBindRenderbuffer
*		glIsRenderbuffer
*		glRenderbufferStorageMultisample
*		glNamedRenderbufferStorageMultisample
*		glRenderbufferStorage
*		glNamedRenderbufferStorage
*	2.	Renderbuffer Object Queries
*		glGetRenderbufferParameteriv
*		glGetNamedRenderbufferParameteriv
*	2. Attaching Renderbuffer Images to a Framebuffer
*		glFramebufferRenderbuffer
*		glNamedFramebufferRenderbuffer
*	2. Attaching Texture Images to a Framebuffer
*		glFramebufferTexture		
*		glNamedFramebufferTexture	
*		glFramebufferTexture1D		
*		glFramebufferTexture2D		
*		glFramebufferTexture3D		
*	2. Selecting Buffers for Writing
* 		glDrawBuffer				
*		glNamedFramebufferDrawBuffer
*		glDrawBuffers				
*		glNamedFramebufferDrawBuffers
*	3. Fine Control of Buffer Updates
*		glColorMask
*		glColorMaski
*	3. Clearing the Buffers
*		glClear
*		glClearColor
*		glClearDepth
*		glClearDepthf
*		glClearStencil
*	4. Clearing Individual Buffers
*		glClearBufferfv
*		glClearNamedFramebufferfv
*		glClearBufferiv
*		glClearNamedFramebufferiv
*		glClearBufferuiv
*		glClearNamedFramebufferuiv
* 		glClearBufferfi
*		glClearNamedFramebufferfi
*	5. Invalidating Framebuffer Contents
*		glInvalidateFramebuffer				
*		glInvalidateNamedFramebufferData	
*		glInvalidateSubFramebuffer			
*		glInvalidateNamedFramebufferSubData
*	6. Selecting Buffers for Reading
*		glReadBuffer				
* 		glNamedFramebufferReadBuffer
*	7. ReadPixels
*		glReadPixels
*		glReadnPixels
*	8. Final Conversion
*		glClampColor
*   9. Blitting Pixel Rectangles
*		glBlitFramebuffer
*		glBlitNamedFramebuffer
*	10. Copying Between Images
*		glCopyImageSubData
*/