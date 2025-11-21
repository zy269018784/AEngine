#version 460
layout (binding = 0) uniform samplerCubeArray cubemapArray;
layout (location = 0) out vec4 outColor;
layout (location = 0) in vec3 inTexCoord;
void main()
{
#if 1
    outColor = texture(cubemapArray, vec4(normalize(inTexCoord), 0));
	//outColor = texture(cubemapArray, vec4(1, 0, 0, 0));
	//outColor = texture(cubemapArray, normalize(vec4(inTexCoord, 0)));
#else
	outColor = vec4(1, 1, 0, 0);
#endif
}
