#ifdef OS_IS_LINUX
#include "ALSADeviceManager.h"
#include <iostream>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

ALSADeviceManager::ALSADeviceManager()
{
	std::cout << "ALSA" << std::endl;
}
#endif
