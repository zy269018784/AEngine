#include "ALSAControl.h"
#include <iostream>
#ifdef PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
#endif

ALSAControl::ALSAControl()
{
#ifdef PROJECT_USE_ALSA

#endif
}

ALSAControl::~ALSAControl()
{
#ifdef PROJECT_USE_ALSA
    Close();
#endif
}

int ALSAControl::Open(const char *Name, int Mode)
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_open(&Handle, Name, Mode);
#else
    return  0;
#endif
}

int ALSAControl::Close()
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_close(Handle);
#endif
}

const char *ALSAControl::Name()
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_name(Handle);
#endif
}

int ALSAControl::ElementList(snd_ctl_elem_list_t *List)
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_elem_list(Handle, List);
#endif
}

int ALSAControl::ElementInfo(snd_ctl_elem_info_t *Info)
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_elem_info(Handle, Info);
#endif
}

int ALSAControl::CardInfo(snd_ctl_card_info_t *Info)
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_card_info(Handle, Info);
#endif
}