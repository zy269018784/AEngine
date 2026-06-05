
#include "CodecContext.h"
#if  PROJECT_USE_FFMPEG
CodecContext::CodecContext(const AVCodec *codec)
{
    if (codec)
        this->Alloc(codec);
}

CodecContext::~CodecContext()
{
    this->Free();
}

void CodecContext::Alloc(const AVCodec *codec)
{
    Handle = avcodec_alloc_context3(codec);
}

void CodecContext::Free()
{
    avcodec_free_context(&Handle);
}

AVCodecContext *CodecContext::GetHandle()
{
    return Handle;
}

void CodecContext::SetTimeBase(int TimeBase)
{
    Handle->time_base.num = 1;
    Handle->time_base.den = TimeBase;
}

void CodecContext::SetFrameRate(int FrameRate)
{
    Handle->framerate.num = FrameRate;
    Handle->framerate.den = 1;
}

void CodecContext::SetBitRate(int BitRate)
{
    Handle->bit_rate = BitRate;
}

void CodecContext::SetWidth(int Width)
{
    Handle->width = Width;
}

void CodecContext::SetHeight(int Height)
{
    Handle->height = Height;
}

void CodecContext::SetMaxBFrames(int Count)
{
    Handle->max_b_frames = Count;
}

void CodecContext::SetGopSize(int Size)
{
    Handle->gop_size = Size;
}

void CodecContext::SetPixelFormat(AVPixelFormat PixelFormat)
{
    Handle->pix_fmt = PixelFormat;
}

int CodecContext::CodecOpen2(const AVCodec *codec, AVDictionary **options)
{
    return avcodec_open2(Handle, codec, options);
}

int CodecContext::SendFrame(const AVFrame *Frame)
{
    return avcodec_send_frame(Handle, Frame);
}

int CodecContext::ReceivePacket(AVPacket *Pkt)
{
    return avcodec_receive_packet(Handle, Pkt);
}
#endif