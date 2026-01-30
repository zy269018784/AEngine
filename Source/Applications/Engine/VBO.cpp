#include "VBO.h"




void AddBox(std::vector<float> &VBO, std::vector<std::uint32_t> &EBO, glm::vec3 AA, glm::vec3 BB)
{
    int VBOOffset = VBO.size();

    // 0
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 1
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 2
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 3
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2

    // 4
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 5
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 6
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 7
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2

    // 右
    EBO.emplace_back(1 + VBOOffset);
    EBO.emplace_back(2 + VBOOffset);
    EBO.emplace_back(6 + VBOOffset);

    EBO.emplace_back(6 + VBOOffset);
    EBO.emplace_back(5 + VBOOffset);
    EBO.emplace_back(1 + VBOOffset);

    // 前
    EBO.emplace_back(3 + VBOOffset);
    EBO.emplace_back(2 + VBOOffset);
    EBO.emplace_back(6 + VBOOffset);

    EBO.emplace_back(6 + VBOOffset);
    EBO.emplace_back(7 + VBOOffset);
    EBO.emplace_back(3 + VBOOffset);

    // 后
    EBO.emplace_back(0 + VBOOffset);
    EBO.emplace_back(1 + VBOOffset);
    EBO.emplace_back(5 + VBOOffset);

    EBO.emplace_back(5 + VBOOffset);
    EBO.emplace_back(4 + VBOOffset);
    EBO.emplace_back(0 + VBOOffset);

    // 下面
    EBO.emplace_back(0 + VBOOffset);
    EBO.emplace_back(1 + VBOOffset);
    EBO.emplace_back(2 + VBOOffset);

    EBO.emplace_back(2 + VBOOffset);
    EBO.emplace_back(3 + VBOOffset);
    EBO.emplace_back(0 + VBOOffset);

    // 上面
    EBO.emplace_back(4 + VBOOffset);
    EBO.emplace_back(5 + VBOOffset);
    EBO.emplace_back(6 + VBOOffset);

    EBO.emplace_back(6 + VBOOffset);
    EBO.emplace_back(7 + VBOOffset);
    EBO.emplace_back(0 + VBOOffset);

    // 左
    EBO.emplace_back(0 + VBOOffset);
    EBO.emplace_back(3 + VBOOffset);
    EBO.emplace_back(7 + VBOOffset);

    EBO.emplace_back(7 + VBOOffset);
    EBO.emplace_back(4 + VBOOffset);
    EBO.emplace_back(0 + VBOOffset);


}

void AddBox2(std::vector<float> &VBO, std::vector<std::uint32_t> &EBO, glm::vec3 AA, glm::vec3 BB)
{
    int VBOOffset = VBO.size();
    int Offset = 0;
    // 下面
    // 0
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 1
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 2
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 3
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2

    // 上面
    // 0
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 1
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 2
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 3
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2

    // 左面
    // 0
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 1
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 2
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 3
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2


    // 右面
    // 0
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 1
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 2
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 3
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2

    // 前面
    // 0
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 1
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 2
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 3
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(BB.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2

    // 后面
    // 0
    VBO.push_back(AA.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(0);  // vec2

    // 1
    VBO.push_back(BB.x); VBO.push_back(AA.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(1); VBO.push_back(0);  // vec2

    // 2
    VBO.push_back(BB.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(1); VBO.push_back(1);  // vec2

    // 3
    VBO.push_back(AA.x); VBO.push_back(BB.y); VBO.push_back(AA.z);  // vec3
    VBO.push_back(0); VBO.push_back(1);  // vec2

    for (int i = 0; i < 6; i++)
    {
        // 下面
        Offset = 4 * i;
        EBO.emplace_back(0 + VBOOffset + Offset);
        EBO.emplace_back(1 + VBOOffset + Offset);
        EBO.emplace_back(2 + VBOOffset + Offset);

        EBO.emplace_back(2 + VBOOffset + Offset);
        EBO.emplace_back(3 + VBOOffset + Offset);
        EBO.emplace_back(0 + VBOOffset + Offset);
    }
}