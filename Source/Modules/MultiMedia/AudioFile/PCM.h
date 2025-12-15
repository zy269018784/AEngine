#pragma once
#include <vector>
#include <string>
/*
	mp2
	mp3
	flac			无损音乐存档
	aac				苹果音乐/Spotify/Youtube
	ac3				DVD/蓝光影碟杜比音效
	opus
	ogg
	3ga				3G手机录音/视频音频					3GPP容器
	669				Composer 669音乐模块
	a52 			Dolby Digital						AC3的早期文件扩展名
	adt				Adobe Audition多轨项目音频
	adts			AAC音频传输流
	aif				Standard AIFF
	aifc			Compressed AIFF
	aiff			专业音频工作站原始音频
	amb				环绕声Ambisonic格式
	amr				早期手机语音录音(Nokia时代)
	aob				DVD-Audio光盘音频
	ape				发烧友音乐收藏
	au				Sun/NeXT系统音频					早期Unix工作站格式
	awb				AMR-WB格式(宽频语音)
	caf				苹果Core Audio格式
	it				Impulse Tracker音乐模块
	kar				卡拉OK伴奏+歌词同步
	m4a				iTunes商店音乐（含DRM则为.m4p）
	m4b				有声书（支持书签功能）
	m4p
	m5p				索尼Minidisc加密音频				索尼私有格式
	mid				电子乐器控制指令（不含声音）
	mka
*/
class PCM
{
public:
	int ReadFromRawFile(std::string InputFile);
	int ReadFromRawFile16Normalized(std::string InputFile);
	void SetSampleRate(int n);
	int GetSampleRate();
	void SetBitRate(int n);
	int GetBitRate();
	void SetChannels(int n);
	int GetChannels();
	void SetSampleCount(int n);
	int GetSampleCount();
	void SetBytesPerSample(int n);
	int GetBytesPerSample();
	const std::vector<short>& GetPCMBuffer();
	const std::vector<int>& GetPCMBuffer32();
public:
	int Write(std::string OutputFile);
	int WriteMP2(std::string OutputFile);	// Ok
	int WriteMP3(std::string OutputFile);	// Ok
	int WriteAAC(std::string OutputFile);	// 0.5
	int WriteAC3(std::string OutputFile);
	int WriteOPUS(std::string OutputFile);
	int WriteFLAC(std::string OutputFile);	// OK
	int WriteLC3(std::string OutputFile);	// 0.1
	int WriteOGG(std::string OutputFile);	// OK
private:
	int BitRate;
	int SampleRate;
	int Channels;
	int BytesPerSample;
	std::vector<short> PCMBuffer;
	std::vector<int>   PCMBuffer32;
};