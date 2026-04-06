//
// Created by zhouyue on 2026/4/6.
//

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