#version 100  // ES 2.0 使用 version 100

precision highp float;  // ES 2.0 需要指定精度

uniform sampler2D texSampler;
uniform sampler2D texSampler2;
uniform sampler2D texSampler3;
varying vec2 fragTexCoord;

void main()
{
    // 示例：使用多个纹理的组合
    vec4 color1 = texture2D(texSampler, fragTexCoord);
    vec4 color2 = texture2D(texSampler2, fragTexCoord);
    vec4 color3 = texture2D(texSampler3, fragTexCoord);

    gl_FragColor = color1;  // 或其他组合
}