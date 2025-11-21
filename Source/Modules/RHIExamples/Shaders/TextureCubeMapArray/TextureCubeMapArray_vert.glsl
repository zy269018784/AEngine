#version 460
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inTexCoord;
layout (location = 0) out vec3 outTexCoord;
void main() 
{
	outTexCoord = inPosition;
	gl_Position = vec4(inPosition, 1.0);
}
