#pragma once
#ifdef PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
    #include <alsa/control.h>
#endif
class ALSAElementID
{
public:
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_id_t *Handle;
#endif
};


