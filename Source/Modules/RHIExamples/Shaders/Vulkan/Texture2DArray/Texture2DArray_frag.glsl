#version 450

layout(binding = 0) uniform sampler2D texSampler;
layout(binding = 1) uniform sampler2DArray  texArraySampler;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 fragColor;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = texture(texSampler, fragTexCoord);
	vec3 UVW = vec3(fragTexCoord.xy, 0);
	outColor = texture(texArraySampler, UVW);
	
	//outColor = texture(texSampler, fragTexCoord);
}
