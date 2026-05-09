static const uint3 gl_WorkGroupSize = uint3(1u, 1u, 1u);

RWStructuredBuffer<uint> RWVoxelVisBuffer;

void comp_main()
{
    RWVoxelVisBuffer[0] = 1u;
    RWVoxelVisBuffer[1] = 8u;
    RWVoxelVisBuffer[2] = 2u;
    RWVoxelVisBuffer[3] = 5u;
}

[numthreads(1, 1, 1)]
void hellomain()
{
    RWVoxelVisBuffer[0] = 1u;
    RWVoxelVisBuffer[1] = 8u;
    RWVoxelVisBuffer[2] = 2u;
    RWVoxelVisBuffer[3] = 5u;
}

[numthreads(1, 1, 1)]
void main()
{
    RWVoxelVisBuffer[0] = 2u;
    RWVoxelVisBuffer[1] = 8u;
    RWVoxelVisBuffer[2] = 2u;
    RWVoxelVisBuffer[3] = 5u;
}
