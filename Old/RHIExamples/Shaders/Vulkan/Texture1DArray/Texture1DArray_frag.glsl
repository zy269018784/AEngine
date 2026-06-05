#version 450
layout(binding = 0) uniform sampler1DArray  texArraySampler;
layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 fragColor;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	vec2 UV = vec2(fragTexCoord.x, 0);
	float Layer = 0;
	outColor = texture(texArraySampler, vec2(fragTexCoord.x, Layer));
}
