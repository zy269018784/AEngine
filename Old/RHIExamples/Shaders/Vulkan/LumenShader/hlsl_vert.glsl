#version 450

layout(binding = 0, std140) uniform _Global
{
    vec4 _RESERVED_IDENTIFIER_FIXUP_gl_HalfPixel;
} _42;

layout(location = 0) in vec3 stage_input_aPos;
layout(location = 1) in vec3 stage_input_aColor;
layout(location = 0) out vec3 _entryPointOutput_outColor;
layout(location = 1) out vec4 _entryPointOutput_gl_Position;
vec3 outColor;
vec3 aColor;
vec4 _RESERVED_IDENTIFIER_FIXUP_gl_Position;
vec3 aPos;

void main()
{
    aColor = stage_input_aColor;
    aPos = stage_input_aPos;
    outColor = aColor;
    _RESERVED_IDENTIFIER_FIXUP_gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    _RESERVED_IDENTIFIER_FIXUP_gl_Position.x = fma(-_42._RESERVED_IDENTIFIER_FIXUP_gl_HalfPixel.x, _RESERVED_IDENTIFIER_FIXUP_gl_Position.w, _RESERVED_IDENTIFIER_FIXUP_gl_Position.x);
    _RESERVED_IDENTIFIER_FIXUP_gl_Position.y = fma(_42._RESERVED_IDENTIFIER_FIXUP_gl_HalfPixel.y, _RESERVED_IDENTIFIER_FIXUP_gl_Position.w, _RESERVED_IDENTIFIER_FIXUP_gl_Position.y);
    _entryPointOutput_outColor = outColor;
    _entryPointOutput_gl_Position = _RESERVED_IDENTIFIER_FIXUP_gl_Position;
}

