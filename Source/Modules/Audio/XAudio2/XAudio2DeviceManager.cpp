#ifdef OS_IS_WINDOWS
#include "XAudio2DeviceManager.h"
#include <iostream>
#pragma comment(lib, "xaudio2.lib")
XAudio2DeviceManager::XAudio2DeviceManager()
{
    HRESULT hr; 
    IXAudio2* pXAudio2 = nullptr;
    UINT32 deviceCount = 0;
    // 初始化 XAudio2
    hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(hr)) {   
        std::cerr << "Failed to create XAudio2: 0x" << std::hex << hr << std::endl;
        return;
    }

}
#endif