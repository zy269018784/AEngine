#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include "Audio/CoreAudio/CoreAudioDeviceManager.h"
#include "Audio/DirectSound/DirectSoundDeviceManager.h"
#include "Audio/XAudio2/XAudio2DeviceManager.h"
#include "Audio/MediaFoundation/MediaFoundationDeviceManager.h"
#include "Audio/DirectMusic/DirectMusicDeviceManager.h"
#include "Audio/ASIO/ASIODeviceManager.h"
#include "Audio/WindowsMultimediaExtensions/WMMEDeviceManager.h"
#include "Audio/AdvancedLinuxSoundArchitecture/ALSADeviceManager.h"

int MusicPlayer(int argc, char** argv);
int main(int argc, char **argv)
{
	return MusicPlayer(argc,argv);

	//std::cout << "hello " << std::endl;
//	CoreAudioDeviceManager adm;
	//	return 0;

	//std::cout << "hello " << argc  << " " << argv[1] << std::endl;
	auto Music = new sf::Music("ikutaerika.mp3");
	std::cout << "play start" << std::endl;
	Music->play();
	std::cout << "play end" << std::endl;
	while (1);
	return 0;
}
