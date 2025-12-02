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
#else
    return 0;
#endif
}

const char *ALSAControl::Name()
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_name(Handle);
#else
    return nullptr;
#endif
}
#ifdef PROJECT_USE_ALSA
int ALSAControl::ElementList(snd_ctl_elem_list_t *List)
{

    return snd_ctl_elem_list(Handle, List);
#
}

int ALSAControl::ElementInfo(snd_ctl_elem_info_t *Info)
{
    return snd_ctl_elem_info(Handle, Info);
}

int ALSAControl::CardInfo(snd_ctl_card_info_t *Info)
{
    return snd_ctl_card_info(Handle, Info);
}
#endif