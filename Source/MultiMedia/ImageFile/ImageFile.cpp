#include "ImageFile.h"
#include "Math/Math.h"
/*
	c++
*/
#include <memory>
#include <vector>
#include <fstream>
/*
	stb
*/
#define STBI_WINDOWS_UTF8
#include <stb_image.h>
#include <stb_image_write.h>
/*
	openexr
*/
#include <OpenEXR/ImfHeader.h>
#include <OpenEXR/ImfFrameBuffer.h>
#include <OpenEXR/ImfThreading.h>
#include <OpenEXR/ImfNamespace.h>
#include <OpenEXR/ImfExport.h>
#include <OpenEXR/ImfForward.h>
#include <OpenEXR/ImfInputFile.h>
#include <OpenEXR/ImfOutputFile.h>
#include <OpenEXR/ImfTiledOutputFile.h>
#include <OpenEXR/ImfGenericInputFile.h>
#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfRgba.h>
#include <OpenEXR/ImfChannelList.h>
/*
	webp
*/
#include <webp/encode.h>
#include <webp/decode.h>
#include <webp/mux.h>
#include <webp/demux.h>
/*
	gif
*/
#include <gif_lib.h>

bool HasExtension(std::string filename, std::string e) {
    std::string ext = e;
    if (!ext.empty() && ext[0] == '.')
        ext.erase(0, 1);

    size_t pos = filename.find('.');
    std::string filenameExtension;
    if (pos != std::string::npos)
    {
        filenameExtension = filename.substr(pos + 1);
    }

    if (ext.size() > filenameExtension.size())
        return false;
    return std::equal(ext.rbegin(), ext.rend(), filenameExtension.rbegin(),
        [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}

ImageFile::ImageFile(Vector2u InResolution, PixelFormat InFormat, void* InPixels)
	: Resolution(InResolution), Format(InFormat), Pixels(InPixels)
{
	auto Count = Resolution.X * Resolution.Y;
	if (!InPixels)
	{
		switch (InFormat)
		{
		case ImageFile::PixelFormat::PF_R8G8B8_UINT:
			Count *= 3;
			Pixels = (void*)(new std::uint8_t[Count]);
			break;
		case ImageFile::PixelFormat::PF_R32G32B32_FLOAT:
			Count *= 3;
			Pixels = (void*)(new float[Count]);
			break;
		case ImageFile::PixelFormat::PF_R16G16B16_HALF:
			Count *= 1.5;
			Pixels = (void*)(new float[Count]);
			break;
		case ImageFile::PixelFormat::PF_R8G8B8A8_UINT:
			Count *= 4;
			Pixels = (void*)(new std::uint8_t[Count]);
			break;
		case ImageFile::PixelFormat::PF_R32G32B32A32_FLOAT:
			Count *= 4;
			Pixels = (void*)(new float[Count]);
			break;
		case ImageFile::PixelFormat::PF_R16G16B16A16_HALF:
			Count *= 2;
			Pixels = (void*)(new float[Count]);
			break;
		default:
			break;
		}
	}
}

ImageFile::~ImageFile()
{
	std::uint8_t* P8;
	float* P32;
	switch (Format)
	{
	case ImageFile::PixelFormat::PF_R8G8B8_UINT:
	case ImageFile::PixelFormat::PF_R8G8B8A8_UINT:
		P8 = (std::uint8_t*)(Pixels);
		delete P8;
		break;
	case ImageFile::PixelFormat::PF_R32G32B32_FLOAT:
	case ImageFile::PixelFormat::PF_R32G32B32A32_FLOAT:
		P32 = (float*)(Pixels);
		delete P32;
		break;
	case ImageFile::PixelFormat::PF_R16G16B16_HALF:
	case ImageFile::PixelFormat::PF_R16G16B16A16_HALF:
		P32 = (float*)(Pixels);
		delete P32;
		break;
	default:
		break;
	}
}

int ImageFile::NChannels() const
{
	int N = 0;
	switch (Format)
	{
	case ImageFile::PixelFormat::PF_R8G8B8_UINT:
	case ImageFile::PixelFormat::PF_R16G16B16_HALF:
	case ImageFile::PixelFormat::PF_R32G32B32_FLOAT:
		N = 3;
		break;
	case ImageFile::PixelFormat::PF_R8G8B8A8_UINT:
	case ImageFile::PixelFormat::PF_R16G16B16A16_HALF:
	case ImageFile::PixelFormat::PF_R32G32B32A32_FLOAT:
		N = 4;
		break;
	default:
		break;
	}

	return N;
}

float ImageFile::GetChannel(Vector2i P, int Channel, WrapMode WrapModeU, WrapMode WrapModeV) const
{
	float V;
	if (!RemapPixelCoords(&P, WrapModeU, WrapModeV))
		return 0;
	int Offset = P.Y * Resolution.X + P.X;
	std::uint8_t* P8;
	float* P32;
	switch (Format)
	{
	case ImageFile::PixelFormat::PF_R8G8B8_UINT:
		P8 = (std::uint8_t*)(Pixels);
		Offset = 3 * Offset + Channel;
		V = P8[Offset];
		break;
	case ImageFile::PixelFormat::PF_R16G16B16_HALF:
		Offset = 3 * Offset + Channel;
		break;
	case ImageFile::PixelFormat::PF_R32G32B32_FLOAT:
		P32 = (float*)(Pixels);
		Offset = 3 * Offset + Channel;
		V = P32[Offset];
		break;
	case ImageFile::PixelFormat::PF_R8G8B8A8_UINT:
		P8 = (std::uint8_t*)(Pixels);
		Offset = 4 * Offset + Channel;
		V = P8[Offset];
		break;
	case ImageFile::PixelFormat::PF_R16G16B16A16_HALF:
		Offset = 4 * Offset + Channel;
		break;
	case ImageFile::PixelFormat::PF_R32G32B32A32_FLOAT:
		P32 = (float*)(Pixels);
		Offset = 4 * Offset + Channel;
		V = P32[Offset];
		break;
	default:
		break;
	}
	return V;
}

bool ImageFile::RemapPixelCoords(Vector2i* P, WrapMode WrapModeU, WrapMode WrapModeV) const
{
	switch (WrapModeU)
	{
	case ImageFile::WrapMode::Black:
		break;
	case ImageFile::WrapMode::Clamp:
		P->X = Clamp(P->X, 0, Resolution.X - 1);
		break;
	case ImageFile::WrapMode::Repeat:
		P->X = Mod(P->X, Resolution.X);
		break;
	case ImageFile::WrapMode::OctahedralSphere:
		break;
	default:
		break;
	}
	switch (WrapModeV)
	{
	case ImageFile::WrapMode::Black:
		break;
	case ImageFile::WrapMode::Clamp:
		P->Y = Clamp(P->Y, 0, Resolution.X - 1);
		break;
	case ImageFile::WrapMode::Repeat:
		P->Y = Mod(P->X, Resolution.Y);
		break;
	case ImageFile::WrapMode::OctahedralSphere:
		break;
	default:
		break;
	}
	return true;
}

bool ImageFile::Write(std::string filename) const
{
	if (HasExtension(filename, "png"))
		return WritePNG(filename);
	else if (HasExtension(filename, "jpg") || HasExtension(filename, "jpeg"))
		return WriteJPG(filename);
	else if (HasExtension(filename, "hdr"))
		return WriteHDR(filename);
	else if (HasExtension(filename, "tga"))
		return WriteTGA(filename);
	else if (HasExtension(filename, "bmp"))
		return WriteBMP(filename);
	else if (HasExtension(filename, "exr"))
		return WriteEXR(filename);
	else if (HasExtension(filename, "webp"))
		return WriteWEBP(filename);
	else if (HasExtension(filename, "gif"))
		return WriteGIF(filename);
	return false;
}

ImageFile* ImageFile::Read(std::string filename)
{
	if (HasExtension(filename, "png"))
		return ReadPNG(filename);
	else if (HasExtension(filename, "jpg") || HasExtension(filename, "jpeg"))
		return ReadJPG(filename);
	else if (HasExtension(filename, "hdr"))
		return ReadHDR(filename);
	else if (HasExtension(filename, "tga"))
		return ReadTGA(filename);
	else if (HasExtension(filename, "bmp"))
		return ReadBMP(filename);
	else if (HasExtension(filename, "exr"))
		return ReadEXR(filename);
	else if (HasExtension(filename, "webp"))
		return ReadWEBP(filename);
	return nullptr;
}

ImageFile* ImageFile::ReadPNG(const std::string filename)
{
	ImageFile* image = nullptr;
	int width, height, channels;
	std::uint8_t* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	std::cout << "png channels " << channels << std::endl;
	if (data) {
		std::vector<std::uint8_t> pixels;
		std::copy(data, data + width * height * channels / sizeof(unsigned char), std::back_inserter(pixels));

		switch (channels) {
		case 3:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		case 4:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8A8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		default:
			printf("%s: %d channel image unsupported.", filename.c_str(), channels);
		}
	}
	return image;
}

ImageFile* ImageFile::ReadJPG(const std::string filename)
{
	ImageFile* image = nullptr;
	int width, height, channels;
	std::uint8_t* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	if (data) {
		std::vector<std::uint8_t> pixels;
		std::copy(data, data + width * height * channels / sizeof(unsigned char), std::back_inserter(pixels));

		switch (channels) {
		case 3: 
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		case 4: 
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8A8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		default:
			printf("%s: %d channel image unsupported.", filename.c_str(), channels);
		}
	}
	return image;
}

ImageFile* ImageFile::ReadTGA(const std::string filename)
{
	ImageFile* image = nullptr;
	int width, height, channels;
	std::uint8_t* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	if (data) {
		std::vector<std::uint8_t> pixels;
		std::copy(data, data + width * height * channels / sizeof(unsigned char), std::back_inserter(pixels));

		switch (channels) {
		case 3:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		case 4:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8A8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		default:
			printf("%s: %d channel image unsupported.", filename.c_str(), channels);
		}
	}
	return image;
}

ImageFile* ImageFile::ReadBMP(const std::string filename)
{
	ImageFile* image = nullptr;
	int width, height, channels;
	std::uint8_t* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	if (data) {
		std::vector<std::uint8_t> pixels;
		std::copy(data, data + width * height * channels / sizeof(unsigned char), std::back_inserter(pixels));

		switch (channels) {
		case 3:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		case 4:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8A8_UINT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		default:
			printf("%s: %d channel image unsupported.", filename.c_str(), channels);
		}
	}
	return image;
}

ImageFile* ImageFile::ReadHDR(const std::string filename)
{
	ImageFile* image = nullptr;
	int width, height, channels;
	float* data = stbi_loadf(filename.c_str(), &width, &height, &channels, 0);
	if (data) {
		std::vector<float> pixels;
		std::copy(data, data + width * height * channels / sizeof(unsigned char), std::back_inserter(pixels));

		switch (channels) {
		case 3:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R32G32B32_FLOAT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		case 4:
			image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R32G32B32A32_FLOAT);
			std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
			break;
		default:
			printf("%s: %d channel image unsupported.", filename.c_str(), channels);
		}
	}
	return image;
}

ImageFile* ImageFile::ReadEXR(const std::string filename)
{
	return nullptr;
}

static std::vector<uint8_t> readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open()) return {};

	size_t size = file.tellg();
	file.seekg(0);
	std::vector<uint8_t> data(size);
	file.read(reinterpret_cast<char*>(data.data()), size);
	file.close();
	return data;
}

ImageFile* ImageFile::ReadWEBP(const std::string filename)
{
	ImageFile* image = nullptr;
	int width, height, channels;
	std::uint8_t* rgb_data = nullptr;
	// 读取文件数据
	std::vector<std::uint8_t> webp_data = readFile(filename);
	if (webp_data.empty()) {
		return {};
	}

	WebPBitstreamFeatures features;
	VP8StatusCode status = WebPGetFeatures(webp_data.data(), webp_data.size(), &features);
	//std::cout << "ReadWEBP features.has_alpha " << features.has_alpha << " " << features.width  << " " << features.height << std::endl;
	if (!features.has_alpha)
	{
		// 解码为 RGB
		rgb_data = WebPDecodeRGB(webp_data.data(), webp_data.size(), &width, &height);
		if (!rgb_data) {
			std::cerr << "Failed to decode WebP as RGB" << std::endl;
			return {};
		}

		/*
			拷贝到临时缓冲
		*/
		std::vector<std::uint8_t> pixels;
		std::copy(rgb_data, rgb_data + width * height * 3, std::back_inserter(pixels));
		/*
			拷贝image内存
		*/
		image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8_UINT);
		std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
	}
	else
	{
		// 解码为 RGBA
		rgb_data = WebPDecodeRGBA(webp_data.data(), webp_data.size(), &width, &height);
		if (!rgb_data) {
			std::cerr << "Failed to decode WebP as RGB" << std::endl;
			return {};
		}

		/*
			拷贝到临时缓冲
		*/
		std::vector<std::uint8_t> pixels;
		std::copy(rgb_data, rgb_data + width * height * 4, std::back_inserter(pixels));

		/*
			拷贝image内存
		*/
		image = new ImageFile(Vector2u(width, height), PixelFormat::PF_R8G8B8A8_UINT);
		std::copy(pixels.begin(), pixels.end(), (std::uint8_t*)image->Pixels);
	}

	WebPFree(rgb_data);
	return image;
}

ImageFile* ImageFile::ReadGIF(const std::string name)
{
	ImageFile* image = nullptr;
	return image;
}

bool ImageFile::WritePNG(std::string filename) const
{
#if 1
	std::unique_ptr<uint8_t[]> Pixel8 = std::make_unique<uint8_t[]>(NChannels() * Resolution.X * Resolution.Y);
	for (int row = 0; row < Resolution.Y; row++) {
		for (int col = 0; col < Resolution.X; col++) {
			for (int c = 0; c < NChannels(); ++c) {
				Pixel8[NChannels() * (row * Resolution.X + col) + c] = GetChannel({ col, row }, c);
			}
		}
	}
	stbi_write_png(filename.c_str(), Resolution.X, Resolution.Y, NChannels(), Pixel8.get(), 0);
	return true;
#else
	return fpng::fpng_encode_image_to_file(filename.c_str(), p8, resolution.x, Resolution.Y, channelNameSize);
#endif
}

bool ImageFile::WriteJPG(std::string filename) const
{
	std::unique_ptr<uint8_t[]> Pixel8 = std::make_unique<uint8_t[]>(NChannels() * Resolution.X * Resolution.Y);
	for (int row = 0; row < Resolution.Y; row++) {
		for (int col = 0; col < Resolution.X; col++) {
			for (int c = 0; c < NChannels(); ++c) {
				Pixel8[NChannels() * (row * Resolution.X + col) + c] = GetChannel({ col, row }, c);
			}
		}
	}
	stbi_write_jpg(filename.c_str(), Resolution.X, Resolution.Y, NChannels(), Pixel8.get(), 100);
	return true;
}

bool ImageFile::WriteTGA(std::string filename) const
{
	std::unique_ptr<uint8_t[]> Pixel8 = std::make_unique<uint8_t[]>(NChannels() * Resolution.X * Resolution.Y);
	for (int row = 0; row < Resolution.Y; row++) {
		for (int col = 0; col < Resolution.X; col++) {
			for (int c = 0; c < NChannels(); ++c) {
				Pixel8[NChannels() * (row * Resolution.X + col) + c] = GetChannel({ col, row }, c);
			}
		}
	}
	stbi_write_tga(filename.c_str(), Resolution.X, Resolution.Y, NChannels(), Pixel8.get());
	return true;
}

bool ImageFile::WriteBMP(std::string filename) const
{
	std::unique_ptr<uint8_t[]> Pixel8 = std::make_unique<uint8_t[]>(NChannels() * Resolution.X * Resolution.Y);
	for (int row = 0; row < Resolution.Y; row++) {
		for (int col = 0; col < Resolution.X; col++) {
			for (int c = 0; c < NChannels(); ++c) {
				Pixel8[NChannels() * (row * Resolution.X + col) + c] = GetChannel({ col, row }, c);
			}
		}
	}
	stbi_write_bmp(filename.c_str(), Resolution.X, Resolution.Y, NChannels(), Pixel8.get());
	return true;
}

bool ImageFile::WriteHDR(std::string filename) const
{
	std::unique_ptr<float []> Pixel32 = std::make_unique<float[]>(NChannels() * Resolution.X * Resolution.Y);
	for (int row = 0; row < Resolution.Y; row++) {
		for (int col = 0; col < Resolution.X; col++) {
			for (int c = 0; c < NChannels(); ++c) {
				Pixel32[NChannels() * (row * Resolution.X + col) + c] = GetChannel({ col, row }, c);
			}
		}
	}
	stbi_write_hdr(filename.c_str(), Resolution.X, Resolution.Y, NChannels(), Pixel32.get());
	return true;
}

bool ImageFile::WriteEXR(std::string filename) const
{
	Imf::Rgba* pixels = new Imf::Rgba[Resolution.X * Resolution.Y];

	for (int row = 0; row < Resolution.Y; row++) {
		for (int col = 0; col < Resolution.X; col++) {
			if (NChannels() > 0)
				pixels[(row * Resolution.X + col)].r = (GetChannel({ col, row }, 0));
			if (NChannels() > 1)
				pixels[(row * Resolution.X + col)].g = (GetChannel({ col, row }, 1));
			if (NChannels() > 2)
				pixels[(row * Resolution.X + col)].b = (GetChannel({ col, row }, 2));
			if (NChannels() > 3)
				pixels[(row * Resolution.X + col)].a = (GetChannel({ col, row }, 3));
			else pixels[(row * Resolution.X + col)].a = 1.0f;
		}
	}

	Imf::RgbaChannels chs;
	if (NChannels() == 4)
		chs = Imf::WRITE_RGBA;
	else
		chs = Imf::WRITE_RGB;
	chs = Imf::WRITE_RGBA;

	Imf::RgbaOutputFile file(filename.c_str(), Resolution.X, Resolution.Y, chs);
	file.setFrameBuffer(pixels, 1, Resolution.X);
	file.writePixels(Resolution.Y);

	delete[] pixels;
	return true;
}
/*
	std::unique_ptr<float []> Pixel32 = std::make_unique<float[]>(NChannels() * Resolution.X * Resolution.Y);
	for (int row = 0; row < Resolution.Y; row++) {
		for (int col = 0; col < Resolution.X; col++) {
			for (int c = 0; c < NChannels(); ++c) {
				Pixel32[NChannels() * (row * Resolution.X + col) + c] = GetChannel({ col, row }, c);
			}
		}
	}
	stbi_write_hdr(filename.c_str(), Resolution.X, Resolution.Y, NChannels(), Pixel32.get());
	return true;
*/
bool ImageFile::WriteWEBP(std::string filename) const
{
	std::uint8_t* output = nullptr;
	size_t size = 0;
	if (4 == NChannels())
	{	
		const std::uint8_t* rgba_data = (std::uint8_t*)Pixels;
		// 编码 RGBA 数据（支持透明度）
		size = WebPEncodeRGBA(rgba_data, Resolution.X, Resolution.Y, Resolution.X * 4, 80.f, &output);
	}
	else
	{
		const std::uint8_t* rgb_data = (std::uint8_t*)Pixels;
		// 编码 RGB 数据
		size = WebPEncodeRGB(rgb_data, Resolution.X, Resolution.Y, Resolution.X * 3, 80.f , &output);
	}

	if (size == 0) {
		std::cerr << "WebP encoding failed" << std::endl;
		return false;
	}

	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		WebPFree(output);
		return false;
	}

	file.write(reinterpret_cast<char*>(output), size);
	file.close();
	WebPFree(output);
	return true;
}

bool ImageFile::WriteGIF(std::string filename) const
{
	int error = 0;
	GifFileType* gif = EGifOpenFileName(filename.c_str(), false, &error);
	if (!gif) {
		printf("Error creating GIF file: %s\n", GifErrorString(error));
		return 1;
	}

	int width  = Resolution.X;
	int height = Resolution.Y;
	int colorMapSize = 256;

	// 创建颜色映射
	ColorMapObject* colorMap = GifMakeMapObject(colorMapSize, NULL);
	if (!colorMap) {
		printf("Error creating color map\n");
		EGifCloseFile(gif, &error);
		return 1;
	}

	// 填充颜色映射（这里创建一个简单的灰度映射）
	for (int i = 0; i < colorMapSize; i++) {
		colorMap->Colors[i].Red = i;
		colorMap->Colors[i].Green = i;
		colorMap->Colors[i].Blue = i;
	}

	// 设置 GIF 的全局颜色映射
	gif->SColorMap = colorMap;

	// 设置 GIF 屏幕描述符
	gif->SWidth  = width;
	gif->SHeight = height;
	gif->SColorResolution = 8;
	gif->SBackGroundColor = 0;
	gif->AspectByte = 0;

	// 分配图像数据（这里创建一个简单的渐变）
	GifByteType* pixels = (GifByteType*)malloc(width * height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = (x + y) % colorMapSize;
			pixels[y * width + x] = index;
		}
	}

	// 写入图像描述符
	if (EGifPutImageDesc(gif, 0, 0, width, height, false, NULL) != GIF_OK) {
		printf("Error writing image descriptor: %s\n", GifErrorString(gif->Error));
		free(pixels);
		GifFreeMapObject(colorMap);
		EGifCloseFile(gif, &error);
		return 1;
	}

	// 写入图像数据（按行写入）
	for (int i = 0; i < height; i++) {
		if (EGifPutLine(gif, pixels + i * width, width) != GIF_OK) {
			printf("Error writing image data: %s\n", GifErrorString(gif->Error));
			free(pixels);
			GifFreeMapObject(colorMap);
			EGifCloseFile(gif, &error);
			return 1;
		}
	}

	free(pixels);
	GifFreeMapObject(colorMap);
	EGifCloseFile(gif, &error);
	return true;
}

bool ImageFile::WriteSVG(std::string name) const
{
	return true;
}




