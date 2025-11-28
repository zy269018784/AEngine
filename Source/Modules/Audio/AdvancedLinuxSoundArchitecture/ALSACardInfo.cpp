#include "ALSACardInfo.h"

ALSACardInfo::ALSACardInfo()
{
#ifdef PROJECT_USE_ALSA
    snd_ctl_card_info_malloc(&Handle);
#endif
}

ALSACardInfo::~ALSACardInfo()
{
#ifdef PROJECT_USE_ALSA
    snd_ctl_card_info_free(Handle);
#endif
}


const char * ALSACardInfo::Name()
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_card_info_get_name(Handle);
#else
    return  nullptr;
#endif
}

const char * ALSACardInfo::LongName () {
#ifdef PROJECT_USE_ALSA
    return snd_ctl_card_info_get_longname(Handle);
#else
    return  nullptr;
#endif
}









