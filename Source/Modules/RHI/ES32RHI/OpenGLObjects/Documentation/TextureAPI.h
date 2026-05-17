/*
*	Chapter. Texture
*	1. API Table
*												                             OpenGL					ES
*		glGenTextures							                    2.0								2.0
*		glDeleteTextures				                            2.0								2.0
*		glBindTexture							                    2.0								2.0
*		glActiveTexture					                            2.0								2.0
*		glTexImage1D							                    2.0								Not Supported
*		glTexImage2D							                    2.0								2.0
*		glTexImage3D							                    2.0								3.0
*		glTexSubImage1D							                    2.0								Not Supported
*		glTextureSubImage1D						                    4.5								Not Supported
*		glTexSubImage2D							                    2.0								2.0
*		glTextureSubImage2D						                    4.5								Not Supported
*		glTexSubImage3D							                    2.0								3.0
*		glTextureSubImage3D						                    4.5								Not Supported
*		glTexImage2DMultisample				                        2.0								Not Supported
*		glTexImage3DMultisample				                        3.2								Not Supported
*		glTexStorage1D							                    4.2								Not Supported
*		glTextureStorage1D						                    4.5								Not Supported
*		glTexStorage2D							                    4.2								3.0
*		glTextureStorage2D						                    4.5								Not Supported
*		glTexStorage3D							                    4.2								3.0
*		glTextureStorage3D						                    4.5								Not Supported
*		glTexStorage2DMultisample				                    4.3								3.1
*		glTextureStorage2DMultisample			                    4.5								Not Supported
*		glTexStorage3DMultisample				                    4.3								3.2
*		glTextureStorage3DMultisample			                    4.5								Not Supported
*		glTexBuffer							   	                    3.1								3.2
*		glTextureBuffer							                    4.5								Not Supported
*		glTexBufferRange						                    4.3								3.2
*		glTextureBufferRange					                    4.5								Not Supported
*		glTexParameterf							                    2.0								2.0
*		glTextureParameterf						                    4.5								Not Supported
*		glTexParameteri							                    2.0								2.0
*		glTextureParameteri						                    4.5								Not Supported
*		glTexParameterfv						                    2.0								2.0
*		glTextureParameterfv					                    4.5								Not Supported
*		glTexParameteriv						                    2.0								2.0
*		glTextureParameteriv					                    4.5								Not Supported
*		glTexParameterIiv						                    3.0								3.2
*		glTextureParameterIiv				                        4.5								Not Supported
*		glTexParameterIuiv						                    3.0								3.2
*		glTextureParameterIuiv			                            4.5								Not Supported
*		glTextureBarrier						                    4.5								Not Supported
*		glTextureView						     	                4.3								Not Supported
*		glGenerateMipmap						                    3.0								2.0
*		glGenerateTextureMipmap		                                4.5								Not Supported
*		glCopyTexImage1D						                    2.0								Not Supported
*		glCopyTexImage2D						                    2.0								2.0
*		glCopyTexSubImage1D						                    2.0								Not Supported
*		glCopyTextureSubImage1D	                                    4.5								Not Supported
*		glCopyTexSubImage2D						                    2.0								2.0
*		glCopyTextureSubImage2D		                                4.5								Not Supported
*		glCopyTexSubImage3D						                    2.0								3.0
*		glCopyTextureSubImage3D		                                4.5								Not Supported
*		glCompressedTexImage1D			                            2.0								Not Supported
*		glCompressedTexImage2D			                            2.0								2.0
*		glCompressedTexImage3D			                            2.0								3.0
*		glCompressedTexSubImage1D				                    2.0								Not Supported
*		glCompressedTextureSubImage1D			                    4.5								Not Supported
*		glCompressedTexSubImage2D				                    2.0								2.0
*		glCompressedTextureSubImage2D			                    4.5								Not Supported
*		glCompressedTexSubImage3D				                    2.0								3.0
*		glCompressedTextureSubImage3D			                    4.5								Not Supported
*		glCopyImageSubData						                    4.3								3.2
*		glBindTextureUnit						                    4.5								Not Supported
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
*        void glTexImage2D(GLenum target,              // 目标
* 	                        GLint level,
* 	                        GLint internalformat,       // 内部格式
* 	                        GLsizei width,              // 图像宽度
* 	                        GLsizei height,             // 图像高度
* 	                        GLint border,               // 必须为0
* 	                        GLenum format,              // 像素格式
* 	                        GLenum type,
* 	                        const void * data);
*
*        void glTexStorage2D(GLenum target,
* 	                          GLsizei levels,
* 	                          GLenum internalformat,    // 内部格式
* 	                          GLsizei width,            // 图像宽度
* 	                          GLsizei height);          // 图像高度
*
*		      void glTexSubImage2D(GLenum target,
* 	                           GLint level,
* 	                           GLint xoffset,           // x偏移
* 	                           GLint yoffset,           // y偏移
* 	                           GLsizei width,           // 图像宽度
* 	                           GLsizei height,          // 图像高度
* 	                           GLenum format,           // 像素格式
* 	                           GLenum type,
* 	                           const void * pixels);    // 像素数据
* 	  format:
* 	       GL_RED,
* 	       GL_RG,
* 	       GL_RGB,
* 	       GL_BGR,
* 	       GL_RGBA,
* 	       GL_BGRA,
* 	       GL_RED_INTEGER,
* 	       GL_RG_INTEGER,
* 	       GL_RGB_INTEGER,
* 	       GL_BGR_INTEGER,
* 	       GL_RGBA_INTEGER,
* 	       GL_BGRA_INTEGER,
* 	       GL_STENCIL_INDEX,
* 	       GL_DEPTH_COMPONENT,
* 	       GL_DEPTH_STENCIL
*
* 	  type:
* 	       GL_UNSIGNED_BYTE
* 	       GL_BYTE
* 	       GL_UNSIGNED_SHORT
* 	       GL_SHORT
* 	       GL_UNSIGNED_INT
* 	       GL_INT
* 	       GL_HALF_FLOAT
* 	       GL_FLOAT
* 	       GL_UNSIGNED_BYTE_3_3_2
* 	       GL_UNSIGNED_BYTE_2_3_3_REV
* 	       GL_UNSIGNED_SHORT_5_6_5
* 	       GL_UNSIGNED_SHORT_5_6_5_REV
* 	       GL_UNSIGNED_SHORT_4_4_4_4
* 	       GL_UNSIGNED_SHORT_4_4_4_4_REV
* 	       GL_UNSIGNED_SHORT_5_5_5_1
* 	       GL_UNSIGNED_SHORT_1_5_5_5_REV
* 	       GL_UNSIGNED_INT_8_8_8_8
* 	       GL_UNSIGNED_INT_8_8_8_8_REV
* 	       GL_UNSIGNED_INT_10_10_10_2
* 	       GL_UNSIGNED_INT_2_10_10_10_REV
*
* 2.2 ES 2.0 Texture
*  创建     glGenTextures
*  绑定     glBindTexture
*  指定格式  glTexImage1D, glTexImage2D
*  上传数据  glTexSubImage2D
*
* 2.3 ES 3.0 Texture
*  创建     glGenTextures
*  绑定     glBindTexture
*  指定格式  glTexStorage2D, glTexStorage3D，
*  上传数据  glTexSubImage2D, glTexSubImage3D
*
* 2.4 ES 3.1 Texture
*  创建     glGenTextures
*  绑定     glBindTexture
*  指定格式  glTexStorage2D, glTexStorage3D，
*  上传数据  glTexSubImage2D, glTexSubImage3D
*
* 2.5 ES 3.2 Texture
*  创建     glGenTextures
*  绑定     glBindTexture
*  指定格式  glTexStorage2D, glTexStorage3D，
*  上传数据  glTexSubImage2D, glTexSubImage3D
*
* 2.6 ES 3.2 Texture
*  创建     glGenTextures
*  绑定     glBindTexture
*  指定格式  glTexStorage2D, glTexStorage3D，
*  上传数据  glTexSubImage2D, glTexSubImage3D
*
* 2.7 OpenGL 3.3 Texture
*  创建     glGenTextures
*  绑定     glBindTexture
*  指定格式  glTexImage1D, glTexImage2D, glTexImage3D
*  上传数据  glTexSubImage1D, glTexSubImage2D, glTexSubImage3D
*
* 2.8 OpenGL 4.6 Texture
*  创建     glGenTextures
*  绑定     glBindTexture
*  指定格式  glTexStorage1D, glTexStorage2D, glTexStorage3D， glTextureStorage1D， glTextureStorage2D， glTextureStorage3D
*  上传数据  glTexSubImage1D, glTexSubImage2D, glTexSubImage3D, glTextureSubImage1D, glTextureSubImage2D, glTextureSubImage3D
*
*	3. Sample Objects
* 4. glsl
*		4.1 1D Texture
*			uniform sampler1D texSampler;
*			float u
*			vec4 outColor = texture(texSampler u);
*		4.2 1D Texture Array
*			uniform sampler1DArray  texArraySampler;
* 			float layer;
*			vec2 UV = vec2(u layer);
*			vec4 outColor = texture(texArraySampler UV);
*		4.3 2D Texture
*			uniform sampler2D texSampler;
*			vec4 outColor = texture(texSampler vec2(u v));
*		4.4 2D Texture Array
*			uniform sampler2DArray  texArraySampler;
*			float layer;
*			vec3 UVW = vec3(uv layer);
*			vec4 outColor = texture(texArraySampler UVW);
*		4.5 3D Texture
*			uniform sampler3D texSampler;
*			vec3 UVW = vec3(u v w);
*			vec4 vec4 color = texture(texSampler UVW);
*		4.6 CubeMap
*			uniform samplerCube cubemap
*			vec3 dir;
*			vec3 UVW = normalize(dir);
*			vec4 outColor = texture(cubemap UVW);
*		4.7 CubeMap Array
*			uniform samplerCubeArray cubemapArray;
*			float layer;
*			vec3 dir;
*			vec3 UVW = normalize(dir);
*			vec4 UVWZ = vec4(UVW layer);
*			vec4 outColor = texture(cubemapArray vec4(normalize(inTexCoord) 0));
*/