#if  PROJECT_USE_FFMEPG
#include "Encoder.h"

Encoder::Encoder(const char *CodecName)
{
    Codec = avcodec_find_encoder_by_name(CodecName);

    CodecContext = new ::CodecContext(Codec);

    Frame = new ::Frame();
}

Encoder::~Encoder()
{
    delete CodecContext;

    delete Frame;
}

int Encoder::CodecOpen2(AVDictionary **options)
{
    return CodecContext->CodecOpen2(Codec, NULL);
}

void Encoder::SetYUV(int Row, int Col, std::uint8_t Y, std::uint8_t U, std::uint8_t V)
{

}

void Encoder::SetRGB(int Row, int Col, std::uint8_t R, std::uint8_t G, std::uint8_t B)
{

}
void Encoder::SetPixelFormat(AVPixelFormat PixelFormat)
{
    CodecContext->SetPixelFormat(PixelFormat);
    Frame->SetPixelFormat(PixelFormat);
}


void Encoder::SetTimeBase(int TimeBase)
{
    CodecContext->SetTimeBase(TimeBase);
}

void Encoder::SetFrameRate(int FrameRate)
{
    CodecContext->SetFrameRate(FrameRate);
}

void Encoder::SetBitRate(int BitRate)
{
    CodecContext->SetBitRate(BitRate);
}

void Encoder::SetWidth(int Width)
{
    CodecContext->SetWidth(Width);
    Frame->SetWidth(Width);
}

void Encoder::SetHeight(int Height)
{
    CodecContext->SetHeight(Height);
    Frame->SetHeight(Height);
}

void Encoder::SetMaxBFrames(int Count)
{
    CodecContext->SetMaxBFrames(Count);
}

void Encoder::SetGopSize(int Size)
{
    CodecContext->SetGopSize(Size);
}

#endif