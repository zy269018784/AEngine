#include "ALSADevice.h"
#ifdef PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
#endif
ALSADevice::ALSADevice(int CardIndex)
    : Handle(CardIndex)
{
#ifdef PROJECT_USE_ALSA
    snd_card_get_name(Handle, &Name);
    snd_card_get_longname(Handle, &LongName);
#endif
}

ALSADevice::~ALSADevice() {

}

int ALSADevice::GetHandle() const {
    return Handle;
}

char *ALSADevice::GetName() const {
    return Name;
}

char *ALSADevice::GetLongName() const {
    return LongName;
}