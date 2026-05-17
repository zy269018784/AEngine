#include "ES32RHI/OpenGLObjects/Texture/ES32Texture.h"
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include "ES32RHI/ES32PixelFormat.h"
/*
* ES 3.2 Texture
*   创建     glGenTextures
*   绑定     glBindTexture
*   指定格式  glTexStorage2D, glTexStorage3D，
*   上传数据  glTexSubImage2D, glTexSubImage3D
 */
ES32Texture::ES32Texture(RHIDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InArraySize, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, void *InData)
    : RHITexture(InType, InFormat,  InX, InY, InZ, InNumMips, InArraySize, InData), Device(InDevice)
{
    std::cout << "ES32Texture "  << "InNumMips " << InNumMips << std::endl;
    glGenTextures(1, &Handle);
    GLenum Target              = ToOpenGLTextureType(InType);
    auto PixelFormat           = OpenGLPixelFormats[int(InFormat)];
    auto InternalFormat = PixelFormat.InternalFormat;
    auto Type           = PixelFormat.Type;
    auto Format         = PixelFormat.Format;

    glBindTexture(Target, Handle);
    switch (InType)
    {
    case RHITextureType::Texture1D:
    case RHITextureType::Texture1DArray:
       /*
           ES 32 not support
       */
       break;
    case RHITextureType::Texture2D:
        glTexStorage2D(GL_TEXTURE_2D, InNumMips, PixelFormat.InternalFormat, InX, InY);
        break;
    case RHITextureType::Texture2DArray:
        //glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 256, 256, 2);
        /*
            InX: 纹理宽度
            InY: 纹理高度
            InArraySize: 纹理数组大小
        */
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, InNumMips, PixelFormat.InternalFormat, InX, InY, InArraySize);
        break;
    case RHITextureType::Texture3D:
        /*
            InX: 纹理宽度
            InY: 纹理高度
            InZ: 纹理深度
        */
        glTexStorage3D(GL_TEXTURE_3D, InNumMips, PixelFormat.InternalFormat, InX, InY, InZ);
       break;
    case RHITextureType::TextureCubeMap:
        glTexStorage2D(GL_TEXTURE_CUBE_MAP, InNumMips, PixelFormat.InternalFormat, InX, InY);
        break;
    case RHITextureType::TextureCubeMapArray:
         /*
             ES 32 not support
         */
         break;
    }
    // set the texture wrapping parameters
    glTexParameteri(Target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(Target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(Target, GL_TEXTURE_WRAP_R, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    UpdateImageData();
}


ES32Texture::~ES32Texture()
{
    glDeleteTextures(1, &Handle);
}

GLuint ES32Texture::GetHandle() const
{
    return Handle;
};


void ES32Texture::Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData)
{
    GLenum Target = ToOpenGLTextureType(GetType());
    auto PixelFormat = OpenGLPixelFormats[int(GetFormat())];
    auto InternalFormat = PixelFormat.InternalFormat;
    auto Type = PixelFormat.Type;
    auto Format = PixelFormat.Format;


    /*
        绑定
    */
    glBindTexture(Target, Handle);

    switch (GetType())
    {
    case RHITextureType::Texture1D:
        /*
            ES 3.2没有glTexSubImage1D, 用glTexSubImage2D替代.
        */
        glTexSubImage1D(Target, MipmapLevel, XOffset, Width, Format, Type, InData);
        //glTexSubImage2D(Target, MipmapLevel, XOffset, 0, Width, 1, Format, Type, InData);
        std::cout << "ES32Texture::Update 1D " << MipmapLevel << " XOffset " <<  XOffset << " Width " << Width << " Format " << Format << " Type " <<  Type << std::endl;
        break;
    case RHITextureType::Texture1DArray:
        /*
            更新2D纹理中的一层, 即更新1个1D纹理.
             YOffset指定更新那一层.
            更新TextureArray[YOffset]， 区域[XOffset, XOffset + Width].
        */
        glTexSubImage2D(Target, MipmapLevel, XOffset, YOffset, Width, Height, Format, Type, InData);
        std::cout << "ES32Texture::Update 1D Array MipmapLevel " << MipmapLevel << " XOffset " << XOffset << " YOffset " << YOffset << " Width " << Width << " Height " << Height << " Format " << Format << " Type " << Type << std::endl;
        break;
    case RHITextureType::Texture2D:
        /*
            更新整个2D纹理区域.
            [XOffset, XOffset + Width，YOffset, YOffset + Width]
        */
        glTexSubImage2D(Target, MipmapLevel, XOffset, YOffset, Width, Height, Format, Type, InData);
        break;
    case RHITextureType::Texture2DArray:
        /*
            更新3D纹理中的一层, 即更新1个2D纹理.
            ZOffset指定更新那一层.
            更新TextureArray[ZOffset]， 区域[XOffset, XOffset + Width, YOffset, YOffset + Width].
        */
        glTexSubImage3D(Target, MipmapLevel, XOffset, YOffset, ZOffset, Width, Height, 1, Format, Type, InData);
        break;
    case RHITextureType::Texture3D:
        /*
            更新整个3D纹理,  [XOffset, XOffset + Width，YOffset, YOffset + Width, ZOffset, ZOffset + Width]
        */
        glTexSubImage3D(Target, MipmapLevel, XOffset, YOffset, ZOffset, Width, Height, Depth, Format, Type, InData);
        break;
    case RHITextureType::TextureCubeMap:
        Target = ToOpenGLCubeMapFace((RHICubeMapFace)ZOffset);
        /*
            更新整个2D纹理.  更新CubeMap[Face]，[XOffset, XOffset + Width，YOffset, YOffset + Width]
        */
        glTexSubImage2D(Target, MipmapLevel, XOffset, YOffset, Width, Height, Format, Type, InData);

        std::cout << "cube map " << Target << " " << XOffset << " " << YOffset << " " << Width << " " << Height << std::endl;
        break;
    case RHITextureType::TextureCubeMapArray:
        /*
            更新3D纹理中的一层, 即更新1个CubeMap.
            ZOffset指定更新那一层.
            Depth指定更新多少面.
            更新CubeMapArray[ZOffset, ZOffset + Depth]， 区域[XOffset, XOffset + Width, YOffset, YOffset + Width].
        */
        glTexSubImage3D(Target, MipmapLevel, XOffset, YOffset, ZOffset, Width, Height, Depth, Format, Type, InData);
        //glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, Handle);
        //for (int layer = 0; layer < 2; layer++) {
        //    for (int face = 0; face < 6; face++) {
        //        glTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY,
        //            0, 0, 0, layer * 6 + face,
        //            Width, Height, 1,
        //            GL_RGBA, GL_UNSIGNED_BYTE, InData);
        //    }
        //}
        std::cout << "cube map array Target " << Target << " XOffset " << XOffset << " YOffset " << YOffset << " ZOffset " << ZOffset << " Width " << Width << " Height " << Height << " Depth " << Depth << " Format " << Format << std::endl;
        break;
    default:
        break;
    }
}

void ES32Texture::TransitionImageLayout(int dir)
{

}