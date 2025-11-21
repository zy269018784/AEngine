#ifdef OS_IS_WINDOWS
#include "ASIODeviceManager.h"
#include <iostream>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

ASIODeviceManager::ASIODeviceManager()
{

}
#endif