#pragma once
#ifdef OS_IS_WINDOWS
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <vector>

class CoreAudioDeviceManager
{
public:
	CoreAudioDeviceManager();
private:
	IMMDeviceEnumerator* DeviceEnumerator = nullptr;
	IMMDeviceCollection* DeviceCollection = nullptr;
	std::vector<IMMDevice *> Devices;
	std::vector<IPropertyStore*> Props;
};
#endif