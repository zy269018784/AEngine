#version 460

layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec3 outColor;

layout (binding = 0) buffer StorageBuffer
{
	vec4 color[8];
} SSBO1;

void main()
{
	FragColor = vec4(SSBO1.color[0].x, SSBO1.color[0].y, SSBO1.color[0].z, 1.0f);
}

