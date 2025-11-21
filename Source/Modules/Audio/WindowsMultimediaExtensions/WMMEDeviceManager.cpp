#ifdef OS_IS_WINDOWS
#include "WMMEDeviceManager.h"
#include <iostream>

WMMEDeviceManager::WMMEDeviceManager()
{

    UINT deviceCount = waveOutGetNumDevs();
    for (UINT i = 0; i < deviceCount; i++) {
        WAVEOUTCAPS caps;
        MMRESULT result = waveOutGetDevCaps(i, &caps, sizeof(caps));

        if (result == MMSYSERR_NOERROR) {
            std::wcout << caps.szPname << std::endl;
        }
    }

}
#endif