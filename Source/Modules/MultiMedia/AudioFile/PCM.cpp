#include "PCM.h"
#include <filesystem>
#include <iostream>
#ifdef PROJECT_USE_MP3LAME
	#include <lame/lame.h>
#endif
#ifdef PROJECT_USE_OGG
	#include <ogg/ogg.h>
#endif
#ifdef PROJECT_USE_VORBIS
	#include <vorbis/vorbisenc.h>
#endif
#ifdef PROJECT_USE_FLAC
	#define FLAC__NO_DLL
	#include <FLAC/stream_encoder.h>
#endif
#ifdef PROJECT_USE_FDKAAC
	#include <fdk-aac/aacenc_lib.h>
	#include <fdk-aac/aacdecoder_lib.h>
#endif
#ifdef PROJECT_USE_TWOLAME
	#include <twolame.h>
#endif
#ifdef 	PROJECT_USE_LC3
	#include <lc3.h>
#endif

int PCM::ReadFromRawFile(std::string InputFile)
{
	size_t FileSize = 0;
	FILE* file = fopen(InputFile.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	FileSize = ftell(file);

	SetSampleCount(FileSize / BytesPerSample);

	fseek(file, 0, SEEK_SET);

	fread(PCMBuffer.data(), BytesPerSample, GetSampleCount(), file);

	PCMBuffer32.resize(GetSampleCount());
	for (size_t i = 0; i < PCMBuffer32.size(); i++)
	{
		PCMBuffer32[i] = PCMBuffer[i];
	}

	fclose(file);

	return 0;
}

int PCM::ReadFromRawFile16Normalized(std::string InputFile)
{
	size_t FileSize = 0;
	FILE* file = fopen(InputFile.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	FileSize = ftell(file);

	SetSampleCount(FileSize / BytesPerSample);

	fseek(file, 0, SEEK_SET);

	fread(PCMBuffer.data(), BytesPerSample, GetSampleCount(), file);
	/*
		将 16-bit PCM 转换为浮点 (-1.0 ~ 1.0)
	*/
	for (size_t i = 0; i < PCMBuffer.size(); i++)
	{
		PCMBuffer[i] = PCMBuffer[i] / 32768.0f;
	}

	fclose(file);

	return 0;
}

void PCM::SetSampleRate(int n)
{
	SampleRate = n;
}

int PCM::GetSampleRate()
{
	return SampleRate;
}

void PCM::SetChannels(int n)
{
	Channels = n;
}

void PCM::SetBitRate(int n)
{
	BitRate = n;
}

int PCM::GetBitRate()
{
	return BitRate;
}

int  PCM::GetChannels()
{
	return Channels;
}

void PCM::SetSampleCount(int n)
{
	PCMBuffer.resize(n);
}

int PCM::GetSampleCount()
{
	return PCMBuffer.size();
}

const std::vector<short>& PCM::GetPCMBuffer()
{
	return PCMBuffer;
}

const std::vector<int>& PCM::GetPCMBuffer32()
{
	return PCMBuffer32;
}

void PCM::SetBytesPerSample(int n)
{
	BytesPerSample = n;
}

int PCM::GetBytesPerSample()
{
	return BytesPerSample;
}
bool HasExtension(const std::filesystem::path& filePath, const std::string& targetExt);

int PCM::Write(std::string OutputFilename) {
	if (HasExtension(OutputFilename, ".mp2"))
	{
		return WriteMP2(OutputFilename);
	}
	else if (HasExtension(OutputFilename, ".mp3"))
	{
		return WriteMP3(OutputFilename);
	}
	else if (HasExtension(OutputFilename, ".ogg"))
	{
		return WriteOGG(OutputFilename);
	}
	else if (HasExtension(OutputFilename, ".flac"))
	{
		return WriteFLAC(OutputFilename);
	}
	else if (HasExtension(OutputFilename, ".aac"))
	{
		return WriteAAC(OutputFilename);
	}
	else if (HasExtension(OutputFilename, ".ac3"))
	{
		return WriteAC3(OutputFilename);
	}
	else if (HasExtension(OutputFilename, ".lc3"))
	{
		return WriteLC3(OutputFilename);
	}
	else if (HasExtension(OutputFilename, ".opus"))
	{
		return WriteOPUS(OutputFilename);
	}
	else
	{
		printf("unsupportted format\n");
	}
	return 0;
}

int PCM::WriteMP2(std::string OutputFile)
{
#ifdef PROJECT_USE_TWOLAME
	twolame_options * glopts = twolame_init();


	twolame_set_in_samplerate(glopts,  GetSampleRate());
	twolame_set_out_samplerate(glopts, GetSampleRate());
	twolame_set_num_channels(glopts, GetChannels());
	twolame_set_bitrate(glopts, GetBitRate());
	twolame_set_psymodel(glopts, -1);  // 使用默认心理声学模型
	twolame_set_energy_levels(glopts, 1);  // 启用能量水平扩展
	twolame_set_error_protection(glopts, 0);  // 禁用CRC错误保护
	twolame_set_copyright(glopts, 0);
	twolame_set_original(glopts, 1);
	twolame_init_params(glopts);

	auto num_samples = twolame_get_framelength(glopts);
	// 6. 分配缓冲区
	auto input_buffer = (short*)malloc(num_samples * GetChannels() * sizeof(short));
	auto output_buffer = (unsigned char*)malloc(16384);  // MP2帧最大可能大小

	FILE* File = fopen(OutputFile.c_str(), "wb");
	if (!File)
	{
		return -1;
	}
	/*
		PCM样本数量
	*/
	int LeftSampleCount = GetSampleCount();
	const int SampleCountPerLoop = 8192;
	int CurrentSampleCount  = SampleCountPerLoop;
	int PCMBufferSampleOffset = 0;

	unsigned char *mp2buffer = (unsigned char *)malloc(8192);
	int mp2buffer_size = 8192;
	while (LeftSampleCount > 0)
	{
		CurrentSampleCount = SampleCountPerLoop;
		if (LeftSampleCount < SampleCountPerLoop)
			CurrentSampleCount = LeftSampleCount;

		int  NumSamples = CurrentSampleCount / GetChannels();

		int bytes = twolame_encode_buffer_interleaved(glopts, PCMBuffer.data() + PCMBufferSampleOffset, NumSamples, mp2buffer, mp2buffer_size);
		if (bytes > 0)
		{
			fwrite(mp2buffer, 1, bytes, File);
		}
		else
			break;
		printf("PCMBufferSampleOffset %d\n", PCMBufferSampleOffset);
		PCMBufferSampleOffset += CurrentSampleCount;

		LeftSampleCount -= CurrentSampleCount;
	}

	fclose(File);
	twolame_close(&glopts);
#endif
	return 0;
}

int PCM::WriteMP3(std::string OutputFile)
{
#ifdef PROJECT_USE_MP3LAME
	FILE* MP3File = fopen(OutputFile.c_str(), "wb");
    if (!MP3File)
    {
        return -1;
    }

	lame_global_flags* GlobalFlags = nullptr;
    GlobalFlags = lame_init();
	lame_set_in_samplerate(GlobalFlags, GetSampleRate());
	lame_set_num_channels(GlobalFlags,  GetChannels());
	lame_set_quality(GlobalFlags, 2);  // 质量等级 2(较好)
	lame_init_params(GlobalFlags);

    const int MP3_BUFFER_SIZE = 8192;
    unsigned char MP3Buffer[MP3_BUFFER_SIZE];

    /*
        PCM样本数量
    */
    int LeftSampleCount = GetSampleCount();
    /*
        通道数量
    */
    int Channels = GetChannels();
    /*
        PCM样本Buffer
    */
    auto PCMBuffer = GetPCMBuffer();
    int PCMBufferSampleOffset = 0;
    /*
        每次循环处理8192个样本
        1个Sample = Channels个PCM Sample
    */
    const int SampleCountPerLoop = 8192;
    int CurrentSampleCount  = SampleCountPerLoop;
    size_t NumWriteBytes = 0;
    while (LeftSampleCount > 0)
    {
        CurrentSampleCount = SampleCountPerLoop;
        if (LeftSampleCount < SampleCountPerLoop)
            CurrentSampleCount = LeftSampleCount;
        /*
             Channels个PCM样本构成1个样本
            1个样本 = Channels个PCM样本
            1个Sample = Channels个PCM Sample
        */
        int  NumSamples = CurrentSampleCount / Channels;
        int encoded = lame_encode_buffer_interleaved(
            GlobalFlags, PCMBuffer.data() + PCMBufferSampleOffset, NumSamples, MP3Buffer, MP3_BUFFER_SIZE
        );

        NumWriteBytes += fwrite(MP3Buffer, 1, encoded, MP3File);
        //printf("NumWriteBytes %llu, PCMBufferSampleOffset %d, encoded %d, CurrentSampleCount %d\n",
        //    NumWriteBytes, PCMBufferSampleOffset, encoded, CurrentSampleCount);

        PCMBufferSampleOffset += CurrentSampleCount;

        LeftSampleCount -= CurrentSampleCount;
    }

    // 刷新剩余数据
    int final = lame_encode_flush(GlobalFlags, MP3Buffer, MP3_BUFFER_SIZE);
    NumWriteBytes += fwrite(MP3Buffer, 1, final, MP3File);

    lame_close(GlobalFlags);
#endif
	return 0;
}

int PCM::WriteAAC(std::string OutputFile)
{
#ifdef PROJECT_USE_FDKAAC
	HANDLE_AACENCODER Encoder;
	AACENC_ERROR ErrorStatus;

	ErrorStatus = aacEncOpen(&Encoder, 0, GetChannels());
	if (AACENC_OK != ErrorStatus)
	{
		fprintf(stderr, "无法打开编码器\n");
		return -1;
	}
	/*
	 *	Mandatory Encoder Parameters
	 */
	aacEncoder_SetParam(Encoder, AACENC_CHANNELMODE, GetChannels());
	aacEncoder_SetParam(Encoder, AACENC_SAMPLERATE, GetSampleRate());
	aacEncoder_SetParam(Encoder, AACENC_BITRATE,    GetBitRate());
	aacEncoder_SetParam(Encoder, AACENC_CHANNELMODE, MODE_2);
	/*
	 *	Audio Quality
	 */
	aacEncoder_SetParam(Encoder, AACENC_AFTERBURNER, 1);

	aacEncoder_SetParam(Encoder, AACENC_CHANNELORDER, 1);
	aacEncoder_SetParam(Encoder, AACENC_TRANSMUX, TT_MP4_ADTS);

	ErrorStatus = aacEncEncode(Encoder, NULL, NULL, NULL, NULL);

	int InBufferSize = GetSampleCount() * GetBytesPerSample();
	void *InBuffer = PCMBuffer.data();
	int InElSize = GetBytesPerSample();
	//int InBufferIds[] = { IN_AUDIO_DATA, IN_ANCILLRY_DATA, IN_METADATA_SETUP };
	int InBufferIds[] = { IN_AUDIO_DATA};
	AACENC_BufDesc inBufDesc = {0};
	inBufDesc.numBufs = 1;
	inBufDesc.bufs = &InBuffer;
	inBufDesc.bufferIdentifiers = InBufferIds;
	inBufDesc.bufSizes   = &InBufferSize;
	inBufDesc.bufElSizes = &InElSize;


	void* OutBuffer =  (void *)malloc(8192 * 8 ) ;
	int OutBufferIds = { OUT_BITSTREAM_DATA };
	int OutBufferSize = { 8192 * 8 };
	int OutBufferElSize = { sizeof(char) };

	AACENC_BufDesc outBufDesc;
	outBufDesc.numBufs = 1;
	outBufDesc.bufs = &OutBuffer;
	outBufDesc.bufferIdentifiers = &OutBufferIds;
	outBufDesc.bufSizes = &OutBufferSize;
	outBufDesc.bufElSizes = &OutBufferElSize;

	AACENC_InArgs in_args = {0};
	in_args.numInSamples = GetSampleCount() / 2;

	// 设置输出参数
	AACENC_OutArgs out_args = {0};

	//do {
		ErrorStatus = aacEncEncode(Encoder, &inBufDesc,&outBufDesc, &in_args, &out_args);
	//}while (ErrorStatus==AACENC_OK);
	FILE* File = fopen(OutputFile.c_str(), "wb");
	if (!File)
	{
		return -1;
	}

	printf("out_args.numOutBytes %d\n", out_args.numOutBytes);
	printf("InBufferSize %d\n", PCMBuffer.size() * 2);
	printf("InBufferSize %d\n", InBufferSize);

	fwrite(reinterpret_cast<const char*>(OutBuffer), 1, out_args.numOutBytes, File);


	fclose(File);
	aacEncClose(&Encoder);
#endif
	return 0;
}

int PCM::WriteAC3(std::string OutputFile)
{

	return 0;
}

int PCM::WriteOPUS(std::string OutputFile)
{
	return 0;
}


#ifdef PROJECT_USE_FLAC
static FLAC__StreamEncoderWriteStatus FLAC_WriteCallback(
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
#endif

int PCM::WriteFLAC(std::string OutputFile)
{
#ifdef PROJECT_USE_FLAC
    unsigned sample_rate = GetSampleRate();
    /*
        通道数量
    */
    unsigned channels = GetChannels();
    /*
        每个PCM样本多少位 = 每个样本字节数 * 8
    */
    //InPCM->SetBytesPerSample(4);
    unsigned BitsPerSample = GetBytesPerSample() * 8;
    //BitsPerSample = 32;
    auto total_pcm_samples = GetSampleCount();

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
    FLAC__stream_encoder_init_stream(encoder, FLAC_WriteCallback, NULL, NULL, NULL, flac);

    /*
        样本数量
    */
    int LeftSampleCount = GetSampleCount();
    /*
        通道数量
    */
    int Channels = GetChannels();
    auto PCMBuffer = GetPCMBuffer32();
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
#endif
	return 0;
}

int PCM::WriteLC3(std::string OutputFile)
{
#ifdef 	PROJECT_USE_LC3

#endif
	return 0;
}

int PCM::WriteOGG(std::string OutputFile)
{
#ifdef PROJECT_USE_OGG
    FILE* ogg_file = fopen(OutputFile.data(), "wb");
    if (!ogg_file)
    {
        return -1;
    }
    /*
        样本数量
    */
    int LeftSampleCount = GetSampleCount();
    /*
        通道数量
    */
    int Channels = GetChannels();
    /*
        PCM Buffer
    */
    auto PCMBuffer = GetPCMBuffer();
    int PCMBufferSampleOffset = 0;
    /*
        样本率
    */
    int SampleRate = GetSampleRate();
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
#endif
	return 0;
}