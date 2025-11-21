#ifdef OS_IS_WINDOWS
#include "CoreAudioDeviceManager.h"
#include <iostream>
CoreAudioDeviceManager::CoreAudioDeviceManager()
{
    HRESULT Result;

    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(Result)) {
        std::cout << "COM 初始化失败: " << Result << std::endl;
        return;
    }

    // 初始化 COM 安全设置
    CoInitializeSecurity(
        nullptr,
        -1,
        nullptr,
        nullptr,
        RPC_C_AUTHN_LEVEL_NONE,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        EOAC_NONE,
        nullptr
    );


    Result = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&DeviceEnumerator);
    Result = DeviceEnumerator->EnumAudioEndpoints(eAll, DEVICE_STATE_ACTIVE, &DeviceCollection);
    /*
        获取设备数量
    */
    unsigned int  count;
    Result = DeviceCollection->GetCount(&count);

    Devices.resize(count);
    Props.resize(count);
    std::cout << "count " << count << std::endl;

    for (int i = 0; i < count; i++)
    {
        Result = DeviceCollection->Item(i, &Devices[i]);

        //Result = Devices[i]->GetId(&pwszID);

        Result = Devices[i]->OpenPropertyStore(STGM_READ, &Props[i]);

        PROPVARIANT varName;
        // Initialize container for property value.
        PropVariantInit(&varName);

        // Get the endpoint's friendly-name property.
        Result = Props[i]->GetValue(PKEY_Device_FriendlyName, &varName);

        std::wcout << "varName " << varName.pwszVal << std::endl;
    }

    for (int i = 0; i < count; i++)
    {
        Devices[i]->Release();
        Props[i]->Release();
    }

    DeviceEnumerator->Release();
    DeviceCollection->Release();
}
#endif