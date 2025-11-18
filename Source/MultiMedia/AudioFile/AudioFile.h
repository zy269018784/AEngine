#pragma once
#include <string>
#include "PCM.h"
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
class AudioFile
{
public:
	enum class Backend : uint8_t
	{
		FFMPEG,
		LAME,
		FDK_AAC,
		OPUS,
		FLAC,
	};

	enum class Channels : uint8_t
	{
		/*
			单声道
		*/
		Mono = 1,
		/*
			立体声	= Left + Right
		*/
		Stereo = 2,
		/*
			2.1声道	= Left + Right + LFE
		*/
		Stereo_LFE = 3,
		/*
			5.1声道 = Front Left + Font Right + Center + Surround Left + Surround Right + LFE
			支持的文件格式: Flac
		*/
		Channel_Surround_Sound_5_1 = 4,
		/*
			7.1声道 = Front Left + Font Right + Back Left + Back Right + Center + Surround Left + Surround Right + LFE
			支持的文件格式: Flac, Opus
		*/
		Channel_Surround_Sound_7_1 = 4,
	};
public:
	AudioFile();
	~AudioFile();
	int EncodePCM(char* InputFilename, char* OutputFilename);
	int EncodePCM(PCM *data, char* OutputFilename);
private:
	int EncodeToMP2(char* InputFilename, char* OutputFilename);
	int EncodeToMP3(char* InputFilename, char* OutputFilename);
	int EncodeToAAC(char* InputFilename, char* OutputFilename);
	int EncodeToAC3(char* InputFilename, char* OutputFilename);
	int EncodeToOPUS(char* InputFilename, char* OutputFilename);
	int EncodeToFLAC(char* InputFilename, char* OutputFilename);
	int EncodeToLC3(char* InputFilename, char* OutputFilename);
	int EncodeToOGG(char* InputFilename, char* OutputFilename);
};