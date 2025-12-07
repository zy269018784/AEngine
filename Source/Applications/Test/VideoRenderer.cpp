// VideoRenderer.cpp
#include "VideoRenderer.h"

#include "OpenGLObjects/Buffer/OpenGLBuffer.h"

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D videoTexture;

void main() {
    FragColor = texture(videoTexture, TexCoord);
}
)";

void VideoRenderer::CheckGLError(const char* context) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL错误 [" << context << "]: " << error << std::endl;
    }
}

bool VideoRenderer::Initialize() {
    if (initialized) return true;

    // 初始化GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW初始化失败" << std::endl;
        return false;
    }
#if 1
    Window = new GLFWWindow(IWindow::GraphicsAPI::OpenGL33);
    window = dynamic_cast<GLFWWindow *>(Window)->GetHandle();
#else 0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(windowWidth, windowHeight, "FFmpeg + OpenGL 播放器", nullptr, nullptr);
    if (!window) {
        std::cerr << "无法创建GLFW窗口" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
#endif
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    pRHI = new ES32RHI();

    std::cout << "OpenGL版本: " << glGetString(GL_VERSION) << std::endl;

    // 设置视口
    glViewport(0, 0, windowWidth, windowHeight);

    // 编译着色器
    if (!CompileShaders()) {
        return false;
    }

    // 设置四边形
    SetupQuad();

    // 设置混合
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initialized = true;
    std::cout << "渲染器初始化成功" << std::endl;
    return true;
}

bool VideoRenderer::CompileShaders() {
    // 顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "顶点着色器编译失败: " << infoLog << std::endl;
        return false;
    }

    // 片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "片段着色器编译失败: " << infoLog << std::endl;
        return false;
    }

    // 着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "着色器程序链接失败: " << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    CheckGLError("CompileShaders");
    return true;
}

void VideoRenderer::SetupQuad() {
    float vertices[] = {
        // 位置          // 纹理坐标
        -1.0f,  1.0f,    0.0f, 0.0f,  // 左上
        -1.0f, -1.0f,    0.0f, 1.0f,  // 左下
         1.0f, -1.0f,    1.0f, 1.0f,  // 右下
         1.0f,  1.0f,    1.0f, 0.0f   // 右上
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
#if 1
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(vertices), vertices);
    VBO = dynamic_cast<OpenGLBuffer *>(RHIVBO)->GetHandle();
    std::cout << "CreateVBO OK" << std::endl;
#else
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#endif
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 纹理坐标属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    CheckGLError("SetupQuad");
}

bool VideoRenderer::CreateTexture(int width, int height) {
    if (textureID == 0) {
        glGenTextures(1, &textureID);
    }

    glBindTexture(GL_TEXTURE_2D, textureID);

    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 分配纹理内存
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    CheckGLError("CreateTexture");
    return glGetError() == GL_NO_ERROR;
}

void VideoRenderer::RenderFrame(const uint8_t* data, int width, int height) {
    if (!initialized || !data || width <= 0 || height <= 0) return;

    // 清除屏幕
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 创建或更新纹理
    if (textureID == 0) {
        if (!CreateTexture(width, height)) {
            return;
        }
    }

    // 更新纹理数据
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    // 渲染四边形
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // 交换缓冲区
    glfwSwapBuffers(window);

    CheckGLError("RenderFrame");
}

void VideoRenderer::Cleanup() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
    if (shaderProgram) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
#if 1
    delete RHIVBO;
#else
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
#endif

    if (EBO) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    delete pRHI;
    glfwTerminate();
    initialized = false;
}

bool VideoRenderer::ShouldClose() const {
    return window ? glfwWindowShouldClose(window) : true;
}

void VideoRenderer::PollEvents() {
    if (window) {
        glfwPollEvents();
    }
}

void VideoRenderer::SetWindowTitle(const char* title) {
    if (window) {
        glfwSetWindowTitle(window, title);
    }
}