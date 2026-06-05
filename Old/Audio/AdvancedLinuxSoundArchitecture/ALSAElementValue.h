#pragma once
#if  PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
    #include <alsa/control.h>
#endif

class ALSAElementValue
{
public:
#if  PROJECT_USE_ALSA
    snd_ctl_elem_value_t *Handle;
#endif
};

