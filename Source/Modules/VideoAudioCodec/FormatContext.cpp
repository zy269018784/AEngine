//
// Created by zhouyue on 2026/4/6.
//

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

AVFormatContext FormatContext::GetHandle() {
    return Handle;
}