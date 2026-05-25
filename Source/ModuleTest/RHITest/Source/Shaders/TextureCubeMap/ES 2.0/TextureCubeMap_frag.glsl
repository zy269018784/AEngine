// OpenGL ES 2.0
precision highp float;

// ES 2.0 支持 samplerCube
uniform samplerCube cubemap;

// varying 变量（对应之前的 in）
varying vec2 outTexCoord;

void main()
{
    // 构造立方体纹理采样方向
    // 原代码: vec3(-1, outTexCoord)
    // outTexCoord.x 和 outTexCoord.y 提供另外两个坐标
    vec3 direction = vec3(-1.0, outTexCoord.x, outTexCoord.y);
    
    // ES 2.0 使用 textureCube 函数采样立方体贴图
    vec4 color = textureCube(cubemap, direction);
    
    // 使用内置输出变量
    gl_FragColor = color;
}