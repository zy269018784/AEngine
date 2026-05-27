#version 460
layout (binding = 0) uniform sampler2D texSampler;
layout (binding = 1) uniform sampler2D texSampler2;
layout (binding = 2) uniform sampler2D texSampler3;
layout (location = 0) in vec2 fragTexCoord;
layout (location = 0) out vec4 outColor;

void main()
{
    outColor = texture(texSampler, fragTexCoord);
}
