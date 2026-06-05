#version 460

layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec3 outColor;

layout (binding = 0) uniform UniformBlock1
{
	vec4 color;
} UBO1;


layout (binding = 1) uniform UniformBlock2
{
	vec4 color;
} UBO2;

layout (binding = 2) uniform UniformBlock3
{
	vec4 color;
} UBO3;

layout (binding = 3) uniform UniformBlock4
{
	vec4 color;
} UBO4;

void main()
{
	FragColor = vec4(UBO4.color.xyz, 1.0f);
}

