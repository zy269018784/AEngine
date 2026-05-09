#ifdef PROJECT_USE_FFMEPG
#include "FormatContext.h"

FormatContext::FormatContext()
{

}

FormatContext::~FormatContext()
{

}

int FormatContext::OpenInput(const char *url, const AVInputFormat *fmt, AVDictionary **options)
{
    return avformat_open_input(&Handle, url, fmt, options);
}

int FormatContext::FindStreamInfo(AVDictionary **options) {
    return avformat_find_stream_info(Handle, NULL);;
}

int FormatContext::GetStreamCount() const
{
    return Handle->nb_streams;
}

AVStream *FormatContext::GetStream(int index) const
{
    return Handle->streams[index];
}

enum AVMediaType FormatContext::GetGetStreamCodecType(int index) const
{
    return Handle->streams[index]->codecpar->codec_type;
}

enum AVCodecID   FormatContext::GetGetStreamCodecID(int index) const
{
    return Handle->streams[index]->codecpar->codec_id;
}

AVFormatContext *FormatContext::GetHandle() {
    return Handle;
}
#endif
