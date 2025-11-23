1. API
    SDL_AudioDevicePaused
    SDL_AudioStreamDevicePaused
    SDL_BindAudioStream
    SDL_BindAudioStreams
    SDL_ClearAudioStream
    SDL_CloseAudioDevice
    SDL_ConvertAudioSamples
    SDL_CreateAudioStream
    SDL_DestroyAudioStream
    SDL_FlushAudioStream
    SDL_GetAudioDeviceChannelMap
    SDL_GetAudioDeviceFormat
    SDL_GetAudioDeviceGain
    SDL_GetAudioDeviceName
    SDL_GetAudioDriver
    SDL_GetAudioFormatName
    SDL_GetAudioPlaybackDevices
    SDL_GetAudioRecordingDevices
    SDL_GetAudioStreamAvailable
    SDL_GetAudioStreamData
    SDL_GetAudioStreamDevice
    SDL_GetAudioStreamFormat
    SDL_GetAudioStreamFrequencyRatio
    SDL_GetAudioStreamGain
    SDL_GetAudioStreamInputChannelMap
    SDL_GetAudioStreamOutputChannelMap
    SDL_GetAudioStreamProperties
    SDL_GetAudioStreamQueued
    SDL_GetCurrentAudioDriver
    SDL_GetNumAudioDrivers
    SDL_GetSilenceValueForFormat
    SDL_IsAudioDevicePhysical
    SDL_IsAudioDevicePlayback
    SDL_LoadWAV
    SDL_LoadWAV_IO
    SDL_LockAudioStream
    SDL_MixAudio
    SDL_OpenAudioDevice
    SDL_OpenAudioDeviceStream
    SDL_PauseAudioDevice
    SDL_PauseAudioStreamDevice
    SDL_PutAudioStreamData
    SDL_PutAudioStreamDataNoCopy
    SDL_PutAudioStreamPlanarData
    SDL_ResumeAudioDevice
    SDL_ResumeAudioStreamDevice
    SDL_SetAudioDeviceGain
    SDL_SetAudioIterationCallbacks
    SDL_SetAudioPostmixCallback
    SDL_SetAudioStreamFormat
    SDL_SetAudioStreamFrequencyRatio
    SDL_SetAudioStreamGain
    SDL_SetAudioStreamGetCallback
    SDL_SetAudioStreamInputChannelMap
    SDL_SetAudioStreamOutputChannelMap
    SDL_SetAudioStreamPutCallback               Set a callback that runs when data is added to an audio stream.
    SDL_UnbindAudioStream
    SDL_UnbindAudioStreams
    SDL_UnlockAudioStream

2. usage
    SDL_AudioDeviceID devid;   
    SDL_AudioSpec spec;
    SDL_AudioSpec src_spec;
    SDL_AudioSpec dst_spec;
    SDL_AudioStream *stream;
    DL_AudioStreamCallback callback;
 
    SDL_OpenAudioDevice(devid, &spec);

    stream = SDL_CreateAudioStream(&src_spec, &dst_spec);

    SDL_SetAudioStreamGetCallback(stream, callback, NULL);    

    SDL_BindAudioStream(devid, stream);
    
    /*
        pause
    */
    SDL_PauseAudioDevice(devid);
    /*
        resume to play
    */
    SDL_ResumeAudioDevice(devid);

    SDL_PauseAudioStreamDevice(stream);  

    SDL_ResumeAudioStreamDevice(stream);

    SDL_UnbindAudioStream(stream);

    SDL_DestroyAudioStream(stream);

    SDL_CloseAudioDevice(devid);

