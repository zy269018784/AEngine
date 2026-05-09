#if  PROJECT_USE_FFMEPG
#include "Frame.h"

Frame::Frame()
{
    this->Alloc();
}

Frame::~Frame()
{
    this->Free();
}

AVFrame *Frame::GetHandle()
{
    return Handle;
}

void Frame::Alloc()
{
    Handle = av_frame_alloc();
}

void Frame::Free()
{
    av_frame_free(&Handle);
}

void Frame::SetWidth(int Width)
{
    Handle->width = Width;
}

void Frame::SetHeight(int Height)
{
    Handle->height = Height;
}

void Frame::SetPixelFormat(AVPixelFormat PixelFormat)
{
    Handle->format = PixelFormat;
}

void Frame::MakeWritable()
{
    av_frame_make_writable(Handle);
}

int Frame::GetBuffer(int Align)
{
    return av_frame_get_buffer(Handle, Align);
}

void Frame::SetYUV(int Row, int Col, std::uint8_t Y, std::uint8_t U, std::uint8_t V)
{
    Handle->data[0][Row * Handle->linesize[0] + Col] = Y;
    Handle->data[1][Row * Handle->linesize[1] + Col] = U;
    Handle->data[2][Row * Handle->linesize[2] + Col] = V;
}

void Frame::SetRGB(int Row, int Col, std::uint8_t R, std::uint8_t G, std::uint8_t B)
{
    Handle->data[0][Row * Handle->linesize[0] + Col] = R;
    Handle->data[1][Row * Handle->linesize[1] + Col] = G;
    Handle->data[2][Row * Handle->linesize[2] + Col] = B;
}
#endif