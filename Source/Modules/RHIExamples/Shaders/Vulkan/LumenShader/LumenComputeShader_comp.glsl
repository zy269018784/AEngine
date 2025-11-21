#version 460
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(binding = 0, std430) buffer RWVoxelVisBuffer
{
    uint _data[];
} RWVoxelVisBuffer_1;

void main()
{
    RWVoxelVisBuffer_1._data[0] = 2u;
    RWVoxelVisBuffer_1._data[1] = 8u;
    RWVoxelVisBuffer_1._data[2] = 2u;
    RWVoxelVisBuffer_1._data[3] = 5u;
}

