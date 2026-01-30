#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <cstdint>
void AddBox(std::vector<float> &VBO, std::vector<std::uint32_t> &EBO, glm::vec3 AA, glm::vec3 BB);
void AddBox2(std::vector<float> &VBO, std::vector<std::uint32_t> &EBO, glm::vec3 AA, glm::vec3 BB);