#include "ALSADevice.h"
#ifdef PROJECT_USE_ALSA
    #include <alsa/asoundlib.h>
#endif
ALSADevice::ALSADevice(int CardIndex)
    : Handle(CardIndex)
{
    snd_card_get_name(Handle, &Name);
    snd_card_get_longname(Handle, &LongName);
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