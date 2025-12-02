#ifdef PROJECT_USE_embroidery
#define LIBEMBROIDERY_IMPLEMENTATION
#endif
#include "embroidery.h"
#include <iostream>
#include <vector>
#include <cmath>

void addTajimaSyncHole(EmbPattern* pattern, double x, double y) {
    if (!pattern) return;

    // 移动到同步孔位置
    emb_pattern_addStitchAbs(pattern, x, y, JUMP, 1);

    // 十字形同步孔序列
    emb_pattern_addStitchAbs(pattern, x + 5, y, JUMP, 1);     // →
    emb_pattern_addStitchAbs(pattern, x - 10, y, JUMP, 1);    // ←
    emb_pattern_addStitchAbs(pattern, x + 5, y, JUMP, 1);     // → (回到中心)
    emb_pattern_addStitchAbs(pattern, x, y + 5, JUMP, 1);     // ↓
    emb_pattern_addStitchAbs(pattern, x, y - 10, JUMP, 1);    // ↑
    emb_pattern_addStitchAbs(pattern, x, y + 5, JUMP, 1);     // ↓ (回到中心)

    std::cout << "添加 Tajima 同步孔 at (" << x << ", " << y << ")" << std::endl;
}

int main() {
#ifdef PROJECT_USE_embroidery
    // 1. 创建图案对象
    EmbPattern* pattern = emb_pattern_create();
    if (!pattern) {
        std::cerr << "无法创建图案对象" << std::endl;
        return 1;
    }

    emb_pattern_addStitchAbs(pattern, 10.0,  0.0, NORMAL, 1);
    emb_pattern_addStitchAbs(pattern, 10.0, 10.0, NORMAL, 1);
    emb_pattern_addStitchAbs(pattern,  0.0,  0.0, END, 1);
    std::cout << " pattern->stitch_list->count " << pattern->stitch_list->count << std::endl;

    emb_pattern_print(pattern);

    emb_pattern_write(pattern, "output.dst", EMB_FORMAT_DST);

    emb_pattern_free(pattern);
#endif
    return 0;
}