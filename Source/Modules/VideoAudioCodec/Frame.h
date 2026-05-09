//
// Created by zhouyue on 2026/4/6.
//

#ifndef ENGINE_AVFRAME_H
#define ENGINE_AVFRAME_H
#include <cstdint>
#ifdef PROJECT_USE_FFMEPG
extern  "C"
{
#include <libavcodec/avcodec.h>
}

class Frame
{
public:
    Frame();
    ~Frame();
    AVFrame *GetHandle();
    void Alloc();
    void Free();
    void SetWidth(int Width);
    void SetHeight(int Height);
    void SetPixelFormat(AVPixelFormat PixelFormat);
    void MakeWritable();
    int GetBuffer(int Align);
    void SetYUV(int Row, int Col, std::uint8_t Y, std::uint8_t U, std::uint8_t V);
    void SetRGB(int Row, int Col, std::uint8_t R, std::uint8_t G, std::uint8_t B);
private:
    AVFrame *Handle;
};
#endif

#endif //ENGINE_AVFRAME_H