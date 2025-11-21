#version 460
layout (binding = 0) uniform sampler3D texSampler;
layout (location = 0) in vec2 fragTexCoord;
layout (location = 0) out vec4 outColor;

void main()
{
#if 0
	vec3 UVW = vec3(fragTexCoord, 1);
    outColor = texture(texSampler, UVW);
#else
	ivec3 P = ivec3(fragTexCoord.x * 32, fragTexCoord.x * 32, 3);
	outColor = texelFetch(texSampler, P, 0);
#endif
}
