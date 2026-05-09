RWStructuredBuffer<uint> RWVoxelVisBuffer;

static float4 FragColor;
static float3 outColor;

struct SPIRV_Cross_Input
{
    float3 outColor : TEXCOORD0;
};

struct SPIRV_Cross_Output
{
    float4 FragColor : COLOR0;
};

void frag_main()
{
    if (RWVoxelVisBuffer[0] == 1u)
    {
        FragColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        if (RWVoxelVisBuffer[0] == 8u)
        {
            FragColor = float4(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else
        {
            FragColor = 1.0f.xxxx;
        }
    }
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    outColor = stage_input.outColor;
    frag_main();
    SPIRV_Cross_Output stage_output;
    stage_output.FragColor = float4(FragColor);
    return stage_output;
}
