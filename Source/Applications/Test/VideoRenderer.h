// VideoRenderer.h
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "Window/GLFWWindow.h"
class VideoRenderer {
private:
    GLFWwindow* window = nullptr;
    IWindow *Window = nullptr;
    GLuint textureID = 0;
    GLuint shaderProgram = 0;
    GLuint VAO = 0, VBO = 0, EBO = 0;

    int windowWidth = 1280;
    int windowHeight = 720;
    bool initialized = false;

public:
    ~VideoRenderer() { Cleanup(); }

    bool Initialize();
    void Cleanup();
    void RenderFrame(const uint8_t* data, int width, int height);
    bool ShouldClose() const;
    void PollEvents();
    void SetWindowTitle(const char* title);

private:
    bool CreateTexture(int width, int height);
    bool CompileShaders();
    void SetupQuad();
    void CheckGLError(const char* context);
};