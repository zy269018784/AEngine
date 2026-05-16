#include <iostream>
#include "GLFW_Include.h"
#include "Shaders/Shaders.h"
#include "Common/ErrorCheck.h"
int OpenGL20_Triangle(int argc, char **argv)
{
    // 1. 初始化 GLFW
    if (!glfwInit())
    {
        std::cout << "init error" << std::endl;
        return -1;
    }
    glfwSetErrorCallback(GLFWErrorCallback);

    // 设置 OpenGL 版本为 2.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    // 2. 创建窗口
    auto Handle = glfwCreateWindow(800, 600, "OpenGL 2.0 Triangle", NULL, NULL);
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

    std::cout << "glGenVertexArrays " << glGenVertexArrays<< std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // 4. 顶点着色器 (GLSL 1.20)
    const char* vertexShaderSource = "#version 120\n"
    "attribute vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

    // 5. 片段着色器 (GLSL 1.20)
    const char* fragmentShaderSource = "#version 120\n"
    "void main()\n"
    "{\n"
    "   gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\0";

    // 编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    CheckShaderCompileError(vertexShader, "VERTEX");

    // 编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    CheckShaderCompileError(fragmentShader, "FRAGMENT");

    // 链接着色器程序
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckProgramLinkError(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 6. 设置顶点数据
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // OpenGL 2.0 使用 VBO，不使用 VAO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 获取属性位置
    GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // 渲染循环
    while (!glfwWindowShouldClose(Handle))
    {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(Handle);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(Handle);
    glfwTerminate();
    return 0;
}