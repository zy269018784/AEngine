#pragma once
#if  PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
    #include <alsa/control.h>
#endif
class ALSACardInfo
{
public:
    ALSACardInfo();
    ~ALSACardInfo();
public:
    const char * Name();
    const char * LongName ();
#if  PROJECT_USE_ALSA
    snd_ctl_card_info_t *Handle;
#endif
};

