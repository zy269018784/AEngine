#if  PROJECT_USE_D3D12
#include <iostream>
#include <vector>
#include <spirv_cross/spirv.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_hlsl.hpp>
std::vector<char> ReadFile(const std::string& filename);
int TestSpirvCross(int argc, char **argv)
{
    std::cout << "TestSpirvCross " << std::endl;
    std::vector<char> spirv_binary = ReadFile("Engine_vert.spv"); // 加载 SPIR-V 二进制文件
    std::cout << spirv_binary.size() << std::endl;
    spirv_cross::CompilerHLSL glsl((uint32_t *)spirv_binary.data(), spirv_binary.size() / 4);
    std::string source = glsl.compile();
    std::cout << source << std::endl;
    return 0;
}
#endif