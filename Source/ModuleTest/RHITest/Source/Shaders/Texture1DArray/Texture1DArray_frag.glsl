#version 460
layout(binding = 0) uniform sampler1DArray  texArraySampler;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 fragColor;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	int layer = 31;
	int lod = 0;
	//outColor = texelFetch(texArraySampler, ivec2(1, layer), lod);
	//outColor = texelFetch(texArraySampler, ivec2(fragTexCoord), lod);

	//outColor = texelFetch(texArraySampler, ivec2(fragTexCoord.x * 32, fragTexCoord.y * 32), lod);
	//outColor = texelFetch(texArraySampler, ivec2(fragTexCoord.x * 476, fragTexCoord.y * 476), lod);
	
	outColor = texture(texArraySampler, vec2(fragTexCoord.x, fragTexCoord.y * 476));
}
