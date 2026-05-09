
// ============================================================================
// 文件名: main.cpp
// 描述: 使用 OpenGL 3.3 + GLAD + GLFW 绘制一个三角形的演示程序
// 编译: g++ main.cpp -o triangle -lglfw -ldl
// 运行: ./triangle
// ============================================================================
#if  PROJECT_USE_GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ----------------------------------------------------------------------------
// 窗口尺寸回调函数
// ----------------------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// ----------------------------------------------------------------------------
// 处理输入
// ----------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// ----------------------------------------------------------------------------
// 顶点着色器源代码 (GLSL 330 core)
// ----------------------------------------------------------------------------
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

// ----------------------------------------------------------------------------
// 片段着色器源代码 (GLSL 330 core)
// ----------------------------------------------------------------------------
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.2f, 0.6f, 0.8f, 1.0f);
}
)";

// ----------------------------------------------------------------------------
// 编译着色器并创建着色器程序
// ----------------------------------------------------------------------------
unsigned int createShaderProgram()
{
    // 1. 创建并编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 检查顶点着色器编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 2. 创建并编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // 检查片段着色器编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 3. 创建着色器程序并链接
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检查链接错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 4. 清理着色器对象（已链接到程序，不再需要）
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// ----------------------------------------------------------------------------
// 主函数
// ----------------------------------------------------------------------------

int TestOpenGL(int argc, char* argv[])
{
    // ==================== 1. 初始化 GLFW ====================
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if  __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macOS 需要
#endif

    // ==================== 2. 创建窗口 ====================
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Triangle - GLAD", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ==================== 3. 初始化 GLAD ====================
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ==================== 4. 构建着色器程序 ====================
    unsigned int shaderProgram = createShaderProgram();

    // ==================== 5. 设置顶点数据 ====================
    // 三个顶点位置（标准化设备坐标，范围 -1 到 1）
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // 左下角
         0.5f, -0.5f, 0.0f,  // 右下角
         0.0f,  0.5f, 0.0f   // 顶部
    };

    // 顶点缓冲对象 (VBO) 和 顶点数组对象 (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 1) 绑定 VAO
    glBindVertexArray(VAO);

    // 2) 绑定并填充 VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3) 设置顶点属性指针
    // 位置属性: location = 0, 3个float, 不归一化, 步长3*sizeof(float), 偏移0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 解绑 VBO 和 VAO（可选，但有利于组织）
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 可选：启用线框模式（便于观察边界，默认是填充模式）
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // ==================== 6. 渲染循环 ====================
    while (!glfwWindowShouldClose(window))
    {
        // 处理输入
        processInput(window);

        // 设置清屏颜色（深灰色）
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);

        // 绑定 VAO 并绘制三角形
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换前后缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ==================== 7. 清理资源 ====================
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
#endif
