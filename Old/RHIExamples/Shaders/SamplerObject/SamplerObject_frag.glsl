#version 460
layout (binding = 0) uniform sampler2D texSampler0;
layout (binding = 1) uniform sampler2D texSampler1;
layout (binding = 2) uniform sampler2D texSampler2;
layout (binding = 3) uniform sampler2D texSampler3;
layout (location = 0) in vec3 fragTexCoord;
layout (location = 0) out vec4 outColor;

void main()
{
	float TextureIndex = fragTexCoord.z;
	if (TextureIndex < 1)
	{
		outColor = texture(texSampler0, fragTexCoord.xy);
	}
	else if (TextureIndex < 2)
	{
		outColor = texture(texSampler1, fragTexCoord.xy);
	}
	else if (TextureIndex < 3)
	{
		outColor = texture(texSampler2, fragTexCoord.xy);
	}
	else if (TextureIndex < 4)
	{
		outColor = texture(texSampler3, fragTexCoord.xy);
	}
}
