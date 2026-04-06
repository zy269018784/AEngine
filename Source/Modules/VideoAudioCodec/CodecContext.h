#ifndef ENGINE_AVCODECCONTEXT_H
#define ENGINE_AVCODECCONTEXT_H

extern  "C"
{
#include <libavcodec/avcodec.h>
}
class CodecContext
{
public:
    CodecContext(const AVCodec *codec = nullptr);
    ~CodecContext();
    void Alloc(const AVCodec *codec);
    void Free();
    void SetTimeBase(int TimeBase);
    void SetFrameRate(int Rate);
    void SetBitRate(int BitRate);
    void SetWidth(int Width);
    void SetHeight(int Height);
    void SetMaxBFrames(int Count);
    void SetGopSize(int Size);
    void SetPixelFormat(AVPixelFormat PixelFormat);
    int CodecOpen2(const AVCodec *codec, AVDictionary **options);
    AVCodecContext *GetHandle();
    int SendFrame(const AVFrame *Frame);
    int ReceivePacket(AVPacket *Pkt);
private:
    AVCodecContext *Handle;
};


#endif //ENGINE_AVCODECCONTEXT_H