
ffmpeg -i 1.mp3 -ch_layout stereo  -acodec pcm_s32le -f s32le output.pcm
ffplay  -ch_layout stereo -f s32le -ar 48000  output.pcm
ffplay  -ac 2 -f s32le -ar 48000  output.pcm



ffmpeg -i 2.mp4 -ch_layout stereo  -acodec pcm_s16le -f s16le output_s16le.pcm
ffplay  -ch_layout stereo -f s16le -ar 48000  output_s16le.pcm
ffplay  -ac 2 -f s16le -ar 48000  output_s16le.pcm