#include <windows.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>
#include <functiondiscoverykeys.h>
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <fcntl.h>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "mmdevapi.lib")

struct AudioDeviceInfo {
    std::wstring DeviceID;
    std::wstring FriendlyName;
    std::wstring DeviceDescription;
    std::wstring State;
    std::wstring Role;
    std::wstring Format;
    bool bIsDefaultRender = false;
    bool bIsDefaultCapture = false;
};

std::wstring GetDeviceStateString(DWORD state) {
    switch (state) {
        case DEVICE_STATE_ACTIVE:   return L"Active";
        case DEVICE_STATE_DISABLED: return L"Disabled";
        case DEVICE_STATE_NOTPRESENT: return L"Not Present";
        case DEVICE_STATE_UNPLUGGED: return L"Unplugged";
        default: return L"Unknown";
    }
}

std::wstring GetDeviceFormatString(IAudioClient* pAudioClient) {
    if (!pAudioClient) return L"Unable to get format";

    WAVEFORMATEX* pwf = nullptr;
    HRESULT hr = pAudioClient->GetMixFormat(&pwf);
    if (FAILED(hr) || !pwf) return L"Unable to get format";

    std::wstring result = std::to_wstring(pwf->nSamplesPerSec) + L" Hz, ";

    switch (pwf->nChannels) {
        case 1: result += L"Mono"; break;
        case 2: result += L"Stereo"; break;
        case 6: result += L"5.1 Surround"; break;
        case 8: result += L"7.1 Surround"; break;
        default: result += std::to_wstring(pwf->nChannels) + L" channels";
    }

    result += L", ";
    result += std::to_wstring(pwf->wBitsPerSample) + L" bit";

    CoTaskMemFree(pwf);
    return result;
}

std::wstring GetDeviceFriendlyName(IMMDevice* pDevice) {
    if (!pDevice) return L"";

    IPropertyStore* pProps = nullptr;
    HRESULT hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
    if (FAILED(hr)) return L"Unable to get name";

    PROPVARIANT varName;
    PropVariantInit(&varName);

    hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
    std::wstring name = L"";
    if (SUCCEEDED(hr) && varName.vt == VT_LPWSTR) {
        name = varName.pwszVal;
    }

    PropVariantClear(&varName);
    pProps->Release();

    return name;
}

std::wstring GetDeviceDescription(IMMDevice* pDevice) {
    if (!pDevice) return L"";

    IPropertyStore* pProps = nullptr;
    HRESULT hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
    if (FAILED(hr)) return L"Unable to get description";

    PROPVARIANT varDesc;
    PropVariantInit(&varDesc);

    hr = pProps->GetValue(PKEY_Device_DeviceDesc, &varDesc);
    std::wstring desc = L"";
    if (SUCCEEDED(hr) && varDesc.vt == VT_LPWSTR) {
        desc = varDesc.pwszVal;
    }

    PropVariantClear(&varDesc);
    pProps->Release();

    return desc;
}

std::vector<AudioDeviceInfo> EnumerateAudioDevices() {
    std::vector<AudioDeviceInfo> devices;

    HRESULT hr;
    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDeviceCollection* pDevices = nullptr;

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,
                          __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr)) {
        return devices;
    }

    hr = pEnumerator->EnumAudioEndpoints(eAll, DEVICE_STATEMASK_ALL, &pDevices);
    if (FAILED(hr)) {
        pEnumerator->Release();
        return devices;
    }

    UINT count = 0;
    hr = pDevices->GetCount(&count);
    if (FAILED(hr)) {
        pDevices->Release();
        pEnumerator->Release();
        return devices;
    }

    // 获取默认设备
    std::wstring defaultRenderID, defaultCaptureID;

    IMMDevice* pDefaultRender = nullptr;
    if (SUCCEEDED(pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDefaultRender))) {
        LPWSTR pwszID = nullptr;
        pDefaultRender->GetId(&pwszID);
        defaultRenderID = pwszID;
        CoTaskMemFree(pwszID);
        pDefaultRender->Release();
    }

    IMMDevice* pDefaultCapture = nullptr;
    if (SUCCEEDED(pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDefaultCapture))) {
        LPWSTR pwszID = nullptr;
        pDefaultCapture->GetId(&pwszID);
        defaultCaptureID = pwszID;
        CoTaskMemFree(pwszID);
        pDefaultCapture->Release();
    }

    for (UINT i = 0; i < count; i++) {
        IMMDevice* pDevice = nullptr;
        hr = pDevices->Item(i, &pDevice);
        if (FAILED(hr)) continue;

        AudioDeviceInfo info;

        LPWSTR pwszID = nullptr;
        hr = pDevice->GetId(&pwszID);
        if (SUCCEEDED(hr)) {
            info.DeviceID = pwszID;
            CoTaskMemFree(pwszID);
        }

        DWORD state = 0;
        pDevice->GetState(&state);
        info.State = GetDeviceStateString(state);

        info.FriendlyName = GetDeviceFriendlyName(pDevice);
        info.DeviceDescription = GetDeviceDescription(pDevice);

        IMMEndpoint* pEndpoint = nullptr;
        hr = pDevice->QueryInterface(__uuidof(IMMEndpoint), (void**)&pEndpoint);
        if (SUCCEEDED(hr)) {
            EDataFlow dataFlow;
            hr = pEndpoint->GetDataFlow(&dataFlow);
            pEndpoint->Release();

            if (SUCCEEDED(hr)) {
                switch (dataFlow) {
                    case eRender: info.Role = L"Render (Output)"; break;
                    case eCapture: info.Role = L"Capture (Input)"; break;
                    case eAll: info.Role = L"Bidirectional"; break;
                    default: info.Role = L"Unknown"; break;
                }
            }
        }

        if (!info.DeviceID.empty() && info.DeviceID == defaultRenderID) {
            info.bIsDefaultRender = true;
        }
        if (!info.DeviceID.empty() && info.DeviceID == defaultCaptureID) {
            info.bIsDefaultCapture = true;
        }

        IAudioClient* pAudioClient = nullptr;
        hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
        if (SUCCEEDED(hr)) {
            info.Format = GetDeviceFormatString(pAudioClient);
            pAudioClient->Release();
        }

        devices.push_back(info);
        pDevice->Release();
    }

    pDevices->Release();
    pEnumerator->Release();

    return devices;
}

void PrintDeviceInfo(const AudioDeviceInfo& info, int index) {
    // ✅ 使用 std::wcout 输出，配合正确的控制台编码
    std::wcout << L"[" << index << L"]" << std::endl;
    std::wcout << L"  Name: " << info.FriendlyName << std::endl;
    std::wcout << L"  Description: " << info.DeviceDescription << std::endl;
    std::wcout << L"  Device ID: " << info.DeviceID << std::endl;
    std::wcout << L"  State: " << info.State << std::endl;
    std::wcout << L"  Type: " << info.Role << std::endl;
    std::wcout << L"  Format: " << info.Format << std::endl;

    if (info.bIsDefaultRender) {
        std::wcout << L"  * Default Output Device" << std::endl;
    }
    if (info.bIsDefaultCapture) {
        std::wcout << L"  * Default Input Device" << std::endl;
    }
    std::wcout << L"  ----------------------------------------" << std::endl;
}

int main() {
    // ✅ 方法1：设置控制台为 UTF-8
    SetConsoleOutputCP(CP_UTF8);

    // ✅ 方法2：设置宽字符输出模式（推荐）
    _setmode(_fileno(stdout), _O_U16TEXT);

    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::wcerr << L"COM initialization failed" << std::endl;
        return 1;
    }

    std::wcout << L"Enumerating all audio devices..." << std::endl;
    std::wcout << L"========================================" << std::endl;

    auto devices = EnumerateAudioDevices();

    if (devices.empty()) {
        std::wcout << L"No audio devices found" << std::endl;
    } else {
        std::wcout << std::endl << L"Device List:" << std::endl;
        std::wcout << L"========================================" << std::endl;

        int index = 0;
        for (const auto& dev : devices) {
            PrintDeviceInfo(dev, ++index);
        }
    }

    CoUninitialize();

    std::wcout << std::endl << L"Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}