
ffmpeg -i 1.mp3 -ch_layout stereo  -acodec pcm_s32le -f s32le output.pcm
ffplay  -ch_layout stereo -f s32le -ar 48000  output.pcm
ffplay  -ac 2 -f s32le -ar 48000  output.pcm

