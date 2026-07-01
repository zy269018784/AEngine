#include "FlacFileFormat.h"
#include "PCM.h"
#include <iostream>
#define FLAC__NO_DLL
#include <FLAC/stream_encoder.h>

static FLAC__StreamEncoderWriteStatus write_callback(
    const FLAC__StreamEncoder* encoder,
    const FLAC__byte buffer[],
    size_t bytes,
    unsigned samples,
    unsigned current_frame,
    void* client_data
) {
    FILE* f = (FILE*)client_data;
    if (fwrite(buffer, 1, bytes, f) != bytes)
        return FLAC__STREAM_ENCODER_WRITE_STATUS_FATAL_ERROR;
    return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
}

int FlacFileFormat::FlacEncoder(class PCM* InPCM, std::string OutputFile)
{
    unsigned sample_rate = InPCM->GetSampleRate();
    /*
        通道数量
    */
    unsigned channels = InPCM->GetChannels();
    /*
        每个PCM样本多少位 = 每个样本字节数 * 8
    */
    //InPCM->SetBytesPerSample(4);
    unsigned BitsPerSample = InPCM->GetBytesPerSample() * 8;
    //BitsPerSample = 32;
    auto total_pcm_samples = InPCM->GetSampleCount();

    auto total_samples = total_pcm_samples / channels;
    std::cout << "total_samples " << total_samples << std::endl;

    // 打开输入 PCM 文件和输出 FLAC 文件
    //FILE* pcm = fopen(InputFilename, "rb");
    FILE* flac = fopen(OutputFile.c_str(), "wb");
    if (!flac)
    {
        return -1;
    }
    // 初始化 FLAC 编码器
    FLAC__StreamEncoder* encoder = FLAC__stream_encoder_new();
    FLAC__stream_encoder_set_channels(encoder, channels);
    FLAC__stream_encoder_set_bits_per_sample(encoder, BitsPerSample);
    FLAC__stream_encoder_set_sample_rate(encoder, sample_rate);
    FLAC__stream_encoder_set_total_samples_estimate(encoder, total_samples);

    // 设置回调函数
    FLAC__stream_encoder_init_stream(encoder, write_callback, NULL, NULL, NULL, flac);

    /*
        样本数量
    */
    int LeftSampleCount = InPCM->GetSampleCount();
    /*
        通道数量
    */
    int Channels = InPCM->GetChannels();
    auto PCMBuffer = InPCM->GetPCMBuffer32();
    int PCMBufferSampleOffset = 0;
    /*
        每次循环处理8192个样本
    */
    int CurrentSampleCount = 8192;
    size_t NumWriteBytes = 0;

    while (LeftSampleCount > 0)
    {
        CurrentSampleCount = 8192;
        if (LeftSampleCount < 8192)
            CurrentSampleCount = LeftSampleCount;


        FLAC__stream_encoder_process_interleaved(encoder, PCMBuffer.data() + PCMBufferSampleOffset, CurrentSampleCount / Channels);

        PCMBufferSampleOffset += CurrentSampleCount;

        LeftSampleCount -= CurrentSampleCount;
    }
    // 清理 FLAC 编码器
    FLAC__stream_encoder_finish(encoder);
    // 释放 FLAC 编码器
    FLAC__stream_encoder_delete(encoder);
    //fclose(pcm);
    fclose(flac);
	return 0;
}