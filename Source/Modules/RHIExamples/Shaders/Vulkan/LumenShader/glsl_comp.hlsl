static const uint3 gl_WorkGroupSize = uint3(1u, 1u, 1u);

RWByteAddressBuffer RWVoxelVisBuffer_1 : register(u0);

void comp_main()
{
    RWVoxelVisBuffer_1.Store(0, 2u);
    RWVoxelVisBuffer_1.Store(4, 8u);
    RWVoxelVisBuffer_1.Store(8, 2u);
    RWVoxelVisBuffer_1.Store(12, 5u);
}

[numthreads(1, 1, 1)]
void main()
{
    comp_main();
}
