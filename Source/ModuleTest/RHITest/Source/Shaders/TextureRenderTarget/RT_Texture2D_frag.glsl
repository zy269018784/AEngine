#version 460 core

// 为采样器指定绑定的纹理单元
layout(binding = 0) uniform sampler2D texSampler;
layout(binding = 1) uniform sampler2D texSampler2;
layout(binding = 2) uniform sampler2D texSampler3;

// 为输入变量指定 location（对应顶点着色器的输出 location）
layout(location = 0) in vec2 fragTexCoord;

// 为输出变量指定 location
layout(location = 0) out vec4 outColor;

void main()
{
    // 使用 texture() 函数
    vec4 color1 = texture(texSampler, fragTexCoord);
    vec4 color2 = texture(texSampler2, fragTexCoord);
    vec4 color3 = texture(texSampler3, fragTexCoord);

    outColor = color1;  // 或其他组合
}