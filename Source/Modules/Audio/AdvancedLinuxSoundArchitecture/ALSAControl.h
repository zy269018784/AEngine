#include <vector>
#ifdef PROJECT_USE_ALSA
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
    int ElementList(snd_ctl_elem_list_t *list);
    int ElementInfo (snd_ctl_elem_info_t *info);
    int CardInfo(snd_ctl_card_info_t *info);
private:
#ifdef PROJECT_USE_ALSA
    snd_ctl_t *Handle;
#endif
};
