uniform float4 gl_HalfPixel;

static float4 gl_Position;
static float3 outColor;
static float3 aColor;
static float3 aPos;

struct SPIRV_Cross_Input
{
    float3 aPos : TEXCOORD0;
    float3 aColor : TEXCOORD1;
};

struct SPIRV_Cross_Output
{
    float3 outColor : TEXCOORD0;
    float4 gl_Position : POSITION;
};

void vert_main()
{
    outColor = aColor;
    gl_Position = float4(aPos.x, aPos.y, aPos.z, 1.0f);
    gl_Position.x = gl_Position.x - gl_HalfPixel.x * gl_Position.w;
    gl_Position.y = gl_Position.y + gl_HalfPixel.y * gl_Position.w;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    aColor = stage_input.aColor;
    aPos = stage_input.aPos;
    vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    stage_output.outColor = outColor;
    return stage_output;
}
