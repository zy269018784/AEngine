#include "ALSAElementList.h"


ALSAElementList::ALSAElementList() {
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_list_malloc(&Handle);
#endif
}

ALSAElementList::~ALSAElementList() {
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_list_free(Handle);
#endif
}

int ALSAElementList::AllocSpace(unsigned int Entries)
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_elem_list_alloc_space(Handle, Entries);
#else
    return  0;
#endif
}

void ALSAElementList::FreeSpace()
{
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_list_free_space(Handle);
#endif
}

unsigned int ALSAElementList::GetCount()
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_elem_list_get_count(Handle);
#else
    return  0;
#endif
}

const char *ALSAElementList::GetName(unsigned int Index)
{
#ifdef PROJECT_USE_ALSA
    return snd_ctl_elem_list_get_name(Handle, Index);
#else
    return  nullptr;
#endif
}

void ALSAElementList::SetOffset(unsigned int Offset)
{
#ifdef PROJECT_USE_ALSA
    snd_ctl_elem_list_set_offset(Handle, Offset);
#endif
}