#version 460

layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec3 outColor;

layout (binding = 0, std430) readonly buffer StorageBuffer1
{
    vec4 color;
} SSBO1;

layout(binding = 1, std430) readonly buffer StorageBuffer2
{
    vec4 color;
} SSBO2;

layout (binding = 2, std430) readonly buffer StorageBuffer3
{
    vec4 color;
} SSBO3;

layout (binding = 3, std430) readonly buffer StorageBuffer4
{
    vec4 color;
} SSBO4;

void main()
{
    FragColor = vec4(SSBO4.color.xyz, 1.0);
}

