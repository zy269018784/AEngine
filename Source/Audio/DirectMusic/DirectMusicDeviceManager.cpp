#ifdef OS_IS_WINDOWS
#include "DirectMusicDeviceManager.h"
#include <iostream>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


DirectMusicDeviceManager::DirectMusicDeviceManager()
{
 
}
#endif