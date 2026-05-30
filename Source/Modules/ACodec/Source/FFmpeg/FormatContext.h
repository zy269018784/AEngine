#ifndef ENGINE_FORMATCONTEXT_H
#define ENGINE_FORMATCONTEXT_H

#include "Core/ACodecExport.h"

extern  "C"
{
     #include <libavformat/avformat.h>
}

class ACODECEXPORT FormatContext {
public:
     FormatContext();
     ~FormatContext();
     int OpenInput(const char *url, const AVInputFormat *fmt, AVDictionary **options);
     int FindStreamInfo(AVDictionary **options);
     int GetStreamCount() const;
     AVStream *GetStream(int index) const;
     enum AVMediaType GetGetStreamCodecType(int index) const;
     enum AVCodecID   GetGetStreamCodecID(int index) const;

     AVFormatContext *GetHandle();
private:
     AVFormatContext *Handle;
};


#endif //ENGINE_FORMATCONTEXT_H