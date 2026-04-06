//
// Created by zhouyue on 2026/4/6.
//

#ifndef ENGINE_AVFRAME_H
#define ENGINE_AVFRAME_H

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
private:
    AVFrame *Handle;
};


#endif //ENGINE_AVFRAME_H