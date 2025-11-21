#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
layout(binding = 0) uniform sampler2D texSampler;
void main()
{
   FragColor = texture(texSampler, TexCoord);
}
