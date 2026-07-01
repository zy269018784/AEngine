#pragma once
#if 0
#include "GMath/Types/Vector.h"
#include "GMath/Types/Rect.h"
#include <cstdint>
#include <string>
class ImageFile
{
public:
	enum class PixelFormat : std::uint32_t
	{
        PF_R8_UINT,			        //   8 bit unsigned byte		R

        PF_R8G8B8_UINT,			//   8 bit unsigned byte		R	G	B
        PF_R16G16B16_HALF,		//   16 bit float				R	G	B
        PF_R32G32B32_FLOAT,		//   32 bit float				R	G	B
        
        PF_R8G8B8A8_UINT,			//   8 bit unsigned byte		R	G	B	A
        PF_R16G16B16A16_HALF,		//   16 bit float				R	G	B	A
        PF_R32G32B32A32_FLOAT,		//   32 bit float				R	G	B	A
	};
    enum class WrapMode : std::uint32_t
    { 
        Black, 
        Clamp, 
        Repeat, 
        OctahedralSphere
    };
public:
    ImageFile() = default;
    ImageFile(Vector2u InResolution, ImageFile::PixelFormat InFormat, void* InPixels = nullptr);
    virtual ~ImageFile();
public:
    int NChannels() const;
    ImageFile::PixelFormat GetFormat() const;
    Vector2u GetResolution() const;
    float GetChannel(Vector2i P, int Channel, WrapMode WrapModeU = WrapMode::Clamp, WrapMode WrapModeV = WrapMode::Clamp) const;
    bool RemapPixelCoords(Vector2i* P, WrapMode WrapModeU, WrapMode WrapModeV) const;
public:
    void DrawImage(Vector2u P, const ImageFile& Image);
    void DrawEllipse(Rectu Rect);
    void DrawLine(const Vector2u& p1, const Vector2u& p2);
    void DrawLine(int x1, int y1, int x2, int y2);
    void DrawRect(const Rectu& rectangle);
    void DrawText(const Vector2u& position, const std::string& text);
public:
	static ImageFile* Read(std::string filename);
    bool Write(std::string name) const;
private:
    static ImageFile* ReadPNG(const std::string name);
    static ImageFile* ReadJPG(const std::string name);
    static ImageFile* ReadTGA(const std::string name);
    static ImageFile* ReadBMP(const std::string name);
    static ImageFile* ReadHDR(const std::string name);
    static ImageFile* ReadEXR(const std::string name);
    static ImageFile* ReadWEBP(const std::string name);
    static ImageFile* ReadGIF(const std::string name);
private:
    bool WritePNG(std::string name) const;
    bool WriteJPG(std::string name) const;
    bool WriteTGA(std::string name) const;
    bool WriteBMP(std::string name) const;
    bool WriteHDR(std::string name) const;
    bool WriteEXR(std::string name) const;
    bool WriteWEBP(std::string name) const;
    bool WriteGIF(std::string name) const;
    bool WriteSVG(std::string name) const;
private:
    /*
        分辨率
    */
    Vector2u Resolution;
	/*
		像素格式
	*/
	PixelFormat Format;
    /*
        像素指针
    */
    void* Pixels;
};
#endif