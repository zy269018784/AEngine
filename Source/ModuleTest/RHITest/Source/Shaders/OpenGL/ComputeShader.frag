#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
layout (std430, binding = 0) buffer ShaderStorageBlock
{
	vec4 Color[32][32];
} ImageData;

void main()
{
	//int x = int(floor(TexCoord.x + 0.5f)) * 32;
	//int y = int(floor(TexCoord.y + 0.5f)) * 32;
	
	int x = int(TexCoord.x * 32);
	int y = int(TexCoord.y * 32);
	FragColor = ImageData.Color[x][y];
}
