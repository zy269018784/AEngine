#include "OggFileFormat.h"
#include "PCM.h"
#include <ogg/ogg.h>
#include <vorbis/vorbisenc.h>
int OggFileFormat::VorbisEncoder(class PCM* InPCM, std::string OutputFile)
{
    FILE* ogg_file = fopen(OutputFile.data(), "wb");
    if (!ogg_file)
    {
        return -1;
    }
    /*
        样本数量
    */
    int LeftSampleCount = InPCM->GetSampleCount();
    /*
        通道数量
    */
    int Channels = InPCM->GetChannels();
    /*
        PCM Buffer
    */
    auto PCMBuffer = InPCM->GetPCMBuffer();
    int PCMBufferSampleOffset = 0;
    /*
        样本率
    */
    int SampleRate = InPCM->GetSampleRate();
    /*
        质量
    */
    int Quality = 0.4;

    // 1. 初始化 Ogg 流
    ogg_stream_state os;
    ogg_stream_init(&os, rand());

    // 2. 初始化 Vorbis 编码器
    vorbis_info vi;
    vorbis_info_init(&vi);
    vorbis_encode_init_vbr(&vi, Channels, SampleRate, 0.4); // 立体声, 44.1kHz, 质量 0.4 (0.1~1.0)

    vorbis_comment vc;
    vorbis_comment_init(&vc);
    vorbis_comment_add_tag(&vc, "ENCODER", "MyOggEncoder");

    // 3. 生成 Vorbis 头部包
    vorbis_dsp_state vd;
    vorbis_block vb;
    vorbis_analysis_init(&vd, &vi);
    vorbis_block_init(&vd, &vb);

    ogg_packet header, header_comm, header_code;
    vorbis_analysis_headerout(&vd, &vc, &header, &header_comm, &header_code);
    ogg_stream_packetin(&os, &header);
    ogg_stream_packetin(&os, &header_comm);
    ogg_stream_packetin(&os, &header_code);

    // 4. 写入 Ogg 头部
    ogg_page og;
    while (ogg_stream_flush(&os, &og)) {
        fwrite(og.header, 1, og.header_len, ogg_file);
        fwrite(og.body, 1, og.body_len, ogg_file);
    }


    // 5.
    /*
        每次循环处理8192个样本
    */
    int CurrentSampleCount = 8192;
    size_t NumWriteBytes = 0;
    float** vorbis_buffer;
    while (LeftSampleCount > 0)
    {
        CurrentSampleCount = 8192;
        if (LeftSampleCount < 8192)
            CurrentSampleCount = LeftSampleCount;

        // 将 16-bit PCM 转换为浮点 (-1.0 ~ 1.0)
        vorbis_buffer = vorbis_analysis_buffer(&vd, CurrentSampleCount / Channels);
        for (size_t i = 0; i < CurrentSampleCount; i += Channels)
        {
            for (int Channel = 0; Channel < Channels; Channel++)
            {
                vorbis_buffer[Channel][i / Channels] = PCMBuffer[PCMBufferSampleOffset + i] / 32768.0f;
            }
        }
        vorbis_analysis_wrote(&vd, CurrentSampleCount / Channels);

        // 编码并写入 Ogg 页面
        while (vorbis_analysis_blockout(&vd, &vb) == 1) {
            vorbis_analysis(&vb, NULL);
            vorbis_bitrate_addblock(&vb);

            ogg_packet op;
            while (vorbis_bitrate_flushpacket(&vd, &op))
            {
                ogg_stream_packetin(&os, &op);
                while (ogg_stream_pageout(&os, &og)) {
                    fwrite(og.header, 1, og.header_len, ogg_file);
                    fwrite(og.body, 1, og.body_len, ogg_file);
                }
            }
        }

        PCMBufferSampleOffset += CurrentSampleCount;

        LeftSampleCount -= CurrentSampleCount;
    }

    vorbis_analysis_wrote(&vd, 0); // 结束流

    // 6. 清理资源
    ogg_stream_clear(&os);
    vorbis_block_clear(&vb);
    vorbis_dsp_clear(&vd);
    vorbis_comment_clear(&vc);
    vorbis_info_clear(&vi);
    fclose(ogg_file);
}