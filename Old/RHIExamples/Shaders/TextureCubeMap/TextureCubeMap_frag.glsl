#version 460
layout (binding = 0) uniform samplerCube cubemap; 
layout (location = 0) out vec4 outColor;
layout (location = 0) in vec2 inTexCoord;
void main()
{
#if 1
    outColor = texture(cubemap, vec3(-1, inTexCoord));
#else
	outColor = vec4(1, 0, 0, 0);
#endif
}
