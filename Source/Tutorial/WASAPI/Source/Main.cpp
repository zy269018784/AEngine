#include <windows.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>
#include <functiondiscoverykeys.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "mmdevapi.lib")

// Device information structure
struct AudioDeviceInfo {
    std::wstring DeviceID;
    std::wstring FriendlyName;
    std::wstring DeviceDescription;
    std::wstring State;
    std::wstring Role;
    std::wstring Format;
    bool bIsDefaultRender = false;
    bool bIsDefaultCapture = false;
    bool bIsDefaultCommunications = false;
};

// Get device state string
std::wstring GetDeviceStateString(DWORD state) {
    switch (state) {
        case DEVICE_STATE_ACTIVE:   return L"Active";
        case DEVICE_STATE_DISABLED: return L"Disabled";
        case DEVICE_STATE_NOTPRESENT: return L"Not Present";
        case DEVICE_STATE_UNPLUGGED: return L"Unplugged";
        default: return L"Unknown";
    }
}

// Get device format info
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

// Get device friendly name
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

// Get device description
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

// Enumerate all audio devices
std::vector<AudioDeviceInfo> EnumerateAudioDevices() {
    std::vector<AudioDeviceInfo> devices;

    HRESULT hr;
    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDeviceCollection* pDevices = nullptr;

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,
                          __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr)) {
        std::cerr << "Failed to create device enumerator: 0x" << std::hex << hr << std::endl;
        return devices;
    }

    hr = pEnumerator->EnumAudioEndpoints(eAll, DEVICE_STATEMASK_ALL, &pDevices);
    if (FAILED(hr)) {
        std::cerr << "Failed to enumerate audio devices: 0x" << std::hex << hr << std::endl;
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

    std::cout << "Found " << count << " audio devices" << std::endl;
    std::cout << "========================================" << std::endl;

    for (UINT i = 0; i < count; i++) {
        IMMDevice* pDevice = nullptr;
        hr = pDevices->Item(i, &pDevice);
        if (FAILED(hr)) continue;

        AudioDeviceInfo info;

        // Get device ID
        LPWSTR pwszID = nullptr;
        hr = pDevice->GetId(&pwszID);
        if (SUCCEEDED(hr)) {
            info.DeviceID = pwszID;
            CoTaskMemFree(pwszID);
        }

        // Get device state
        DWORD state = 0;
        hr = pDevice->GetState(&state);
        if (SUCCEEDED(hr)) {
            info.State = GetDeviceStateString(state);
        }

        // Get friendly name and description
        info.FriendlyName = GetDeviceFriendlyName(pDevice);
        info.DeviceDescription = GetDeviceDescription(pDevice);

        // Get data flow using IMMEndpoint
        IMMEndpoint* pEndpoint = nullptr;
        hr = pDevice->QueryInterface(__uuidof(IMMEndpoint), (void**)&pEndpoint);
        if (SUCCEEDED(hr)) {
            EDataFlow dataFlow;
            hr = pEndpoint->GetDataFlow(&dataFlow);
            pEndpoint->Release();

            if (SUCCEEDED(hr)) {
                switch (dataFlow) {
                    case eRender:
                        info.Role = L"Render (Output)";
                        break;
                    case eCapture:
                        info.Role = L"Capture (Input)";
                        break;
                    case eAll:
                        info.Role = L"Bidirectional";
                        break;
                    default:
                        info.Role = L"Unknown";
                        break;
                }
            }
        }

        // Check if default render device
        IMMDevice* pDefaultRender = nullptr;
        hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDefaultRender);
        if (SUCCEEDED(hr)) {
            LPWSTR pwszDefaultID = nullptr;
            if (SUCCEEDED(pDefaultRender->GetId(&pwszDefaultID))) {
                if (info.DeviceID == pwszDefaultID) {
                    info.bIsDefaultRender = true;
                }
                CoTaskMemFree(pwszDefaultID);
            }
            pDefaultRender->Release();
        }

        // Check if default capture device
        IMMDevice* pDefaultCapture = nullptr;
        hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDefaultCapture);
        if (SUCCEEDED(hr)) {
            LPWSTR pwszDefaultID = nullptr;
            if (SUCCEEDED(pDefaultCapture->GetId(&pwszDefaultID))) {
                if (info.DeviceID == pwszDefaultID) {
                    info.bIsDefaultCapture = true;
                }
                CoTaskMemFree(pwszDefaultID);
            }
            pDefaultCapture->Release();
        }

        // Get device format
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

// Print device info
void PrintDeviceInfo(const AudioDeviceInfo& info, int index) {
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
    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::cerr << "COM initialization failed: 0x" << std::hex << hr << std::endl;
        return 1;
    }

    std::cout << "Enumerating all audio devices..." << std::endl;
    std::cout << "========================================" << std::endl;

    auto devices = EnumerateAudioDevices();

    if (devices.empty()) {
        std::cout << "No audio devices found" << std::endl;
    } else {
        std::cout << std::endl << "Device List:" << std::endl;
        std::cout << "========================================" << std::endl;

        // Separate render and capture devices
        std::vector<AudioDeviceInfo> renderDevices;
        std::vector<AudioDeviceInfo> captureDevices;

        for (const auto& dev : devices) {
            if (dev.Role.find(L"Render") != std::wstring::npos) {
                renderDevices.push_back(dev);
            } else if (dev.Role.find(L"Capture") != std::wstring::npos) {
                captureDevices.push_back(dev);
            }
        }

        // Print render devices
        std::cout << std::endl << "=== Render Devices (Output) ===" << std::endl;
        int index = 0;
        for (const auto& dev : renderDevices) {
            PrintDeviceInfo(dev, ++index);
        }

        // Print capture devices
        std::cout << std::endl << "=== Capture Devices (Input) ===" << std::endl;
        index = 0;
        for (const auto& dev : captureDevices) {
            PrintDeviceInfo(dev, ++index);
        }
    }

    // Cleanup COM
    CoUninitialize();

    std::cout << std::endl << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}