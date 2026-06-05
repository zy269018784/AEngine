#version 460
layout (location = 0) out vec4 outColor;
layout (location = 0) in vec2 fragTexCoord;
layout (binding = 1) uniform sampler2D texSampler;

void main()
{
	outColor = texture(texSampler, fragTexCoord);
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

