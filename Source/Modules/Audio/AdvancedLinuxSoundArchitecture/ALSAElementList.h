#pragma once
#ifdef PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
    #include <alsa/control.h>
#endif
class ALSAElementList
{
public:
    ALSAElementList();
    ~ALSAElementList();
public:
    /*
     * Wrapper
     */
    int AllocSpace(unsigned int Entries);
    void FreeSpace();
    unsigned int GetCount();
    const char *GetName(unsigned int Index);
    void SetOffset(unsigned int Offset);
public:
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_list_t *Handle;
#endif
};

