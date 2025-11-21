#version 460
layout(binding = 0) uniform sampler2D texSampler;
layout(binding = 1) uniform sampler2DArray  texArraySampler;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 fragColor;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
#if 0
	vec3 UVW1 = vec3(fragTexCoord.xy, 0);
	vec3 UVW2 = vec3(fragTexCoord.xy, 1);
	outColor = texture(texArraySampler, UVW1);
#else
	outColor = texture(texSampler, fragTexCoord);
#endif
}
