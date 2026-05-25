// OpenGL ES 2.0 顶点着色器
// ES 2.0 不需要版本声明，或者使用 #version 100

// 使用 attribute 关键字声明顶点属性（对应 layout(location)）
attribute vec3 inPosition;
attribute vec2 inTexCoord;

// 使用 varying 关键字传递数据到片段着色器
varying vec2 vTexCoord;

void main() 
{
    // 传递纹理坐标
    vTexCoord = inTexCoord;
    
    // 设置顶点位置（gl_Position 是内置变量）
    gl_Position = vec4(inPosition, 1.0);
}