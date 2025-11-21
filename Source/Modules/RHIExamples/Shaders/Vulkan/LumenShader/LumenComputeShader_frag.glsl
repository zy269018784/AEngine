#version 460

layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec3 outColor;

layout (binding = 0) buffer RWVoxelVisBuffer
{
	uint _data[];
} RWVoxelVisBuffer_1;

void main()
{
	if (RWVoxelVisBuffer_1._data[0] == 1)
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	else if (RWVoxelVisBuffer_1._data[1] == 8)
		FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	else
		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

