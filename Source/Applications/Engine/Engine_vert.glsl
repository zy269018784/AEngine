#version 460
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

layout (binding = 0) uniform UniformBlock1
{
	mat4 mvp;
} UBO1;

void main() 
{
    fragTexCoord 	= inTexCoord;
    //gl_Position = vec4(inPosition, 1.0);
    gl_Position = UBO1.mvp * inPosition;
}
