//
// Created by 26901 on 2026/4/18.
//

#ifndef ENGINE_MUXER_H
#define ENGINE_MUXER_H

#include "FormatContext.h"
extern  "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavutil/opt.h>
    #include <libavutil/imgutils.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}
class Muxer
{
public:
    void AddStream();
public:
    const AVOutputFormat *fmt;
    FormatContext *FC;
};



#endif //ENGINE_MUXER_H
