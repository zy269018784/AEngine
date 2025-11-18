#include "AudioFile.h"
#include <filesystem>
#include <iostream>
#include <stdio.h>

#include <fdk-aac/aacenc_lib.h>
#include <opus.h>

#include <ogg/ogg.h>

#include <vorbis/vorbisenc.h>

#include <twolame.h>

#include "MP3FileFormat.h"
#include "FlacFileFormat.h"
#include "OggFileFormat.h"
#include "PCM.h"

bool HasExtension(const std::filesystem::path& filePath, const std::string& targetExt)
{
    // 统一转为小写比较（可选）
    std::string ext = filePath.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == targetExt;
}

AudioFile::AudioFile()
{
   
}

AudioFile::~AudioFile()
{
}

int AudioFile::EncodePCM(char* InputFilename, char* OutputFilename)
{
    if (HasExtension(OutputFilename, ".mp2"))
    {
        return EncodeToMP2(InputFilename, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".mp3"))
    {
        return EncodeToMP3(InputFilename, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".ogg"))
    {
        return EncodeToOGG(InputFilename,  OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".flac"))
    {
        return EncodeToFLAC(InputFilename, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".acc"))
    {
        return EncodeToAAC(InputFilename, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".ac3"))
    {
        return EncodeToAC3(InputFilename, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".lc3"))
    {
        return EncodeToLC3(InputFilename,  OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".opus"))
    {
        return EncodeToOPUS(InputFilename, OutputFilename);
    } 
    else
    {
        printf("unsupportted format\n");
    }
    return 0;
}

int AudioFile::EncodePCM(PCM* pcm, char* OutputFilename)
{
    if (HasExtension(OutputFilename, ".mp2"))
    {
       
    }
    else if (HasExtension(OutputFilename, ".mp3"))
    {
        MP3FileFormat mp3ff;
        return mp3ff.LameEncoder(pcm, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".ogg"))
    {
        OggFileFormat oggff;
        return oggff.VorbisEncoder(pcm, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".flac"))
    {
        FlacFileFormat flacff;
        return flacff.FlacEncoder(pcm, OutputFilename);
    }
    else if (HasExtension(OutputFilename, ".acc"))
    {
        
    }
    else if (HasExtension(OutputFilename, ".ac3"))
    {
        
    }
    else if (HasExtension(OutputFilename, ".lc3"))
    {
       
    }
    else if (HasExtension(OutputFilename, ".opus"))
    {
        
    }
    else
    {
        printf("unsupportted format\n");
        return -1;
    }
    return 0;
}

int AudioFile::EncodeToMP2(char* InputFilename, char* OutputFilename)
{

    return 0;
}

int AudioFile::EncodeToMP3(char* InputFilename, char* OutputFilename)
{
    PCM pcm;
    pcm.SetChannels(2);
    pcm.SetBytesPerSample(2);
    pcm.SetSampleRate(44100);
    pcm.ReadFromRawFile(InputFilename);

    MP3FileFormat mp3ff;
    return mp3ff.LameEncoder(&pcm, OutputFilename);
}

#define PCM_BUFFER_SIZE 8192 * 2  // 16-bit 立体声的PCM帧大小
#define AAC_BUFFER_SIZE 512 * 2   // AAC最大

int AudioFile::EncodeToAAC(char* InputFilename, char* OutputFilename)
{
    // 初始化编码器
    HANDLE_AACENCODER hEncoder;
    if (aacEncOpen(&hEncoder, 0, 2) != AACENC_OK) {
        fprintf(stderr, "无法打开AAC编码器\n");
        return -1;
    }

    // 设置编码参数（关键！）
    if (aacEncoder_SetParam(hEncoder, AACENC_AOT, AOT_AAC_LC) != AACENC_OK ||  // AAC-LC标准
        aacEncoder_SetParam(hEncoder, AACENC_SAMPLERATE, 44100) != AACENC_OK ||  // 44.1kHz
        aacEncoder_SetParam(hEncoder, AACENC_CHANNELMODE, MODE_2) != AACENC_OK ||  // 立体声
        aacEncoder_SetParam(hEncoder, AACENC_BITRATE, 128000) != AACENC_OK ||  // 128kbps
        aacEncoder_SetParam(hEncoder, AACENC_TRANSMUX, TT_MP4_ADIF) != AACENC_OK) {  // ADTS头格式
        fprintf(stderr, "参数设置失败\n");
        aacEncClose(&hEncoder);
        return -1;
    }

    // 初始化编码器配置
    if (aacEncEncode(hEncoder, NULL, NULL, NULL, NULL) != AACENC_OK) {
        fprintf(stderr, "编码器初始化失败\n");
        aacEncClose(&hEncoder);
        return -1;
    }

    // 获取编码器信息（可选）
    AACENC_InfoStruct info = { 0 };
    if (aacEncInfo(hEncoder, &info) != AACENC_OK) {
        fprintf(stderr, "无法获取编码器信息\n");
        aacEncClose(&hEncoder);
        return -1;
    }
    printf("AAC帧大小: %d bytes\n", info.frameLength);

    // 打开输入(PCM)和输出(AAC)文件
    FILE* pcm_file = fopen(InputFilename, "rb");  // 假设是16-bit 立体声 PCM
    FILE* aac_file = fopen(OutputFilename, "wb"); // ADTS格式的AAC文件
    if (!pcm_file || !aac_file) {
        perror("文件打开失败");
        aacEncClose(&hEncoder);
        return -1;
    }

    // 缓冲区配置
    short pcm_buffer[PCM_BUFFER_SIZE];
    unsigned char aac_buffer[AAC_BUFFER_SIZE];
    AACENC_BufDesc in_buf = { 0 }, out_buf = { 0 };
    AACENC_InArgs in_args = { 0 };
    AACENC_OutArgs out_args = { 0 };

    // 输入/输出缓冲区设置
    void* in_ptr[] = { pcm_buffer };
    int in_size[] = { sizeof(pcm_buffer) };
    int in_identifier[] = { IN_AUDIO_DATA };
    in_buf.bufs = in_ptr;
    in_buf.bufferIdentifiers = in_identifier;
    in_buf.bufSizes = in_size;
    in_buf.numBufs = 1;

    void* out_ptr[] = { aac_buffer };
    int out_size[] = { sizeof(aac_buffer) };
    int out_identifier[] = { OUT_BITSTREAM_DATA };
    out_buf.bufs = out_ptr;
    out_buf.bufferIdentifiers = out_identifier;
    out_buf.bufSizes = out_size;
    out_buf.numBufs = 1;

    // 编码循环
    while (1) {
        // 读取PCM数据（16-bit 小端 立体声）
        size_t read = fread(pcm_buffer, sizeof(short), PCM_BUFFER_SIZE, pcm_file);
        if (read == 0) break;  // 文件结束

        in_args.numInSamples = read;
        AACENC_ERROR Error = aacEncEncode(hEncoder, &in_buf, &out_buf, &in_args, &out_args);

        printf("error %d\n", Error);
        if (AACENC_OK != Error) {
            fprintf(stderr, "编码失败\n");
            break;
        }

        // 写入AAC数据到文件
        if (out_args.numOutBytes > 0) {
            fwrite(aac_buffer, 1, out_args.numOutBytes, aac_file);
        }
    }

    // 刷新编码器（处理剩余数据）
    in_args.numInSamples = 0;
    while (aacEncEncode(hEncoder, NULL, &out_buf, &in_args, &out_args) == AACENC_OK) {
        if (out_args.numOutBytes > 0) {
            fwrite(aac_buffer, 1, out_args.numOutBytes, aac_file);
        }
        else {
            break;
        }
    }

    // 清理资源
    fclose(pcm_file);
    fclose(aac_file);
    aacEncClose(&hEncoder);
    printf("AAC文件生成成功: output.aac\n");
    return 0;
}

int AudioFile::EncodeToAC3(char* InputFilename, char* OutputFilename)
{
    return 0;
}


#define SAMPLE_RATE 48000    // Opus标准采样率（支持8k/12k/16k/24k/48k）
#define CHANNELS 2           // 立体声
#define FRAME_SIZE 960       // 每帧样本数（48kHz下=20ms）
#define MAX_PACKET_SIZE 4000 // Opus包最大大小

int AudioFile::EncodeToOPUS(char* InputFilename, char* OutputFilename)
{
    // 打开PCM输入文件和Opus输出文件
    FILE* pcm_file = fopen(InputFilename, "rb");
    FILE* opus_file = fopen(OutputFilename, "wb");
    if (!pcm_file || !opus_file) {
        perror("文件打开失败");
        return -1;
    }

    // 初始化Opus编码器
    int err;
    OpusEncoder* encoder = opus_encoder_create(
        SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_AUDIO, &err
    );
    if (err != OPUS_OK) {
        fprintf(stderr, "Opus编码器创建失败: %s\n", opus_strerror(err));
        fclose(pcm_file);
        fclose(opus_file);
        return -1;
    }

    // 设置编码器参数（可选）
    opus_encoder_ctl(encoder, OPUS_SET_BITRATE(64000));  // 64kbps
    opus_encoder_ctl(encoder, OPUS_SET_COMPLEXITY(8));   // 最高质量

    // 缓冲区
    short pcm_buffer[FRAME_SIZE * CHANNELS];  // 16-bit PCM
    unsigned char opus_packet[MAX_PACKET_SIZE];

    // 编码循环
    while (1) {
        // 读取PCM数据（16-bit小端，立体声交错）
        size_t read = fread(pcm_buffer, sizeof(short), FRAME_SIZE * CHANNELS, pcm_file);
        if (read == 0) break;  // 文件结束

        // 编码为Opus
        int packet_size = opus_encode(
            encoder,
            pcm_buffer,
            FRAME_SIZE,       // 每声道样本数（非总样本数！）
            opus_packet,
            MAX_PACKET_SIZE
        );
        if (packet_size < 0) {
            fprintf(stderr, "编码失败: %s\n", opus_strerror(packet_size));
            break;
        }

        // 写入Opus包到文件
        fwrite(opus_packet, 1, packet_size, opus_file);
    }

    // 清理资源
    opus_encoder_destroy(encoder);
    fclose(pcm_file);
    fclose(opus_file);
    printf("Opus文件生成成功: %s\n", OutputFilename);
    return 0;
    return 0;
}

int AudioFile::EncodeToFLAC(char* InputFilename, char* OutputFilename)
{
    printf("hello flac\n");
    PCM pcm;
    pcm.SetChannels(2);
    pcm.SetBytesPerSample(2);
    pcm.SetSampleRate(44100);
    pcm.ReadFromRawFile32(InputFilename);

    FlacFileFormat flacff;
    return flacff.FlacEncoder(&pcm, OutputFilename);
}

int AudioFile::EncodeToLC3(char* InputFilename, char* OutputFilename)
{
    return 0;
}

int AudioFile::EncodeToOGG(char* InputFilename, char* OutputFilename)
{
    PCM pcm;
    pcm.SetChannels(2);
    pcm.SetBytesPerSample(2);
    pcm.SetSampleRate(44100);
    pcm.ReadFromRawFile32(InputFilename);

    OggFileFormat oggff;
    return oggff.VorbisEncoder(&pcm, OutputFilename);

    //FILE* pcm_file = fopen(InputFilename, "rb"); // 16-bit 小端 PCM
    //FILE* ogg_file = fopen(OutputFilename, "wb");

    //// 1. 初始化 Ogg 流
    //ogg_stream_state os;
    //ogg_stream_init(&os, rand());

    //// 2. 初始化 Vorbis 编码器
    //vorbis_info vi;
    //vorbis_info_init(&vi);
    //vorbis_encode_init_vbr(&vi, 2, 44100, 0.4); // 立体声, 44.1kHz, 质量 0.4 (0.1~1.0)

    //vorbis_comment vc;
    //vorbis_comment_init(&vc);
    //vorbis_comment_add_tag(&vc, "ENCODER", "MyOggEncoder");

    //// 3. 生成 Vorbis 头部包
    //vorbis_dsp_state vd;
    //vorbis_block vb;
    //vorbis_analysis_init(&vd, &vi);
    //vorbis_block_init(&vd, &vb);

    //ogg_packet header, header_comm, header_code;
    //vorbis_analysis_headerout(&vd, &vc, &header, &header_comm, &header_code);
    //ogg_stream_packetin(&os, &header);
    //ogg_stream_packetin(&os, &header_comm);
    //ogg_stream_packetin(&os, &header_code);

    //// 4. 写入 Ogg 头部
    //ogg_page og;
    //while (ogg_stream_flush(&os, &og)) {
    //    fwrite(og.header, 1, og.header_len, ogg_file);
    //    fwrite(og.body, 1, og.body_len, ogg_file);
    //}

    //// 5. 编码 PCM 数据
    //const int BUFFER_SIZE = 4096;
    //int16_t pcm_buffer[BUFFER_SIZE * 2]; // 立体声 16-bit PCM
    //float** vorbis_buffer;
    //int eos = 0;

    //while (!eos) {
    //    size_t read = fread(pcm_buffer, sizeof(int16_t), BUFFER_SIZE * 2, pcm_file);
    //    if (read == 0) {
    //        vorbis_analysis_wrote(&vd, 0); // 结束流
    //        break;
    //    }

    //    // 将 16-bit PCM 转换为浮点 (-1.0 ~ 1.0)
    //    vorbis_buffer = vorbis_analysis_buffer(&vd, read / 2);
    //    for (size_t i = 0; i < read; i += 2) {
    //        vorbis_buffer[0][i / 2] = pcm_buffer[i] / 32768.0f;   // 左声道
    //        vorbis_buffer[1][i / 2] = pcm_buffer[i + 1] / 32768.0f; // 右声道
    //    }
    //    vorbis_analysis_wrote(&vd, read / 2);

    //    // 编码并写入 Ogg 页面
    //    while (vorbis_analysis_blockout(&vd, &vb) == 1) {
    //        vorbis_analysis(&vb, NULL);
    //        vorbis_bitrate_addblock(&vb);

    //        ogg_packet op;
    //        while (vorbis_bitrate_flushpacket(&vd, &op)) {
    //            ogg_stream_packetin(&os, &op);
    //            while (ogg_stream_pageout(&os, &og)) {
    //                fwrite(og.header, 1, og.header_len, ogg_file);
    //                fwrite(og.body, 1, og.body_len, ogg_file);
    //            }
    //        }
    //    }
    //}

    //// 6. 清理资源
    //ogg_stream_clear(&os);
    //vorbis_block_clear(&vb);
    //vorbis_dsp_clear(&vd);
    //vorbis_comment_clear(&vc);
    //vorbis_info_clear(&vi);
    //fclose(pcm_file);
    //fclose(ogg_file);
    return 0;
}
