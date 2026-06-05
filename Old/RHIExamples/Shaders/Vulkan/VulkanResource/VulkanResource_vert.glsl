#version 460

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec3 outNormal;


void main()
{
	outColor = aColor;
	outNormal = aNormal;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

