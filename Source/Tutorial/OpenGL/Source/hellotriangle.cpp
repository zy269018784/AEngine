#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void glfwErrorCallback(int error, const char *desc)
{
    std::cout << "error " << error << " desc " << desc << std::endl;
}

// 顶点着色器源码 (ES 2.0)
const char* vertexShaderSource = R"(
    attribute vec2 aPos;
    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

// 片段着色器源码 (ES 2.0)
const char* fragmentShaderSource = R"(
    void main() {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

// 检查着色器编译状态
GLuint checkShaderCompile(GLuint shader)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader compilation failed:\n" << infoLog << std::endl;
    }
    return success;
}

// 检查程序链接状态
GLuint checkProgramLink(GLuint program)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Program linking failed:\n" << infoLog << std::endl;
    }
    return success;
}

int helotrianle(int argc, char **argv) 
{
    // 设置错误回调
    glfwSetErrorCallback(glfwErrorCallback);
    
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cout << "init error" << std::endl;
        return -1;
    }
    
    // 配置 OpenGL ES 2.0
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    // 创建窗口
    auto Handle = glfwCreateWindow(800, 600, "Triangle - OpenGL ES 2.0", NULL, NULL);
    if (!Handle) {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "glfw handle " << Handle << std::endl;
    
    glfwMakeContextCurrent(Handle);
    
    // 加载 OpenGL ES 2.0 函数
    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "gladLoadGLES2 failed" << std::endl;
        return -1;
    }
    
    std::cout << "OpenGL ES Version: " << glGetString(GL_VERSION) << std::endl;
    
    // 1. 创建顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    if (!checkShaderCompile(vertexShader)) return -1;
    
    // 2. 创建片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    if (!checkShaderCompile(fragmentShader)) return -1;
    
    // 3. 创建着色器程序并链接
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    if (!checkProgramLink(shaderProgram)) return -1;
    
    // 4. 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 5. 设置顶点数据（三角形三个顶点）
    GLfloat vertices[] = {
         0.0f,  0.5f,  // 顶部
        -0.5f, -0.5f,  // 左下
         0.5f, -0.5f   // 右下
    };
    
    // 6. 创建 VBO（ES 2.0 只需要 VBO，不需要 VAO）
    GLuint VBO;
    glGenBuffers(1, &VBO);
    
    // 绑定并填充 VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 7. 获取顶点属性位置
    GLuint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
    
    // 8. 设置顶点属性指针（直接设置，不需要 VAO）
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(posAttrib);
    
    // 注意：ES 2.0 中，顶点属性配置直接绑定到当前的 GL_ARRAY_BUFFER
    // 不需要 VAO，每次绘制前重新设置即可
    
    // 主循环
    while (!glfwWindowShouldClose(Handle))
    {
        // 清屏
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 使用着色器程序
        glUseProgram(shaderProgram);
        
        // 每次绘制前需要重新绑定 VBO 和设置顶点属性
        // （因为 ES 2.0 没有 VAO 来保存这些状态）
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(posAttrib);
        
        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // 交换缓冲区
        glfwSwapBuffers(Handle);
        glfwPollEvents();
    }
    
    // 清理资源
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
    return 0;
}
