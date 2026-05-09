#pragma once
#if  PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
    #include <alsa/control.h>
#endif
class ALSAElementInfo
{
public:
    ALSAElementInfo();
    ~ALSAElementInfo();
public:
    const char *Name();
public:
#if  PROJECT_USE_ALSA
    snd_ctl_elem_info_t *Handle;
#endif
};

