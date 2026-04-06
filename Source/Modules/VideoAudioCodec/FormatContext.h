//
// Created by zhouyue on 2026/4/6.
//

#ifndef ENGINE_FORMATCONTEXT_H
#define ENGINE_FORMATCONTEXT_H
#include <libavformat/avformat.h>


class FormatContext {
public:
     FormatContext();
     ~FormatContext();
     int OpenInput(const char *url, const AVInputFormat *fmt, AVDictionary **options);
     AVFormatContext GetHandle();
private
     AVFormatContext *Handle;
};


#endif //ENGINE_FORMATCONTEXT_H