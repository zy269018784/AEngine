// VideoDecoder.h
#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

struct VideoFrame {
    std::unique_ptr<uint8_t[]> data;  // Ê¹ÓÃÖÇÄÜÖ¸Õë¹ÜÀíÄÚ´æ
    int width = 0;
    int height = 0;
    int64_t pts = 0;
    double timestamp = 0.0;

    VideoFrame() = default;
    VideoFrame(int w, int h) : width(w), height(h) {
        data = std::make_unique<uint8_t[]>(w * h * 3); // RGB24
    }
};

class VideoDecoder {
private:
    std::thread decodeThread;
    std::queue<std::unique_ptr<VideoFrame>> frameQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;

    AVFormatContext* formatCtx = nullptr;
    AVCodecContext* codecCtx = nullptr;
    SwsContext* swsCtx = nullptr;
    int videoStreamIndex = -1;

    bool running = false;
    const int maxQueueSize = 1000000;

public:
    ~VideoDecoder() { Cleanup(); }

    bool Open(const char* filename);
    void Start();
    void Stop();
    std::unique_ptr<VideoFrame> GetFrame();
    int GetWidth() const { return codecCtx ? codecCtx->width : 0; }
    int GetHeight() const { return codecCtx ? codecCtx->height : 0; }
    bool IsRunning() const { return running; }

private:
    void DecodeLoop();
    void Cleanup();
    std::unique_ptr<VideoFrame> ConvertToRGB(AVFrame* frame);
};