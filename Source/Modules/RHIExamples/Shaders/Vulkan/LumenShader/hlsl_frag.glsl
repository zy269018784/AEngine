#version 450

layout(binding = 0, std430) buffer RWVoxelVisBuffer
{
    uint _data[];
} RWVoxelVisBuffer_1;

layout(location = 0) out vec4 _entryPointOutput_FragColor;
vec4 FragColor;

void main()
{
    if (RWVoxelVisBuffer_1._data[0] == 1u)
    {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else
    {
        if (RWVoxelVisBuffer_1._data[0] == 8u)
        {
            FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        }
        else
        {
            FragColor = vec4(1.0);
        }
    }
    _entryPointOutput_FragColor = FragColor;
}

