#include "ALSAElementInfo.h"

ALSAElementInfo::ALSAElementInfo() {
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_info_malloc(&Handle);
#endif
}

ALSAElementInfo::~ALSAElementInfo() {
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_info_free(Handle);
#endif
}

const char *ALSAElementInfo::Name() {
#ifdef PROJECT_USE_ALSA
    return snd_ctl_elem_info_get_name(Handle);
#else
    return  nullptr;
#endif
}