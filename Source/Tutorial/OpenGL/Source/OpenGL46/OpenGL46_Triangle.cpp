#include <iostream>
#include "GLFW_Include.h"
#include "Shaders/Shaders.h"
#include "Common/ErrorCheck.h"

int OpenGL46_Triangle(int argc, char **argv)
{
    // 1. 初始化 GLFW
    if (!glfwInit())
    {
        std::cout << "init error" << std::endl;
        return -1;
    }
    glfwSetErrorCallback(GLFWErrorCallback);

    // 设置 OpenGL 版本为 4.6 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    // 2. 创建窗口
    auto Handle = glfwCreateWindow(800, 600, "OpenGL 4.6 Triangle", NULL, NULL);
    if (!Handle)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Handle);

    // 3. 加载 OpenGL 函数
    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        std::cout << "gladLoadGL failed!" << std::endl;
        return -1;
    }

    // 输出 OpenGL 版本信息
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // 4. 编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &TriangleVertexShader, NULL);
    glCompileShader(vertexShader);
    CheckShaderCompileError(vertexShader, "VERTEX");

    // 5. 编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &TriangleFragmentShader, NULL);
    glCompileShader(fragmentShader);
    CheckShaderCompileError(fragmentShader, "FRAGMENT");

    // 6. 链接着色器程序
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckProgramLinkError(shaderProgram);

    // 删除着色器对象（已链接到程序）
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 7. 设置顶点数据
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // 左下角
         0.5f, -0.5f, 0.0f,  // 右下角
         0.0f,  0.5f, 0.0f   // 顶部
    };

    // 8. 创建 VAO, VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 绑定 VAO
    glBindVertexArray(VAO);

    // 绑定并设置 VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 解绑（可选）
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 9. 渲染循环
    while (!glfwWindowShouldClose(Handle))
    {
        // 清屏（深蓝色背景）
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);

        // 绑定 VAO 并绘制三角形
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换缓冲区和处理事件
        glfwSwapBuffers(Handle);
        glfwPollEvents();
    }

    // 10. 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(Handle);
    glfwTerminate();
    return 0;
}