#ifdef OS_IS_WINDOWS
#include "DirectSoundDeviceManager.h"
#include <iostream>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
// 枚举回调函数
BOOL CALLBACK DSEnumCallback(LPGUID lpGuid,
    LPCSTR lpcstrDescription,
    LPCSTR lpcstrModule,
    LPVOID lpContext) {
    std::cout << "找到音频设备:" << std::endl;
    std::cout << "  描述: " << lpcstrDescription << std::endl;
    std::cout << "  模块: " << lpcstrModule << std::endl;

    if (lpGuid) {
        std::cout << "  有 GUID" << std::endl;
    }
    else {
        std::cout << "  默认设备" << std::endl;
    }
    std::cout << "------------------------" << std::endl;

    return TRUE; // 继续枚举
}

DirectSoundDeviceManager::DirectSoundDeviceManager()
{
    // DirectSoundEnumerate 不需要 COM 初始化
    HRESULT hr = DirectSoundEnumerate(DSEnumCallback, nullptr);
    if (FAILED(hr)) {
        std::cout << "枚举 DirectSound 设备失败: " << hr << std::endl;
    }
}
#endif