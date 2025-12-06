// main.cpp
#include "VideoDecoder.h"
#include "VideoRenderer.h"
#include <chrono>
#include <thread>
#include <iostream>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "用法: " << argv[0] << " <视频文件>" << std::endl;
        return -1;
    }

    // 初始化渲染器
    VideoRenderer renderer;
    if (!renderer.Initialize()) {
        std::cerr << "渲染器初始化失败" << std::endl;
        return -1;
    }

    // 初始化解码器
    VideoDecoder decoder;
    if (!decoder.Open(argv[1])) {
        std::cerr << "无法打开视频文件: " << argv[1] << std::endl;
        return -1;
    }

    // 开始解码
    decoder.Start();

    // 主渲染循环
    auto lastTime = std::chrono::steady_clock::now();
    double frameTime = 1.0 / 25.0; // 假设30fps

    while (!renderer.ShouldClose()) {
        auto currentTime = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(currentTime - lastTime).count();

        if (elapsed >= frameTime) {
            // 获取一帧
            auto frame = decoder.GetFrame();
            if (frame) {
                // 渲染帧
                renderer.RenderFrame(frame->data.get(),
                    decoder.GetWidth(),
                    decoder.GetHeight());
                lastTime = currentTime;
            }
        }

        renderer.PollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // 清理
    decoder.Stop();
    renderer.Cleanup();

    return 0;
}