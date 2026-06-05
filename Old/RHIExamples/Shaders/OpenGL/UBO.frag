#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D Texture;
layout (std140, binding = 0) uniform UniformBlock1
{
	float Scale[4];
} UBO1;

layout (std140, binding = 1) uniform UniformBlock2
{
	vec4  Color[4];
} UBO2;
void main()
{
	vec4 Color = UBO1.Scale[0] * UBO2.Color[0];
	vec4 TexColor = texture(Texture, TexCoord);
	FragColor = mix(Color, TexColor, 0.5f);
}
