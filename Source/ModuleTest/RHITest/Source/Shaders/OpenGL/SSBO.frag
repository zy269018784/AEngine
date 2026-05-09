#version 460 core
out vec4 FragColor;

layout (std140, binding = 0) buffer ShaderStorageBlock1
{
	float Scale[4];
} SSBO1;

layout (std140, binding = 1) buffer ShaderStorageBlock2
{
	vec4  Color[4];
} SSBO2;

void main()
{
	vec4 Color = SSBO1.Scale[0] * SSBO2.Color[3];
	FragColor = Color;
}
