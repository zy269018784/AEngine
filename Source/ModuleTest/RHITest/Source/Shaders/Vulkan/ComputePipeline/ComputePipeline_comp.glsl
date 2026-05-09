#version 460

layout (local_size_x = 8, local_size_y = 1, local_size_z = 1) in;

layout (binding = 0) buffer StorageBuffer
{
	vec4 color[8];
} SSBO1;


void main()
{
	SSBO1.color[gl_GlobalInvocationID.x] = vec4(float(gl_GlobalInvocationID) / 8.f);
}

