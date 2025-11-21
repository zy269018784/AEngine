#version 460

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec3 outColor;
layout(location = 1) in vec3 outNormal;


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
#if 1
layout (binding = 0) buffer StorageBuffer1
{
	vec4 color;
} SSBO1;

layout (binding = 1) buffer StorageBuffer2
{
	vec4 color;
} SSBO2;

layout (binding = 2) buffer StorageBuffer3
{
	vec4 color;
} SSBO3;

layout (binding = 3) buffer StorageBuffer5
{
	vec4 color;
} SSBO4;

#endif


void main()
{

    //FragColor = vec4(outColor, 1.0);
	//FragColor = vec4(SSBO4.color.xyz, 1.0);
	FragColor = vec4(UBO1.color.xyz, 1.0);
}

