#ifdef OS_IS_LINUX
#include "ALSADeviceManager.h"
#include <iostream>
#ifdef PROJECT_USE_ALSA
#include <alsa/asoundlib.h>
#endif
void list_alsa_devices() {
#ifdef PROJECT_USE_ALSA
	char** hints;
	int err;

	err = snd_device_name_hint(-1, "pcm", (void***)&hints);
	if (err != 0) {
		fprintf(stderr, "Error: Cannot get device hints: %s\n", snd_strerror(err));
		return;
	}

	char** n = hints;
	int count = 0;

	while (*n != NULL) {
		char* name = snd_device_name_get_hint(*n, "NAME");
		char* desc = snd_device_name_get_hint(*n, "DESC");
		char* ioid = snd_device_name_get_hint(*n, "IOID");

		if (name && strcmp(name, "null") != 0) {
			printf("Device #%d:\n", ++count);
			printf("  Name: %s\n", name);

			if (desc) {
				// Clean up description
				char* clean_desc = strdup(desc);
				char* p = clean_desc;
				while (*p) {
					if (*p == '\n') *p = ' ';
					p++;
				}
				printf("  Desc: %s\n", clean_desc);
				free(clean_desc);
			}

			if (ioid) {
				printf("  I/O: %s\n", ioid);
			}
			printf("\n");
		}

		if (name) free(name);
		if (desc) free(desc);
		if (ioid) free(ioid);
		n++;
	}

	snd_device_name_free_hint((void**)hints);

	if (count == 0) {
		printf("No ALSA devices found!\n");
	}
#endif
}

ALSADeviceManager::ALSADeviceManager()
{
#ifdef PROJECT_USE_ALSA
	list_alsa_devices();
	std::cout << "ALSA" << std::endl;
#endif
}
#endif
