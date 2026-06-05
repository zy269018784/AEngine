#version 460

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec3 outColor;
layout(location = 1) in vec3 outNormal;


void main()
{
	float a = dot(vec3(0, 0, 1), outNormal);
	vec3 Color = mix(outColor, vec3(1, 0, 0), a);
    FragColor = vec4(outColor, 1.0);
}

