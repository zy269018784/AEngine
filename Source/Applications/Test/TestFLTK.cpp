// fltk_gl46_triangle.cpp
// 编译: g++ -o gl46 main.cpp -lfltk_gl -lfltk -lGL -ldl
// GLAD 头文件 (需要先生成)
#include <glad/glad.h>

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>



#include <cstdio>
#include <vector>

// OpenGL 4.6 顶点着色器源码
static const char* vertexShaderSource = R"(#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vColor;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    vColor = aColor;
}
)";

// OpenGL 4.6 片段着色器源码
static const char* fragmentShaderSource = R"(#version 460 core
in vec3 vColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}
)";

class GL46Window : public Fl_Gl_Window {
private:
    // OpenGL 资源
    GLuint shaderProgram;
    GLuint VAO, VBO;

    // 着色器编译辅助函数
    GLuint compileShader(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        // 检查编译错误
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            fprintf(stderr, "Shader compilation error (%s):\n%s\n",
                    type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);
            return 0;
        }
        return shader;
    }

    // 创建着色器程序
    bool createShaderProgram() {
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        if (vertexShader == 0 || fragmentShader == 0) {
            return false;
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // 检查链接错误
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            fprintf(stderr, "Shader linking error:\n%s\n", infoLog);
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return true;
    }

    // 设置顶点数据
    void setupGeometry() {
        // 顶点数据: 位置 (x,y) + 颜色 (r,g,b)
        struct Vertex {
            float x, y;
            float r, g, b;
        };

        std::vector<Vertex> vertices = {
            // 左下角顶点 - 红色
            {-0.6f, -0.5f, 1.0f, 0.0f, 0.0f},
            // 右下角顶点 - 绿色
            { 0.6f, -0.5f, 0.0f, 1.0f, 0.0f},
            // 顶部顶点 - 蓝色
            { 0.0f,  0.6f, 0.0f, 0.0f, 1.0f}
        };

        // 创建 VAO 和 VBO
        glCreateVertexArrays(1, &VAO);
        glCreateBuffers(1, &VBO);

        // 绑定 VAO (使用现代 DSA 方式需要先绑定)
        glBindVertexArray(VAO);

        // 填充 VBO 数据
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                     vertices.data(), GL_STATIC_DRAW);

        // 设置顶点属性
        // 位置属性 (location = 0)
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // 颜色属性 (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // 解绑
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

public:
    GL46Window(int x, int y, int w, int h, const char* title)
        : Fl_Gl_Window(x, y, w, h, title) {

        // 设置 OpenGL 模式
        mode(FL_RGB | FL_DOUBLE | FL_DEPTH);

        shaderProgram = 0;
        VAO = VBO = 0;
    }

    ~GL46Window() {
        if (shaderProgram) glDeleteProgram(shaderProgram);
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
    }

    // 打印 OpenGL 信息
    void printOpenGLInfo() {
        printf("========================================\n");
        printf("OpenGL Information:\n");
        printf("  Vendor:   %s\n", glGetString(GL_VENDOR));
        printf("  Renderer: %s\n", glGetString(GL_RENDERER));
        printf("  Version:  %s\n", glGetString(GL_VERSION));
        printf("  Shading:  %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

        // 获取支持的 OpenGL 版本号
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        printf("  Context:  %d.%d\n", major, minor);

        // 检查是否为 Core Profile
        GLint profile;
        glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        if (profile & GL_CONTEXT_CORE_PROFILE_BIT) {
            printf("  Profile:  Core Profile\n");
        }
        if (profile & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT) {
            printf("  Profile:  Compatibility Profile\n");
        }
        printf("========================================\n");
    }

    virtual void draw() override {
        // 检查是否需要初始化 OpenGL 上下文
        if (!valid()) {
            printf("Initializing OpenGL 4.6 context...\n");

            // 初始化 GLAD (必须在使用任何 OpenGL 函数之前)
            if (!gladLoadGL()) {
                fprintf(stderr, "Failed to initialize GLAD!\n");
                return;
            }

            // 打印 OpenGL 信息
            printOpenGLInfo();

            // 验证 OpenGL 版本是否满足 4.6
            GLint major, minor;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MINOR_VERSION, &minor);

            if (major < 4 || (major == 4 && minor < 6)) {
                fprintf(stderr, "Warning: OpenGL %d.%d detected, but 4.6 is required!\n",
                        major, minor);
            } else {
                printf("OpenGL 4.6 context successfully created!\n");
            }

            // 创建着色器程序
            if (!createShaderProgram()) {
                fprintf(stderr, "Failed to create shader program!\n");
                return;
            }

            // 设置几何体
            setupGeometry();

            // 设置清除颜色 (深灰色背景)
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

            // 启用深度测试 (虽然 2D 三角形不需要，但这是良好实践)
            glEnable(GL_DEPTH_TEST);

            printf("OpenGL initialization complete!\n");
        }

        // 清除颜色和深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);

        // 绘制三角形
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // 结束绘制
        glUseProgram(0);
    }

    virtual int handle(int event) override {
        switch (event) {
            case FL_FOCUS:
            case FL_UNFOCUS:
                return 1;  // 接收键盘事件
            case FL_KEYBOARD:
                switch (Fl::event_key()) {
                    case FL_Escape:
                        return 0;  // 让 FLTK 处理退出
                    case 'r':
                    case 'R':
                        // 重新初始化 OpenGL (重新加载着色器)
                        valid(0);
                        redraw();
                        return 1;
                }
                break;
        }
        return Fl_Gl_Window::handle(event);
    }
};

int TestFLTK(int argc, char** argv) {
    // 创建窗口
    GL46Window window(100, 100, 800, 600, "FLTK + OpenGL 4.6 - Colorful Triangle");
    window.end();
    window.show(argc, argv);

    printf("Program started. Press 'R' to reload OpenGL, ESC to exit.\n");

    return Fl::run();
}