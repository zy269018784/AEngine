#pragma once
#include <GHttp/GAbstractHttpClient.h>
#include <curl/curl.h>
#include <GCore/GExport.h>

class GEXPORT GHttpClient1 : public GAbstractHttpClient
{
public:
    GHttpClient1(GAbstractHttpClient *Parent = nullptr);
    virtual ~GHttpClient1();
    CURL *GetHandle() const;
private:
    CURL *Handle = nullptr;
};


