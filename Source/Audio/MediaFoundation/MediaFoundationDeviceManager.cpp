#ifdef OS_IS_WINDOWS
#include "MediaFoundationDeviceManager.h"
#include <iostream>

#include <mfapi.h>
#include <mfidl.h>
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
MediaFoundationDeviceManager::MediaFoundationDeviceManager()
{
    // 初始化 COM
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        std::cout << "com failed" << std::endl;
    }

    // 初始化 Media Foundation
    hr = MFStartup(MF_VERSION, MFSTARTUP_LITE);
    if (FAILED(hr))
    {
        std::cout << "MFStartup failed" << std::endl;
    }

    IMFAttributes* pAttributes = nullptr;
    IMFActivate** ppDevices = nullptr;
    UINT32 count = 0;

    // 创建属性存储
    hr = MFCreateAttributes(&pAttributes, 1);
    if (FAILED(hr))
    {
        std::cout << "MFCreateAttributes failed" << std::endl;
    }

    // 设置设备类别
    hr = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_GUID);
    if (FAILED(hr)) {
        pAttributes->Release();
        return;
    }

    // 枚举设备
    hr = MFEnumDeviceSources(pAttributes, &ppDevices, &count);
    if (FAILED(hr)) {
        std::cout << "MFEnumDeviceSources failed" << std::endl;
        return;
    }
    std::cout << "count " << count << std::endl;

    pAttributes->Release();
    LPWSTR name = nullptr;
    UINT32 length = 0;
    if (SUCCEEDED(hr)) {
        for (UINT32 i = 0; i < count; i++) {
            HRESULT hr = ppDevices[i]->GetAllocatedString(
                MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
                &name,
                &length
            );

            std::wcout << "name " << name << std::endl;
           // devices.push_back(ppDevices[i]);
        }
        CoTaskMemFree(ppDevices);
    }

}
#endif