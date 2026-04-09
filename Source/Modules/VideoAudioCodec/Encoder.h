//
// Created by zhouyue on 2026/4/10.
//

#ifndef ENGINE_ENCODER_H
#define ENGINE_ENCODER_H
#include <cstdint>

#include "Frame.h"
#include "CodecContext.h"

class Encoder
{
public:
    Encoder(const char *CodecName = nullptr);
    ~Encoder();

    int CodecOpen2(AVDictionary **options);
    void SetPointer(uint8_t **data, int *Linesize, int ArraySize);

    void SetYUV(int Row, int Col, std::uint8_t Y, std::uint8_t U, std::uint8_t V);
    void SetRGB(int Row, int Col, std::uint8_t R, std::uint8_t G, std::uint8_t B);

    void SetPixelFormat(AVPixelFormat PixelFormat);
    void SetTimeBase(int TimeBase);
    void SetFrameRate(int Rate);
    void SetBitRate(int BitRate);
    void SetWidth(int Width);
    void SetHeight(int Height);
    void SetMaxBFrames(int Count);
    void SetGopSize(int Size);
public:
    CodecContext *CodecContext = nullptr;
    Frame *Frame = nullptr;
    const AVCodec *Codec;
private:
};


#endif //ENGINE_ENCODER_H