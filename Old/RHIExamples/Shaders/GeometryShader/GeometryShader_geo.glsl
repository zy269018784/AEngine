#version 460

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

layout(location = 0) in vec3 inColor[];
layout(location = 0) out vec3 outColor;

void main() {
    // 遍历三角形的3个顶点
    for(int i = 0; i < 3; i++) {
        // 设置位置（直接传递）
        gl_Position = gl_in[i].gl_Position;
        gl_Position.x += 0.5f;
        // 传递颜色
        //outColor = inColor[i];
		outColor = vec3(1, 0, 0);
        
        // 发射顶点
        EmitVertex();
    }
    
    // 结束图元
    EndPrimitive();
}