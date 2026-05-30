#version 100  // ES 2.0 使用 version 100

attribute vec3 inPosition;
attribute vec2 inTexCoord;

varying vec2 fragTexCoord;

void main()
{
    fragTexCoord = inTexCoord;
    gl_Position = vec4(inPosition, 1.0);
}