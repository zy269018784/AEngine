#include <vector>
#if  PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
    #include <alsa/control.h>
#endif
class ALSAControl
{
public:
    ALSAControl();
    ~ALSAControl();
    int Open(const char *Name, int Mode);
    int Close();
    const char *Name();
#if  PROJECT_USE_ALSA
    int ElementList(snd_ctl_elem_list_t *list);
    int ElementInfo (snd_ctl_elem_info_t *info);
    int CardInfo(snd_ctl_card_info_t *info);
#endif
private:
#if  PROJECT_USE_ALSA
    snd_ctl_t *Handle;
#endif
};
