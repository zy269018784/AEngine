#version 460
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout(location = 0) out vec2 fragTexCoord;

layout (binding = 0) uniform UniformBlock1
{
	mat4 mvp;
} UBO1;

void main()
{
	fragTexCoord = aUV;
    gl_Position = UBO1.mvp * vec4(aPos, 1.0);
}

