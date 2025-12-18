#include <iomanip>
#include <iostream>
#include  "MultiMedia/CADFile/DSTFile.h"
#if 0
int main(int argc, char **argv)
{
    DSTFile file;
    file.Write("test.dst");
    std::cout << "hello world test" << std::endl;
    return 0;
}
#endif
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace  std;
#pragma pack(push, 1)
struct DSTHeader {
    char signature[3] = {'L', 'A', ' '};  // 签名
    uint8_t version = 0;                  // 版本
    uint8_t stitch_count[3] = {0};        // 24位针迹数
    uint8_t color_count = 0;              // 颜色数
    int16_t min_x = 0;                    // 最小X
    int16_t min_y = 0;                    // 最小Y
    int16_t max_x = 0;                    // 最大X
    int16_t max_y = 0;                    // 最大Y
    char design_name[12] = {0};           // 设计名称
    char machine_type[16] = {0};          // 机器型号
    uint8_t reserved[20] = {0};           // 保留区
    uint8_t padding[452] = {0};           // 填充区

    void setStitchCount(uint32_t count) {
        stitch_count[0] = count & 0xFF;
        stitch_count[1] = (count >> 8) & 0xFF;
        stitch_count[2] = (count >> 16) & 0xFF;
    }

    uint32_t getStitchCount() const {
        return (stitch_count[2] << 16) | (stitch_count[1] << 8) | stitch_count[0];
    }
};
#pragma pack(pop)

// DST针迹指令（3字节）
struct DSTStitch {
    uint8_t command_byte;  // 命令+数据
    int8_t dx;             // X移动 (-127~127)
    int8_t dy;             // Y移动 (-127~127)

    DSTStitch(uint8_t cmd, int8_t x, int8_t y)
        : command_byte(cmd), dx(x), dy(y) {}
};

class StraightLineDST {
public:
    // 创建一条水平直线
    static void createHorizontalLine(const std::string& filename,
                                    int startX = 0, int startY = 0,
                                    int length = 100, int stitchDensity = 5) {
        std::vector<DSTStitch> stitches;
        int currentX = 0;  // DST使用相对坐标，起点总是(0,0)
        int currentY = 0;

        // 1. 计算针迹数（每单位长度多少针）
        int numStitches = length / stitchDensity;
        if (numStitches < 1) numStitches = 1;

        // 2. 计算每步移动距离
        int step = length / numStitches;

        // 3. 生成直线针迹
        for (int i = 0; i < numStitches; i++) {
            stitches.emplace_back(0x00, step, 0);  // 正常针迹，向右移动
        }

        // 4. 添加结束指令
        stitches.emplace_back(0xC0, 0, 0);  // 结束指令

        // 5. 创建并保存DST文件
        saveDSTFile(filename, "STRAIGHT_LINE", stitches,
                   startX, startY, length, 0);

        std::cout << "创建直线DST文件: " << filename << std::endl;
        std::cout << "针迹数: " << numStitches << std::endl;
        std::cout << "直线长度: " << length << " 单位 (" << length * 0.1 << "mm)" << std::endl;
    }

    // 创建一条垂直直线
    static void createVerticalLine(const std::string& filename,
                                  int startX = 0, int startY = 0,
                                  int length = 100, int stitchDensity = 5) {
        std::vector<DSTStitch> stitches;
        int numStitches = length / stitchDensity;
        if (numStitches < 1) numStitches = 1;

        int step = length / numStitches;

        for (int i = 0; i < numStitches; i++) {
            stitches.emplace_back(0x00, 0, step);  // 正常针迹，向下移动
        }

        stitches.emplace_back(0xC0, 0, 0);  // 结束指令

        saveDSTFile(filename, "VERTICAL_LINE", stitches,
                   startX, startY, 0, length);
    }

    // 创建一条斜线（45度）
    static void createDiagonalLine(const std::string& filename,
                                  int startX = 0, int startY = 0,
                                  int length = 100, int stitchDensity = 5) {
        std::vector<DSTStitch> stitches;
        int numStitches = length / stitchDensity;
        if (numStitches < 1) numStitches = 1;

        // 45度斜线：dx = dy
        int step = length / numStitches;

        for (int i = 0; i < numStitches; i++) {
            stitches.emplace_back(0x00, step, step);  // 向右下45度
        }

        stitches.emplace_back(0xC0, 0, 0);  // 结束指令

        saveDSTFile(filename, "DIAGONAL_LINE", stitches,
                   startX, startY, length, length);
    }

private:
    static void saveDSTFile(const std::string& filename,
                           const std::string& designName,
                           const std::vector<DSTStitch>& stitches,
                           int startX, int startY,
                           int lengthX, int lengthY) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "无法创建文件: " << filename << std::endl;
            return;
        }

        // 1. 创建DST头部
        DSTHeader header;

        // 设置设计名称
        std::string name = designName;
        if (name.length() > 11) name = name.substr(0, 11);
        strncpy(header.design_name, name.c_str(), sizeof(header.design_name) - 1);

        // 设置针迹数（不包括结束指令）
        header.setStitchCount(stitches.size());  // 包括结束指令

        // 设置颜色数（1种颜色）
        header.color_count = 1;

        // 设置边界框
        // 直线从(startX, startY)到(startX+lengthX, startY+lengthY)
        header.min_x = startX;
        header.min_y = startY;
        header.max_x = startX + lengthX;
        header.max_y = startY + lengthY;

        // 设置机器型号
        strcpy(header.machine_type, "TAJIMA");

        // 2. 写入头部
        file.write(reinterpret_cast<const char*>(&header), sizeof(DSTHeader));

        // 3. 写入针迹数据
        for (const auto& stitch : stitches) {
            file.write(reinterpret_cast<const char*>(&stitch), sizeof(DSTStitch));
        }

        file.close();

        // 4. 创建文本描述文件
        createInfoFile(filename + ".txt", designName, stitches.size() - 1,
                      startX, startY, lengthX, lengthY);
    }

    static void createInfoFile(const std::string& filename,
                              const std::string& designName,
                              int stitchCount,
                              int startX, int startY,
                              int lengthX, int lengthY) {
        std::ofstream info(filename);

        info << "LA:" << designName << std::endl;
        info << "ST:   " << stitchCount << std::endl;
        info << "CO:  1" << std::endl;

        // 计算边界参数
        int maxX = std::max(startX, startX + lengthX);
        int minX = std::min(startX, startX + lengthX);
        int maxY = std::max(startY, startY + lengthY);
        int minY = std::min(startY, startY + lengthY);

        info << "+X:   " << maxX << std::endl;
        info << "-X:   " << -minX << std::endl;
        info << "+Y:   " << maxY << std::endl;
        info << "-Y:   " << -minY << std::endl;
        info << "AX:+" << std::setw(5) << startX << std::endl;
        info << "AY:+" << std::setw(5) << startY << std::endl;
        info << "MX:+" << std::setw(5) << (startX + lengthX) << std::endl;
        info << "MY:+" << std::setw(5) << (startY + lengthY) << std::endl;

        info.close();
    }
};

int DSTMain() {
    std::cout << "=== 生成直线DST文件 ===" << std::endl;

    // 1. 生成水平直线（100单位 = 10mm）
    StraightLineDST::createHorizontalLine("horizontal_line.dst",
                                         0, 0, 100, 10);

    // 2. 生成垂直直线（150单位 = 15mm）
    StraightLineDST::createVerticalLine("vertical_line.dst",
                                       0, 0, 150, 10);

    // 3. 生成45度斜线（200单位 = 20mm）
    StraightLineDST::createDiagonalLine("diagonal_line.dst",
                                       0, 0, 200, 15);

    // 4. 生成更长的直线（300单位 = 30mm）
    StraightLineDST::createHorizontalLine("long_line.dst",
                                         0, 50, 300, 5);

    std::cout << "\n所有文件已生成：" << std::endl;
    std::cout << "1. horizontal_line.dst - 水平直线" << std::endl;
    std::cout << "2. vertical_line.dst   - 垂直直线" << std::endl;
    std::cout << "3. diagonal_line.dst   - 45度斜线" << std::endl;
    std::cout << "4. long_line.dst       - 长直线" << std::endl;
    std::cout << "每个文件都附带对应的 .txt 描述文件" << std::endl;

    return 0;
}
