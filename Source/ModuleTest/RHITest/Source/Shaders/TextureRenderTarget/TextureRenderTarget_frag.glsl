#version 460
layout (binding = 0) uniform sampler2D texSampler;
layout (location = 0) in vec2 fragTexCoord;
layout (location = 0) out vec4 outColor0;
layout (location = 1) out vec4 outColor1;
layout (location = 2) out vec4 outColor2;

void main()
{
    outColor0 = vec4(1) * texture(texSampler, fragTexCoord);
    outColor1 = vec4(1, 0, 0, 0) * texture(texSampler, fragTexCoord);
    outColor2 = vec4(0, 1, 0, 0) * texture(texSampler, fragTexCoord);

    outColor0 = vec4(1, 0, 0, 0);
    outColor1 = vec4(0, 1, 0, 0);
    outColor2 = vec4(0, 0, 1, 0);
}
