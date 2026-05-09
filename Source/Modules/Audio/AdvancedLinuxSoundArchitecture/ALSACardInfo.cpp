#include "ALSACardInfo.h"

ALSACardInfo::ALSACardInfo()
{
#if  PROJECT_USE_ALSA
    snd_ctl_card_info_malloc(&Handle);
#endif
}

ALSACardInfo::~ALSACardInfo()
{
#if  PROJECT_USE_ALSA
    snd_ctl_card_info_free(Handle);
#endif
}


const char * ALSACardInfo::Name()
{
#if  PROJECT_USE_ALSA
    return snd_ctl_card_info_get_name(Handle);
#else
    return  nullptr;
#endif
}

const char * ALSACardInfo::LongName () {
#if  PROJECT_USE_ALSA
    return snd_ctl_card_info_get_longname(Handle);
#else
    return  nullptr;
#endif
}









