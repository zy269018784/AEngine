#version 460

layout(binding = 0) uniform usampler1D texSampler1;
layout(binding = 1) uniform sampler2D texSampler2;


layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 fragColor;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor.r = texture(texSampler1, 0).r;
	outColor.g = texture(texSampler1, 0.50).r;
	outColor.b = texture(texSampler1, 0.51).r;
}
