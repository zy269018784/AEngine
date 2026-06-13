#include "GHttpClient1.h"

GHttpClient1::GHttpClient1(GAbstractHttpClient *Parent)
    : GAbstractHttpClient(Parent)
{
    Handle = curl_easy_init();
}

GHttpClient1::~GHttpClient1()
{
    curl_easy_cleanup(Handle);
}

CURL *GHttpClient1::GetHandle() const
{
    return Handle;
}