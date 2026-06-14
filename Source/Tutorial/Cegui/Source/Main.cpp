
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>



#include <GLFW/glfw3.h>
#include <iostream>
extern "C" {
extern int gladLoadGL(void);
}
int main() {
    // 1. 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "glfwInit failed" << std::endl;
        return -1;
    }

    // 设置 OpenGL 版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    GLFWwindow* window = glfwCreateWindow(800, 600, "CEGUI + GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "gladLoadGL failed AA" << std::endl;
        return -1;
    }
    // 重要：GLFW 需要交换一次缓冲区才能完全初始化 OpenGL
    glfwSwapBuffers(window);
    glfwPollEvents();

    std::cout << "debug 1" << std::endl;

    // 2. 初始化 CEGUI（用 try-catch 捕获异常）
    try {
        std::cout << "Initializing CEGUI..." << std::endl;
        CEGUI::OpenGL3Renderer::bootstrapSystem();
        std::cout << "debug 2" << std::endl;

        CEGUI::System& sys = CEGUI::System::getSingleton();
        std::cout << "debug 3" << std::endl;

        CEGUI::GUIContext& ctx = sys.getDefaultGUIContext();
        std::cout << "debug 4" << std::endl;

    } catch (const CEGUI::Exception& e) {
        std::cerr << "CEGUI Exception: " << e.what() << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Standard Exception: " << e.what() << std::endl;
        return -1;
    }

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}