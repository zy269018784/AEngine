
#include <mmdeviceapi.h>
/*
                 Windows 音频 API 对比                    │
├─────────────────────────────────────────────────────────────┤
│ 传统 API         │ 现代 API              │ 游戏 API         │
├─────────────────────────────────────────────────────────────┤
│ • Waveform API   │ • WASAPI              │ • XAudio2        │
│ • DirectSound    │ • Media Foundation    │ • DirectSound    │
│ • MCI            │ • Core Audio          │
*/
bool test1()
{
    IMMDeviceEnumerator* deviceEnumerator = nullptr;
    IMMDevice* audioDevice = nullptr;


    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator),
        nullptr,
        CLSCTX_ALL,
        __uuidof(IMMDeviceEnumerator),
        (void**)&deviceEnumerator
    );

    if (FAILED(hr)) return false;

    // 获取默认音频渲染设备（扬声器）
    hr = deviceEnumerator->GetDefaultAudioEndpoint(
        eRender,        // 渲染设备（输出）
        eConsole,       // 控制台应用
        &audioDevice
    );
}