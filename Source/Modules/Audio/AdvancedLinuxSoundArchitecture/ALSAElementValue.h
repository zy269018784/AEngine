#pragma once
#ifdef PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
    #include <alsa/control.h>
#endif

class ALSAElementValue
{
public:
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_value_t *Handle;
#endif
};

