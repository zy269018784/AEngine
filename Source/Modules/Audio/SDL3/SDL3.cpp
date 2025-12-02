#ifdef PROJECT_USE_SDL3
#include "SDL3/SDL.h"

#include <SDL3/SDL_main.h>
#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846
// Audio callback function
void audio_callback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount) {
    // Generate a simple sine wave
    static double phase = 0.0;
    double phase_increment = 2.0 * M_PI * 440.0 / 44100.0; // 440 Hz tone

    int samples_needed = additional_amount / sizeof(Sint16);
    Sint16* samples = (Sint16*)SDL_malloc(additional_amount);

    if (samples) {
        for (int i = 0; i < samples_needed; i++) {
            samples[i] = (Sint16)(sin(phase) * 32000); // 16-bit signed audio
            phase += phase_increment;
            if (phase > 2.0 * M_PI) {
                phase -= 2.0 * M_PI;
            }
        }

        SDL_PutAudioStreamData(stream, samples, additional_amount);
        SDL_free(samples);
    }
}

int testSDL3()
{
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_AUDIO)) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    // Create audio stream
    SDL_AudioSpec spec = {
        .format = SDL_AUDIO_S16,
        .channels = 2,
        .freq = 44100
    };
    // Create audio device
    SDL_AudioDeviceID device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!device) {
        printf("Failed to open audio device: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_AudioSpec src_spec = {
        .format = SDL_AUDIO_S16,
        .channels = 2,
        .freq = 44100
    };;
    SDL_AudioSpec dst_spec= {
        .format = SDL_AUDIO_S16,
        .channels = 2,
        .freq = 44100
    };;

    SDL_AudioStream* stream = SDL_CreateAudioStream(&src_spec, &dst_spec);
    if (!stream) {
        printf("Failed to create audio stream: %s\n", SDL_GetError());
        SDL_CloseAudioDevice(device);
        SDL_Quit();
        return 1;
    }

    // Bind stream to device
    if (!SDL_BindAudioStream(device, stream))
    {
        printf("Failed to bind audio stream: %s\n", SDL_GetError());
        SDL_DestroyAudioStream(stream);
        SDL_CloseAudioDevice(device);
        SDL_Quit();
        return 1;
    }

    SDL_AudioStreamCallback callback = audio_callback;
    SDL_SetAudioStreamGetCallback(stream, callback, NULL);

    printf("Playing audio... Press Enter to stop.\n");

    // Start audio playback
    SDL_ResumeAudioStreamDevice(stream);

    // Wait for user input
    getchar();

    // Clean up
    SDL_DestroyAudioStream(stream);
    SDL_CloseAudioDevice(device);
    SDL_Quit();

    return 0;
}
#endif