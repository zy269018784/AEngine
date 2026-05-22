#version 460
layout (binding = 0) uniform texture2D Texture;
layout (binding = 1) uniform sampler texSampler;

layout (location = 0) in vec2 fragTexCoord;
layout (location = 0) out vec4 outColor;

void main()
{
	outColor = texture(sampler2D(Texture, texSampler), fragTexCoord);
    //outColor = texture(texSampler, fragTexCoord);
}
